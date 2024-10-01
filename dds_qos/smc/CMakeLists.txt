# Copyright 2022 Covidien LP
# All Rights Reserved. The information contained herein is confidential
# property of Covidien LP. The use, copying, transfer or disclosure of such
# information is prohibited except by express written agreement with Covidien LP.

require_conditions_or_return(TARGET_ARCHS linux_x86_64 qnx_armv7 qnx_x86_64 windows_x64)

# Participant configuration file for SMC readers and writers
set(PARTICIPANT_NAME "smc_smc_participant.xml")

configure_file("smc_participant_library.xml" ${PARTICIPANT_NAME} @ONLY)

install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PARTICIPANT_NAME}")

# Participant configuration file for ORTI readers and writers
set(PARTICIPANT_NAME "gui_smc_participant.xml")

configure_file("gui_participant_library.xml" ${PARTICIPANT_NAME} @ONLY)

install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PARTICIPANT_NAME}")

# Participant configuration file for MSC readers and writers
set(PARTICIPANT_NAME "msc_smc_participant.xml")

configure_file("msc_participant_library.xml" ${PARTICIPANT_NAME} @ONLY)

install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PARTICIPANT_NAME}")

# Participant configuration file for MSC readers and writers
set(PARTICIPANT_NAME "tst_msc_smc_participant.xml")

configure_file("tst_participant_library.xml" ${PARTICIPANT_NAME} @ONLY)

install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PARTICIPANT_NAME}")
