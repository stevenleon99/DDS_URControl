#include <iostream>
#include <vector>
#include <sstream>
#include <random>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "linmath.h"

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

// Screen dimensions
const int WIDTH = 600;
const int HEIGHT = 600;

// Mouse position
float pos_x = 0, pos_y = 0;
float pos_x_set = 0, pose_y_set = 0;
// Store the history of mouse positions as 3D points
std::vector<glm::vec3> mousePositions;

std::vector<float> scaleCoordinate(const std::vector<float> in) {
    std::vector<float> res;

    std::random_device rd2;  // Seed the random number generator
    std::mt19937 gen2(rd2()); // Mersenne Twister engine
    std::uniform_real_distribution<> dis2(-0.01, 0.01); // Range between -1 and 1

    if (in[0] > 0.3 && in[0] < 0.6 && in[1] > 0.13 && in[1] < 0.44) {
        res.push_back( ( in[0] - 0.45  ) * 5.0 / 0.3 ); // map between -1 to 1
        res.push_back(-( in[1] - 0.285 ) * 5.0 / 0.3 ); // map between -1 to 1
        res.push_back( ( in[2] ) );
    } else {
        return {-2,-2,-2};
    }
    return res;
}

void parseMemory(const char* mem){
    // Parse the data using a comma as the delimiter
    std::istringstream stream(mem);
    std::string item;
    std::vector<std::string> items;

    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> dis(-0.01, 0.01); // Range between -1 and 1


    while (std::getline(stream, item, ',')) {
        items.push_back(item);
    }

    // // Display the parsed tokens
    // std::cout << "Parsed tokens:" << std::endl;
    // for (const auto& t : items) {
    //     std::cout << "number: " << stof(t) << std::endl;
    // }
    float x = stof(items[0]);
    float y = stof(items[1]);
    float z = stof(items[2]);

    auto scale_coord = scaleCoordinate({x, y, z});
    if (scale_coord[0] == -2) return;

    pos_x = scale_coord[0]*3;
    pos_y = scale_coord[1]*3;

    mousePositions.push_back(glm::vec3(scale_coord[0], 
                                       scale_coord[1], 
                                    //    dis(gen)
                                       scale_coord[2]));
}

//========================================================================
// Mouse position callback function
//========================================================================


// Callback function to capture mouse position
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    
    // // Convert to normalized device coordinates (NDC)
    // float x = (2.0f * xpos) / WIDTH - 1.0f;
    // float y = 1.0f - (2.0f * ypos) / HEIGHT; // Invert Y for OpenGL
    // float z = 0.0f; // Arbitrary depth for demonstration

    // std::cout << "x: " << x << " y: " << y << std::endl;
    // // Store the position as a 3D point
    // mousePositions.push_back(glm::vec3(x, y, z));
    // pos_x = x*4, pos_y = y;

    try {
        // Open the existing shared memory object
        shared_memory_object shm(open_only, "position", read_only);

        // Map the shared memory into this process
        mapped_region region(shm, read_only);

        // Read the data from the shared memory
        char *mem = static_cast<char*>(region.get_address());
        if (mem == nullptr) {
            std::cerr << "memory is null" << std::endl;
            return;
        } else if (std::string(mem).length() == 0) {
            std::cerr << "memory is empty" << std::endl;
            return;
        }
        std::cout << "Message read from shared memory: " << mem << std::endl;
        parseMemory(mem);

        // Remove the shared memory
        shared_memory_object::remove("position");

    } catch (const interprocess_exception& e) {
        std::cerr << "Interprocess exception: " << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;

    }
    
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if ((button == GLFW_MOUSE_BUTTON_LEFT)) {
        if (action == GLFW_PRESS) {
            pos_x_set = pos_x;
            pose_y_set = pos_y;
        } else if (action == GLFW_RELEASE) {
            // Action when the left button is released
        }
    }
}

