

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from DDS_test.idl
using RTI Code Generator (rtiddsgen) version 4.3.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef DDS_testPlugin_1934069328_h
#define DDS_testPlugin_1934069328_h

#include "DDS_test.hpp"

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

#define DDSTestMessagePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

#define DDSTestMessagePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define DDSTestMessagePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

#define DDSTestMessagePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define DDSTestMessagePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern DDSTestMessage*
DDSTestMessagePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern DDSTestMessage*
DDSTestMessagePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern DDSTestMessage*
DDSTestMessagePluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
DDSTestMessagePluginSupport_copy_data(
    DDSTestMessage *out,
    const DDSTestMessage *in);

NDDSUSERDllExport extern void 
DDSTestMessagePluginSupport_destroy_data_w_params(
    DDSTestMessage *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
DDSTestMessagePluginSupport_destroy_data_ex(
    DDSTestMessage *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
DDSTestMessagePluginSupport_destroy_data(
    DDSTestMessage *sample);

NDDSUSERDllExport extern void 
DDSTestMessagePluginSupport_print_data(
    const DDSTestMessage *sample,
    const char *desc,
    unsigned int indent);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
DDSTestMessagePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
DDSTestMessagePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
DDSTestMessagePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
DDSTestMessagePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
DDSTestMessagePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    DDSTestMessage *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
DDSTestMessagePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    DDSTestMessage *out,
    const DDSTestMessage *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool
DDSTestMessagePlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const DDSTestMessage *sample,
    ::dds::core::policy::DataRepresentationId representation
    = ::dds::core::policy::DataRepresentation::xcdr()); 

NDDSUSERDllExport extern RTIBool 
DDSTestMessagePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    DDSTestMessage **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *cdrStream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
DDSTestMessagePlugin_deserialize_from_cdr_buffer(
    DDSTestMessage *sample,
    const char * buffer,
    unsigned int length);    

NDDSUSERDllExport extern unsigned int 
DDSTestMessagePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
DDSTestMessagePlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
DDSTestMessagePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
DDSTestMessagePlugin_get_serialized_key_max_size_for_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
DDSTestMessagePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    DDSTestMessage ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *cdrStream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
DDSTestMessagePlugin_new(void);

NDDSUSERDllExport extern void
DDSTestMessagePlugin_delete(struct PRESTypePlugin *);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* DDS_testPlugin_1934069328_h */

