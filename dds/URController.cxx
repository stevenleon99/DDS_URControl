

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from URController.idl
using RTI Code Generator (rtiddsgen) version 4.3.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <iosfwd>
#include <iomanip>

#ifndef NDDS_STANDALONE_TYPE
#include "rti/topic/cdr/Serialization.hpp"
#include "URControllerPlugin.hpp"
#else
#include "rti/topic/cdr/SerializationHelpers.hpp"
#endif

#include "URController.hpp"

#include <rti/util/ostream_operators.hpp>

// ---- DesireJoint: 

DesireJoint::DesireJoint()  {

}   

DesireJoint::DesireJoint (const ::dds::core::array< double, 6L>& oriThetaArr_,const ::dds::core::array< double, 6L>& desiredPosArr_):
    m_oriThetaArr_(oriThetaArr_), 
    m_desiredPosArr_(desiredPosArr_) {
}

void DesireJoint::swap(DesireJoint& other_)  noexcept 
{
    using std::swap;
    swap(m_oriThetaArr_, other_.m_oriThetaArr_);
    swap(m_desiredPosArr_, other_.m_desiredPosArr_);
}  

bool DesireJoint::operator == (const DesireJoint& other_) const {
    if (m_oriThetaArr_ != other_.m_oriThetaArr_) {
        return false;
    }
    if (m_desiredPosArr_ != other_.m_desiredPosArr_) {
        return false;
    }
    return true;
}

bool DesireJoint::operator != (const DesireJoint& other_) const {
    return !this->operator ==(other_);
}

std::ostream& operator << (std::ostream& o,const DesireJoint& sample)
{
    ::rti::util::StreamFlagSaver flag_saver (o);
    o <<"[";
    o << "oriThetaArr: " << sample.oriThetaArr ()<<", ";
    o << "desiredPosArr: " << sample.desiredPosArr ();
    o <<"]";
    return o;
}

#ifdef NDDS_STANDALONE_TYPE
namespace rti {
    namespace topic {
    }
}

#else
// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        template<>
        struct native_type_code< ::DesireJoint > {
            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode DesireJoint_g_tc_oriThetaArr_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,6L, NULL,NULL);
                static DDS_TypeCode DesireJoint_g_tc_desiredPosArr_array =DDS_INITIALIZE_ARRAY_TYPECODE(1,6L, NULL,NULL);

                static DDS_TypeCode_Member DesireJoint_g_tc_members[2]=
                {

                    {
                        (char *)"oriThetaArr",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"desiredPosArr",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode DesireJoint_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"DesireJoint", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        2, /* Number of members */
                        DesireJoint_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for DesireJoint*/

                if (is_initialized) {
                    return &DesireJoint_g_tc;
                }

                is_initialized = RTI_TRUE;

                DesireJoint_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                DesireJoint_g_tc_oriThetaArr_array._data._typeCode =(RTICdrTypeCode *)&DDS_g_tc_double;
                DesireJoint_g_tc_desiredPosArr_array._data._typeCode =(RTICdrTypeCode *)&DDS_g_tc_double;
                DesireJoint_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& DesireJoint_g_tc_oriThetaArr_array;
                DesireJoint_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)& DesireJoint_g_tc_desiredPosArr_array;

                /* Initialize the values for member annotations. */

                DesireJoint_g_tc._data._sampleAccessInfo = sample_access_info();
                DesireJoint_g_tc._data._typePlugin = type_plugin_info();    

                return &DesireJoint_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static RTIBool is_initialized = RTI_FALSE;

                ::DesireJoint *sample;

                static RTIXCdrMemberAccessInfo DesireJoint_g_memberAccessInfos[2] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo DesireJoint_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized) {
                    return (RTIXCdrSampleAccessInfo*) &DesireJoint_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ::DesireJoint);
                if (sample == NULL) {
                    return NULL;
                }

                DesireJoint_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->oriThetaArr() - (char *)sample);

                DesireJoint_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->desiredPosArr() - (char *)sample);

                DesireJoint_g_sampleAccessInfo.memberAccessInfos = 
                DesireJoint_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::DesireJoint);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        DesireJoint_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        DesireJoint_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                DesireJoint_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                DesireJoint_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::DesireJoint >;

                DesireJoint_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized = RTI_TRUE;
                return (RTIXCdrSampleAccessInfo*) &DesireJoint_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin DesireJoint_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &DesireJoint_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::DesireJoint >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::DesireJoint >::get())));
        }
    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< ::DesireJoint >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::DesireJointPlugin_new,
                ::DesireJointPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::DesireJoint >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::DesireJoint& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = DesireJointPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = DesireJointPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::DesireJoint >::from_cdr_buffer(::DesireJoint& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = DesireJointPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::DesireJoint from cdr buffer");
        }

        void topic_type_support< ::DesireJoint >::reset_sample(::DesireJoint& sample) 
        {
            ::rti::topic::reset_sample(sample.oriThetaArr());
            ::rti::topic::reset_sample(sample.desiredPosArr());
        }

        void topic_type_support< ::DesireJoint >::allocate_sample(::DesireJoint& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.oriThetaArr(),  -1, -1);
            ::rti::topic::allocate_sample(sample.desiredPosArr(),  -1, -1);
        }
    }
}  

#endif // NDDS_STANDALONE_TYPE
