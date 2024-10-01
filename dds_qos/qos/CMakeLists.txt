# Copyright 2023 Covidien LP
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

set(SECURE_DDS_QOS_PROFILE_IN "einstein_custom_qos_profile_library.xml.in")
set(SECURE_DDS_QOS_PROFILE "einstein_custom_qos_profile_library.xml")
set(SECURE_DDS_QOS_PROFILE_WIN_ESAT "einstein_custom_qos_profile_library_esat_win.xml")
set(SECURE_DDS_QOS_PROFILE_TEST "einstein_custom_qos_profile_library_test.xml")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DDS_SECURE_LOG_LEVEL "ERROR")
else()
    set(DDS_SECURE_LOG_LEVEL "WARNING")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(DDS_SECURE_LOG_PATH "C:\\Users\\Medtronic\\AppData\\Local\\Temp\\")
    set(SECURITY_RESOURCE_LOCATION "E:\\einstein\\application\\resource\\")
    set(SECURITY_HUGO_CA_CERT_LOCATION "C:\\Windows\\System32\\drivers\\etc\\")
    set(SECURITY_HUGO_ID_CERT_LOCATION "E:\\einstein\\keys\\comm\\")
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(DDS_SECURE_LOG_PATH "/tmp/")
    set(SECURITY_RESOURCE_LOCATION "./resource/")
    set(SECURITY_HUGO_CA_CERT_LOCATION "./resource/")
    set(SECURITY_HUGO_ID_CERT_LOCATION "./resource/")
else()
    set(DDS_SECURE_LOG_PATH "/tmp/")
    set(SECURITY_RESOURCE_LOCATION "/einstein/application/resource/")
    set(SECURITY_HUGO_CA_CERT_LOCATION "/etc/")
    set(SECURITY_HUGO_ID_CERT_LOCATION "/einstein/keys/comm/")
endif()

set(SECURITY_PREFIX "file:")

set(DDS_SECURE_LOG_FILE "dds_secure.log")

# Certificats expiration
set(CERTIFICATE_VALIDITY_NOT_BEFORE "2023-08-20T18:27:10")
set(CERTIFICATE_VALIDITY_NOT_AFTER "2030-10-20T18:27:10")


# Add security artifacts
# Use Hugo Identity Certificate for DDS
# Support the ESAT to load the engineering identity certificate for DDS secure

set(GOVERNANCE_FILE "einstein_domain_governance.xml")
set(GOVERNANCE_FILE_IN "${GOVERNANCE_FILE}.in")
configure_file(${GOVERNANCE_FILE_IN} ${GOVERNANCE_FILE} @ONLY)

set(PERMISSION_FILE "einstein_participant_permissions.xml")
set(PERMISSION_FILE_IN "${PERMISSION_FILE}.in")
configure_file(${PERMISSION_FILE_IN} ${PERMISSION_FILE} @ONLY)

set(GOVERNANCE_FILE_SIGNED "einstein_domain_governance.p7s")
set(PERMISSION_FILE_SIGNED "einstein_participant_permissions.p7s")

set(PERMISSIONS_CA_CERT "EC_X509.CRT")
set(PERMISSIONS_CA_KEY "EC_PRIV.PEM")
configure_file(${EIN_SRC_ROOT}/keys/engineering-keys/general/${PERMISSIONS_CA_KEY} ${PERMISSIONS_CA_KEY} COPYONLY)

