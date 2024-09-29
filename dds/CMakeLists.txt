# (c) 2020 Copyright, Real-Time Innovations, Inc. All rights reserved.
# No duplications, whole or partial, manual or electronic, may be made
# without express written permission.  Any such copies, or revisions thereof,
# must display this notice unaltered.
# This code contains trade secrets of Real-Time Innovations, Inc.
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/cmake"
)

message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# Include ConnextDdsAddExample.cmake from resources/cmake
include(ConnextDdsAddExample)

connextdds_add_example(
    IDL "URController"
    LANG "C++11"
    CODEGEN_ARGS
    APPLICATION_NAMES
        "URController_publisher"
        "URController_subscriber"
    QOS_FILENAME "USER_QOS_PROFILES.xml"
    DEPENDENCIES
        "captureMouse" 
        "URController"
)

