

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from URController.idl
using RTI Code Generator (rtiddsgen) version 4.3.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef URControllerPlugin_457231758_h
#define URControllerPlugin_457231758_h

#include "URController.hpp"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#define DesireJointPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

#define DesireJointPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define DesireJointPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

#define DesireJointPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define DesireJointPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern DesireJoint*
DesireJointPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern DesireJoint*
DesireJointPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern DesireJoint*
DesireJointPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
DesireJointPluginSupport_copy_data(
    DesireJoint *out,
    const DesireJoint *in);

NDDSUSERDllExport extern void 
DesireJointPluginSupport_destroy_data_w_params(
    DesireJoint *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
DesireJointPluginSupport_destroy_data_ex(
    DesireJoint *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
DesireJointPluginSupport_destroy_data(
    DesireJoint *sample);

NDDSUSERDllExport extern void 
DesireJointPluginSupport_print_data(
    const DesireJoint *sample,
    const char *desc,
    unsigned int indent);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
DesireJointPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
DesireJointPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
DesireJointPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
DesireJointPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
DesireJointPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    DesireJoint *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
DesireJointPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    DesireJoint *out,
    const DesireJoint *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool
DesireJointPlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const DesireJoint *sample,
    ::dds::core::policy::DataRepresentationId representation
    = ::dds::core::policy::DataRepresentation::xcdr()); 

NDDSUSERDllExport extern RTIBool 
DesireJointPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    DesireJoint **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *cdrStream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
DesireJointPlugin_deserialize_from_cdr_buffer(
    DesireJoint *sample,
    const char * buffer,
    unsigned int length);    

NDDSUSERDllExport extern unsigned int 
DesireJointPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
DesireJointPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
DesireJointPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
DesireJointPlugin_get_serialized_key_max_size_for_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
DesireJointPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    DesireJoint ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *cdrStream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
DesireJointPlugin_new(void);

NDDSUSERDllExport extern void
DesireJointPlugin_delete(struct PRESTypePlugin *);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* URControllerPlugin_457231758_h */

