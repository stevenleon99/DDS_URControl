cmake_minimum_required(VERSION 3.11)

project(dds_urcontrol)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # For executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # For shared libraries (.so/.dll)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # For static libraries (.a/.lib)

add_subdirectory(Matlab_URController)
add_subdirectory(mouse_movement)
add_subdirectory(dds)
add_subdirectory(displaywindow)
