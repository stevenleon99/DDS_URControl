#include "captureMouse.hpp"

std::vector<double> trackMousePos(){
    vector<double> res;
    int ratio = 2000;
    // Open a connection to the X server
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open display\n";
        return res;
    }
    // Get the root window (the top-level window that covers the screen)
    Window root = DefaultRootWindow(display);
    // Variables to store mouse information
    int root_x, root_y;  // Mouse position relative to the root window
    int win_x, win_y;    // Mouse position relative to the current window
    unsigned int mask;   // Modifier keys and buttons pressed

    // Variables to store the window information
    Window returned_window;
    if (XQueryPointer(display, root, &returned_window, &returned_window,
                          &root_x, &root_y, &win_x, &win_y, &mask)) {
        // std::cout << "Mouse position: (" << root_x << ", " << root_y << ")\n";
        res = {static_cast<double>(root_x)/ratio, 
               static_cast<double>(root_y)/ratio};
    } else {
        std::cerr << "Failed to query pointer\n";
    }

    // Close the display connection
    XCloseDisplay(display);

    return res;
};