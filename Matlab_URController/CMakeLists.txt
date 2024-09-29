cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MatlabProject URController)

# build simulink library
add_library(${MatlabProject} SHARED 
    URController.cpp)