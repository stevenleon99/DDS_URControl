# Copyright 2022 Covidien LP
# All Rights Reserved. The information contained herein is confidential
# property of Covidien LP. The use, copying, transfer or disclosure of such
# information is prohibited except by express written agreement with Covidien LP.

require_conditions_or_return(TARGET_ARCHS linux_gateway_x86_64 linux_x86_64 qnx_armv7 qnx_x86_64 windows_x64)

# Setting Priority Levels based on the OS

unset(RTI_DDS_EVENT_THREAD_PRIORITY)
unset(RTI_DDS_RECEIVER_POOL_THREAD_PRIORITY)

if (CMAKE_SYSTEM_NAME STREQUAL Linux OR CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(RTI_DDS_EVENT_THREAD_PRIORITY THREAD_PRIORITY_ABOVE_NORMAL CACHE STRING "DDS Event Thread Priority")
    set(RTI_DDS_RECEIVER_POOL_THREAD_PRIORITY THREAD_PRIORITY_ABOVE_NORMAL CACHE STRING "DDS Receiver Thread Priority")
elseif (CMAKE_SYSTEM_NAME STREQUAL QNX)
    # Setting Priorities as defined in the PriorityCategories from einstein::os::thread
    set(NRT_EVENT_HANDLER 80)
    set(NRT_COMMUNICATION_ENDPOINT 100)
    set(RTI_DDS_EVENT_THREAD_PRIORITY ${NRT_EVENT_HANDLER} CACHE STRING "DDS Event Thread Priority")
    set(RTI_DDS_RECEIVER_POOL_THREAD_PRIORITY ${NRT_COMMUNICATION_ENDPOINT} CACHE STRING "DDS Receiver Thread Priority")
endif()

set(DOMAIN_LIBRARY "einstein_domain_library.xml")
configure_file(${DOMAIN_LIBRARY} ${DOMAIN_LIBRARY} @ONLY)

install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${DOMAIN_LIBRARY}")
