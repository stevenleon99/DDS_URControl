cmake_minimum_required(VERSION 3.11)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(captureMouse captureMouse)
# build captureMouse library
# Find the X11 library
find_package(X11 REQUIRED)

# Add the executable target
add_library(${captureMouse} SHARED captureMouse.cpp)

# Link the X11 library to the executable
target_link_libraries(${captureMouse} X11::X11)