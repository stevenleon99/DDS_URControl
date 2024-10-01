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

# # Specify the file you want to copy
# set(SOURCE_FILE "USER_QOS_PROFILES.xml")

# # Specify the destination directory (this is where the file will be copied to)
# set(DESTINATION_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# # Create a custom command to copy the file
# add_custom_command(
#     OUTPUT ${DESTINATION_DIR}/${SOURCE_FILE}
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCE_FILE} ${DESTINATION_DIR}
#     DEPENDS "${SOURCE_FILE}"
#     COMMENT "Copying ${SOURCE_FILE} to ${DESTINATION_DIR}"
# )

# # Create a custom target to ensure the file is copied during the build
# add_custom_target(copy_qos_file ALL DEPENDS ${DESTINATION_DIR}/${SOURCE_FILE})
