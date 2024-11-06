cmake_minimum_required(VERSION 3.22)

project(
    displaywindow
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

# Find dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/displaywindow.cpp)

add_executable(displaywindow ${SOURCES})

target_link_libraries(
    displaywindow
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
        ${Boost_LIBRARIES}
)


