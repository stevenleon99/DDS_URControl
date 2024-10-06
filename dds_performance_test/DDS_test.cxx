

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from DDS_test.idl
using RTI Code Generator (rtiddsgen) version 4.3.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <iosfwd>
#include <iomanip>

#ifndef NDDS_STANDALONE_TYPE
#include "rti/topic/cdr/Serialization.hpp"
#include "DDS_testPlugin.hpp"
#else
#include "rti/topic/cdr/SerializationHelpers.hpp"
#endif

#include "DDS_test.hpp"

#include <rti/util/ostream_operators.hpp>

// ---- DDSTestMessage: 

DDSTestMessage::DDSTestMessage() :
    m_timestamp_ (0ull) ,
    m_msg_ ("")  {

}   

DDSTestMessage::DDSTestMessage (uint64_t timestamp_,const std::string& msg_):
    m_timestamp_(timestamp_), 
    m_msg_(msg_) {
}

void DDSTestMessage::swap(DDSTestMessage& other_)  noexcept 
{
    using std::swap;
    swap(m_timestamp_, other_.m_timestamp_);
    swap(m_msg_, other_.m_msg_);
}  

bool DDSTestMessage::operator == (const DDSTestMessage& other_) const {
    if (m_timestamp_ != other_.m_timestamp_) {
        return false;
    }
    if (m_msg_ != other_.m_msg_) {
        return false;
    }
    return true;
}

bool DDSTestMessage::operator != (const DDSTestMessage& other_) const {
    return !this->operator ==(other_);
}

std::ostream& operator << (std::ostream& o,const DDSTestMessage& sample)
{
    ::rti::util::StreamFlagSaver flag_saver (o);
    o <<"[";
    o << "timestamp: " << sample.timestamp ()<<", ";
    o << "msg: " << sample.msg ();
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
        struct native_type_code< ::DDSTestMessage > {
            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode DDSTestMessage_g_tc_msg_string;

                static DDS_TypeCode_Member DDSTestMessage_g_tc_members[2]=
                {

                    {
                        (char *)"timestamp",/* Member name */
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
                        (char *)"msg",/* Member name */
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

                static DDS_TypeCode DDSTestMessage_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"DDSTestMessage", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        2, /* Number of members */
                        DDSTestMessage_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for DDSTestMessage*/

                if (is_initialized) {
                    return &DDSTestMessage_g_tc;
                }

                is_initialized = RTI_TRUE;

                DDSTestMessage_g_tc_msg_string = initialize_string_typecode((500000000L));

                DDSTestMessage_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                DDSTestMessage_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;
                DDSTestMessage_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDSTestMessage_g_tc_msg_string;

                /* Initialize the values for member annotations. */
                DDSTestMessage_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
                DDSTestMessage_g_tc_members[0]._annotations._defaultValue._u.ulong_long_value = 0ull;
                DDSTestMessage_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
                DDSTestMessage_g_tc_members[0]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
                DDSTestMessage_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
                DDSTestMessage_g_tc_members[0]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;
                DDSTestMessage_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                DDSTestMessage_g_tc_members[1]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

                DDSTestMessage_g_tc._data._sampleAccessInfo = sample_access_info();
                DDSTestMessage_g_tc._data._typePlugin = type_plugin_info();    

                return &DDSTestMessage_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static RTIBool is_initialized = RTI_FALSE;

                ::DDSTestMessage *sample;

                static RTIXCdrMemberAccessInfo DDSTestMessage_g_memberAccessInfos[2] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo DDSTestMessage_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized) {
                    return (RTIXCdrSampleAccessInfo*) &DDSTestMessage_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ::DDSTestMessage);
                if (sample == NULL) {
                    return NULL;
                }

                DDSTestMessage_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->timestamp() - (char *)sample);

                DDSTestMessage_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->msg() - (char *)sample);

                DDSTestMessage_g_sampleAccessInfo.memberAccessInfos = 
                DDSTestMessage_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::DDSTestMessage);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        DDSTestMessage_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        DDSTestMessage_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                DDSTestMessage_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                DDSTestMessage_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::DDSTestMessage >;

                DDSTestMessage_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized = RTI_TRUE;
                return (RTIXCdrSampleAccessInfo*) &DDSTestMessage_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin DDSTestMessage_g_typePlugin = 
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

                return &DDSTestMessage_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::DDSTestMessage >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::DDSTestMessage >::get())));
        }
    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< ::DDSTestMessage >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::DDSTestMessagePlugin_new,
                ::DDSTestMessagePlugin_delete);
        }

        std::vector<char>& topic_type_support< ::DDSTestMessage >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::DDSTestMessage& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = DDSTestMessagePlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = DDSTestMessagePlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::DDSTestMessage >::from_cdr_buffer(::DDSTestMessage& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = DDSTestMessagePlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::DDSTestMessage from cdr buffer");
        }

        void topic_type_support< ::DDSTestMessage >::reset_sample(::DDSTestMessage& sample) 
        {
            sample.timestamp(0ull);
            sample.msg("");
        }

        void topic_type_support< ::DDSTestMessage >::allocate_sample(::DDSTestMessage& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.msg(),  -1, 500000000L);
        }
    }
}  

#endif // NDDS_STANDALONE_TYPE