// Render the scene
void drawScene() {
    // glBegin(GL_POINTS);
    // for (const auto& pos : mousePositions) {
    //     glVertex3f(pos.x, pos.y, pos.z);
    // }
    // glEnd();

    const GLfloat model_diffuse[4]  = {1.0f, 0.8f, 0.2f, 0.3f}; // Opaque diffuse color
    const GLfloat model_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // White specular for high reflection
    const GLfloat model_shininess   = 80.0f;                    // Higher value for sharp highlights

    // Set color and material
    glColor4fv(model_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, model_shininess);

    float halfSize = 0.01f; // Half the side length of the cube

    for (const auto& pos : mousePositions){
        // Draw solid cube
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solid mode
        glBegin(GL_QUADS);
        // Front face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z + halfSize);
        // Back face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z - halfSize);
        // Left face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z - halfSize);
        // Right face
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize);
        // Top face
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z + halfSize);
        // Bottom face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z + halfSize);
        glEnd();

        // Draw wireframe cube on top
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
        glBegin(GL_QUADS);
        // Front face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z + halfSize);
        // Back face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z - halfSize);
        // Left face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z - halfSize);
        // Right face
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize);
        // Top face
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y + halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y + halfSize, pos.z + halfSize);
        // Bottom face
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize);
        glVertex3f(pos.x + halfSize, pos.y - halfSize, pos.z + halfSize);
        glVertex3f(pos.x - halfSize, pos.y - halfSize, pos.z + halfSize);
        glEnd();

        // Reset to solid fill for subsequent objects
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
}


//========================================================================
// Draw a 2D grid (used for orthogonal views)
//========================================================================