if(CMAKE_BUILD_TYPE STREQUAL "Release" AND PRODSIGN STREQUAL "ON" AND BAMBOO_BUILD)
    
    set(PERMISSIONS_CA_SIGN_SCRIPT "permissions_ca_sign_files_production.sh")
    configure_file(${PERMISSIONS_CA_SIGN_SCRIPT} ${PERMISSIONS_CA_SIGN_SCRIPT} @ONLY)

    set(PRODUCTION_SIGN_GENERAL_SCRIPT "production-sign-general.sh")
    set(PERMISSIONS_SIGN_DDS_SCRIPT "production-sign-dds.sh")
    set(X509CRT "tamans-ap192lv.crt")
    configure_file("${EIN_SRC_ROOT}/keys/production-keys/general/CN=MITG-Einstein-CS-Dev-2024.PEM" ${PERMISSIONS_CA_CERT} COPYONLY)
    
    execute_process(COMMAND bash -c "./${PERMISSIONS_CA_SIGN_SCRIPT} ${EIN_SRC_ROOT}/tool/scripts/production_signing/${PRODUCTION_SIGN_GENERAL_SCRIPT} \
        ${EIN_SRC_ROOT}/tool/scripts/production_signing/${PERMISSIONS_SIGN_DDS_SCRIPT} ${EIN_SRC_ROOT}/tool/scripts/production_signing/${X509CRT} \
        ${PERMISSION_FILE} ${GOVERNANCE_FILE} ${CMAKE_CURRENT_BINARY_DIR}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    
else()

    set(PERMISSIONS_CA_SIGN_SCRIPT "permissions_ca_sign_files.sh")
    set(PERMISSIONS_CA_SIGN_SCRIPT_WINDOWS "permissions_ca_sign_files.ps1")
    configure_file(${EIN_SRC_ROOT}/keys/engineering-keys/general/${PERMISSIONS_CA_CERT} ${PERMISSIONS_CA_CERT} COPYONLY)

    if (CMAKE_SYSTEM_NAME STREQUAL Windows)
        configure_file(${PERMISSIONS_CA_SIGN_SCRIPT_WINDOWS} ${PERMISSIONS_CA_SIGN_SCRIPT_WINDOWS} @ONLY)
        execute_process(COMMAND PowerShell -ExecutionPolicy Bypass -File ${PERMISSIONS_CA_SIGN_SCRIPT_WINDOWS} ${PERMISSION_FILE} ${GOVERNANCE_FILE} ${PERMISSIONS_CA_CERT} ${PERMISSIONS_CA_KEY} "${OPENSSL_ROOT_DIR}/bin/openssl.exe" 
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        configure_file(${PERMISSIONS_CA_SIGN_SCRIPT} ${PERMISSIONS_CA_SIGN_SCRIPT} @ONLY)
        execute_process(COMMAND bash -c "./${PERMISSIONS_CA_SIGN_SCRIPT} ${PERMISSION_FILE} ${GOVERNANCE_FILE} ${PERMISSIONS_CA_CERT} ${PERMISSIONS_CA_KEY}"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

endif()

install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PERMISSIONS_CA_CERT}")
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${GOVERNANCE_FILE_SIGNED}")
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PERMISSIONS_CA_KEY}")
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${PERMISSION_FILE_SIGNED}")

configure_file(${SECURE_DDS_QOS_PROFILE_IN} ${SECURE_DDS_QOS_PROFILE} @ONLY)
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${SECURE_DDS_QOS_PROFILE}")

cmrc_add_resource_library(
        einstein_custom_qos_profile_library_modern
        WHENCE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/einstein_custom_qos_profile_library.xml.in"
)

# Custom configuration for ESAT on Windows
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(DDS_SECURE_LOG_PATH ".\\esat_workspace\\temp_log_files\\")
    set(SECURITY_RESOURCE_LOCATION ".\\resource\\")
    set(SECURITY_HUGO_CA_CERT_LOCATION ".\\resource\\")
    set(SECURITY_HUGO_ID_CERT_LOCATION ".\\resource\\")
    configure_file(${SECURE_DDS_QOS_PROFILE_IN} ${SECURE_DDS_QOS_PROFILE_WIN_ESAT} @ONLY)
    install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${SECURE_DDS_QOS_PROFILE_WIN_ESAT}")
endif()

# Custom configuration for Edge tool
if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(EDGE_SECURE_DDS_QOS_PROFILE "edge_einstein_custom_qos_profile_library.xml")
    set(DDS_SECURE_LOG_PATH "$(EDGE_RUNTIME_DIR)/")
    set(SECURITY_RESOURCE_LOCATION "$(EDGE_RUNTIME_DIR)/resource/")
    set(SECURITY_HUGO_CA_CERT_LOCATION ${SECURITY_RESOURCE_LOCATION})
    set(SECURITY_HUGO_ID_CERT_LOCATION ${SECURITY_RESOURCE_LOCATION})
    configure_file(${SECURE_DDS_QOS_PROFILE_IN} ${EDGE_SECURE_DDS_QOS_PROFILE} @ONLY)
    install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${EDGE_SECURE_DDS_QOS_PROFILE}")
endif()

# It have to be at the end because override a lot of variables
set(SECURITY_PREFIX "data:,")
set(TESTS_ONLY_PROPERTY "<!--This is required in tests becase test QoS security snipplet use data instead of file values which are much longer-->
                    <participant_property_string_max_length>0xffff</participant_property_string_max_length>")
set(TESTS_ONLY_PROPERTY2 "<!--This property is required because exist some tests which dont use EinsteinDomainParticipantQoS.-->
            <participant_qos>
                <resource_limits>
                    <participant_property_string_max_length>0xffff</participant_property_string_max_length>
                </resource_limits>
            </participant_qos>")

#use different log location for  windows tests
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(DDS_SECURE_LOG_PATH "${EIN_BUILD_ROOT}\\Testing\\Temporary\\")
else()
    set(DDS_SECURE_LOG_PATH "/tmp/")
endif()

#tests doesnt use file, clear location part
set(SECURITY_RESOURCE_LOCATION "")
set(SECURITY_HUGO_ID_CERT_LOCATION "")
set(SECURITY_HUGO_CA_CERT_LOCATION "")

set(HUGO_CA_CERT_TEST "HUGO_CA_CERT_TEST.PEM")
configure_file(${HUGO_CA_CERT_TEST} ${HUGO_CA_CERT_TEST} COPYONLY)
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${HUGO_CA_CERT_TEST}")

set(HUGO_ID_CERT_TEST "HUGOID_CERT_TEST.PEM")
configure_file(${HUGO_ID_CERT_TEST} ${HUGO_ID_CERT_TEST} COPYONLY)
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${HUGO_ID_CERT_TEST}")

set(HUGO_ID_PRIV_TEST "HUGOID_PRIV_TEST.PEM")
configure_file(${HUGO_ID_PRIV_TEST} ${HUGO_ID_PRIV_TEST} COPYONLY)
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${HUGO_ID_PRIV_TEST}")


file(READ "${CMAKE_CURRENT_BINARY_DIR}/${HUGO_CA_CERT_TEST}" TMP)
string(REGEX REPLACE "^.*(\\-\\-\\-\\-\\-BEGIN CERTIFICATE\\-\\-\\-\\-\\-)" "\\1" TMP "${TMP}")
set(HUGO_CA_CERT ${TMP})

file(READ "${CMAKE_CURRENT_BINARY_DIR}/${HUGO_ID_CERT_TEST}" TMP)
string(REGEX REPLACE "^.*(\\-\\-\\-\\-\\-BEGIN CERTIFICATE\\-\\-\\-\\-\\-)" "\\1" TMP "${TMP}")
set(HUGO_ID_CERT ${TMP})

file(READ "${CMAKE_CURRENT_BINARY_DIR}/${HUGO_ID_PRIV_TEST}" TMP)
set(HUGO_ID_PRIV ${TMP})

file(READ "${CMAKE_CURRENT_BINARY_DIR}/${PERMISSIONS_CA_CERT}" TMP)
string(REGEX REPLACE "^.*(\\-\\-\\-\\-\\-BEGIN CERTIFICATE\\-\\-\\-\\-\\-)" "\\1" TMP "${TMP}")
set(PERMISSIONS_CA_CERT ${TMP})

file(READ "${CMAKE_CURRENT_BINARY_DIR}/${GOVERNANCE_FILE_SIGNED}" TMP)
set(GOVERNANCE_FILE_SIGNED "<![CDATA[${TMP}]]>")

file(READ "${CMAKE_CURRENT_BINARY_DIR}/${PERMISSION_FILE_SIGNED}" TMP)
set(PERMISSION_FILE_SIGNED "<![CDATA[${TMP}]]>")

configure_file(${SECURE_DDS_QOS_PROFILE_IN} ${SECURE_DDS_QOS_PROFILE_TEST} @ONLY)
install_resource_files("${CMAKE_CURRENT_BINARY_DIR}/${SECURE_DDS_QOS_PROFILE_TEST}")
