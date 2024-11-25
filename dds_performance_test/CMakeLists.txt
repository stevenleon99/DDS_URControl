# (c) 2020 Copyright, Real-Time Innovations, Inc. All rights reserved.
# No duplications, whole or partial, manual or electronic, may be made
# without express written permission.  Any such copies, or revisions thereof,
# must display this notice unaltered.
# This code contains trade secrets of Real-Time Innovations, Inc.
cmake_minimum_required(VERSION 3.11)
project(rticonnextdds-getting-started-basic-qos)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/cmake"
)
message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

# Include ConnextDdsAddExample.cmake from resources/cmake
include(ConnextDdsAddExample)

connextdds_add_example(
    IDL "DDS_test"
    LANG "C++11"
    CODEGEN_ARGS
    APPLICATION_NAMES
        "DDS_test_publisher"
        "DDS_test_subscriber"
    QOS_FILENAME "test_qos_file.xml"
)

# Path to your shell script
set(SCRIPT_NAME "/home/steve/rticonnextdds-getting-started/DDS_URControl/dds_performance_test/script/run_computer1.sh"
                "/home/steve/rticonnextdds-getting-started/DDS_URControl/dds_performance_test/script/run_computer2.sh")

# Install the shell script to the "bin" directory
install(FILES ${SCRIPT_NAME} DESTINATION ${CMAKE_BINARY_DIR} PERMISSIONS OWNER_EXECUTE OWNER_READ GROUP_EXECUTE WORLD_EXECUTE)