static void drawGrid(float scale, int steps)
{
    int i;
    float x, y;
    mat4x4 view;

    glPushMatrix();

    // Set background to some dark bluish grey
    glClearColor(0.05f, 0.05f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Setup modelview matrix (flat XY view)
    {
        vec3 eye = { 0.f, 0.f, 1.f };
        vec3 center = { 0.f, 0.f, 0.f };
        vec3 up = { 0.f, 1.f, 0.f };
        mat4x4_look_at(view, eye, center, up);
    }
    glLoadMatrixf((const GLfloat*) view);

    // We don't want to update the Z-buffer
    glDepthMask(GL_FALSE);

    // Set grid color
    glColor3f(0.0f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    // Horizontal lines
    x = scale * 0.5f * (float) (steps - 1);
    y = -scale * 0.5f * (float) (steps - 1);
    for (i = 0;  i < steps;  i++)
    {
        glVertex3f(-x, y, 0.0f);
        glVertex3f(x, y, 0.0f);
        y += scale;
    }

    // Vertical lines
    x = -scale * 0.5f * (float) (steps - 1);
    y = scale * 0.5f * (float) (steps - 1);
    for (i = 0;  i < steps;  i++)
    {
        glVertex3f(x, -y, 0.0f);
        glVertex3f(x, y, 0.0f);
        x += scale;
    }

    glEnd();

    // Enable Z-buffer writing again
    glDepthMask(GL_TRUE);

    glPopMatrix();
}

void drawGroundPlane(float size, int divisions) {
    float halfSize = size / 2.0f;
    float divisionSize = size / divisions;
    // Set the color to white for the entire ground plane
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Blue background
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {
            float x = -halfSize + i * divisionSize;
            float z = -halfSize + j * divisionSize;

            // Color alternates for a checkerboard pattern
            glColor3f((i + j) % 2 == 0 ? 0.8f : 0.6f, (i + j) % 2 == 0 ? 0.8f : 0.6f, (i + j) % 2 == 0 ? 0.8f : 0.6f);

            glVertex3f(x, -3.0f, z);
            glVertex3f(x + divisionSize, -3.0f, z);
            glVertex3f(x + divisionSize, -3.0f, z + divisionSize);
            glVertex3f(x, -3.0f, z + divisionSize);
        }
    }
    glEnd();
}

static void drawAllViews(void)
{
    // const GLfloat light_position[4] = {1.0f, 8.0f, 8.0f, 1.0f};
    // const GLfloat light_diffuse[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
    // const GLfloat light_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    // const GLfloat light_ambient[4]  = {0.2f, 0.2f, 0.3f, 1.0f};
    float aspect;
    mat4x4 view, projection;

    // Calculate aspect of window
    if (HEIGHT > 0)
        aspect = (float) WIDTH / (float) HEIGHT;
    else
        aspect = 1.f;

    // Clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable scissor test
    glEnable(GL_SCISSOR_TEST);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // ** ORTHOGONAL VIEWS **

    // // For orthogonal views, use wireframe rendering
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Enable line anti-aliasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Setup orthogonal projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 1.0, 50.0);

    // Upper left view (TOP VIEW)
    glViewport(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
    glScissor(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
    {
        vec3 eye = { 0.f, 10.f, 1e-3f };
        vec3 center = { 0.f, 0.f, 0.f };
        vec3 up = { 0.f, 1.f, 0.f };
        mat4x4_look_at( view, eye, center, up );
    }
    glLoadMatrixf((const GLfloat*) view);
    // glClearColor(1.0f, 0.0f, 0.0f, 0.2f);  // Red background
    // glClear(GL_COLOR_BUFFER_BIT);
    drawGrid(0.5, 12);
    drawScene();

    // Lower left view (FRONT VIEW)
    glViewport(0, 0, WIDTH / 2, HEIGHT / 2);
    glScissor(0, 0, WIDTH / 2, HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
    {
        vec3 eye = { 0.f, 0.f, 10.f };
        vec3 center = { 0.f, 0.f, 0.f };
        vec3 up = { 0.f, 1.f, 0.f };
        mat4x4_look_at( view, eye, center, up );
    }
    glLoadMatrixf((const GLfloat*) view);
    // glClearColor(0.0f, 1.0f, 0.0f, 0.2f);  // Green background
    // glClear(GL_COLOR_BUFFER_BIT);
    drawGrid(0.5, 12);
    drawScene();

    // Lower right view (SIDE VIEW)
    glViewport(WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2);
    glScissor(WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
    {
        vec3 eye = { 10.f, 0.f, 0.f };
        vec3 center = { 0.f, 0.f, 0.f };
        vec3 up = { 0.f, 1.f, 0.f };
        mat4x4_look_at( view, eye, center, up );
    }
    glLoadMatrixf((const GLfloat*) view);
    // glClearColor(0.0f, 0.0f, 1.0f, 0.2f);  // Blue background
    // glClear(GL_COLOR_BUFFER_BIT);
    drawGrid(0.5, 12);
    drawScene();

    // Disable line anti-aliasing
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);

    // ** PERSPECTIVE VIEW **
    // For perspective view, use solid rendering
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Enable face culling (faster rendering)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // Setup perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    mat4x4_perspective(projection,
                       65.f * (float) M_PI / 180.f,
                       aspect,
                       1.f, 50.f);
    glLoadMatrixf((const GLfloat*) projection);

    // Upper right view (PERSPECTIVE VIEW)
    glViewport(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
    glScissor(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);


    glMatrixMode(GL_MODELVIEW);
    {
        vec3 eye = { 5.f+pose_y_set, 1.0f, pos_x_set };
        vec3 center = { 0.f, 0.f, 0.f };
        vec3 up = { 0.f, 1.f, 0.f };
        mat4x4_look_at( view, eye, center, up );
    }
    glLoadMatrixf((const GLfloat*) view);

    // // Configure and enable light source 1
    // glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    // glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    // glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    // glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    // glEnable(GL_LIGHT1);
    // glEnable(GL_LIGHTING);

    drawGroundPlane(10.0f, 20);
    
    // Draw scene
    drawScene();

    // Disable lighting
    glDisable(GL_LIGHTING);

    // Disable face culling
    glDisable(GL_CULL_FACE);

    // Disable depth test
    glDisable(GL_DEPTH_TEST);

    // Disable scissor test
    glDisable(GL_SCISSOR_TEST);

}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Mouse Trail - Split Views", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Get window size
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // Calculate center position
    int xPos = (windowWidth + WIDTH) / 2;
    int yPos = (windowHeight) / 2;
    // Set window position
    glfwSetWindowPos(window, xPos, yPos);


    // Set the mouse callback
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    
    // Set up basic OpenGL settings
    glPointSize(5.0f); // Size of each point
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f); // Clear color (blue)

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawAllViews();

        // Swap buffers
        glfwSwapBuffers(window);

        // wait for events
        glfwWaitEvents();
        
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}