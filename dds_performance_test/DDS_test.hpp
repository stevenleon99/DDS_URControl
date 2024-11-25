

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from DDS_test.idl
using RTI Code Generator (rtiddsgen) version 4.3.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef DDS_test_1934069347_hpp
#define DDS_test_1934069347_hpp

#include <iosfwd>

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif

#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/External.hpp"
#include "rti/core/LongDouble.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/core/array.hpp"
#include "rti/topic/TopicTraits.hpp"

#include "omg/types/string_view.hpp"

#include "rti/core/BoundedSequence.hpp"
#include "dds/core/Optional.hpp"

#ifndef NDDS_STANDALONE_TYPE
#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

class NDDSUSERDllExport DDSTestMessage {
  public:

    DDSTestMessage();

    DDSTestMessage(uint64_t count_,double timestamp_,const std::string& msg_);

    uint64_t& count() noexcept {
        return m_count_;
    }

    const uint64_t& count() const noexcept {
        return m_count_;
    }

    void count(uint64_t value) {

        m_count_ = value;
    }

    double& timestamp() noexcept {
        return m_timestamp_;
    }

    const double& timestamp() const noexcept {
        return m_timestamp_;
    }

    void timestamp(double value) {

        m_timestamp_ = value;
    }

    std::string& msg() noexcept {
        return m_msg_;
    }

    const std::string& msg() const noexcept {
        return m_msg_;
    }

    void msg(const std::string& value) {

        m_msg_ = value;
    }

    void msg(std::string&& value) {
        m_msg_ = std::move(value);
    }
    bool operator == (const DDSTestMessage& other_) const;
    bool operator != (const DDSTestMessage& other_) const;

    void swap(DDSTestMessage& other_) noexcept ;

  private:

    uint64_t m_count_;
    double m_timestamp_;
    std::string m_msg_;

};

inline void swap(DDSTestMessage& a, DDSTestMessage& b)  noexcept 
{
    a.swap(b);
}

NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const DDSTestMessage& sample);

#ifdef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace topic {
    }
}
#else

namespace rti {
    namespace flat {
        namespace topic {
        }
    }
}
namespace dds {
    namespace topic {

        template<>
        struct topic_type_name< ::DDSTestMessage > {
            NDDSUSERDllExport static std::string value() {
                return "DDSTestMessage";
            }
        };

        template<>
        struct is_topic_type< ::DDSTestMessage > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::DDSTestMessage > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::DDSTestMessage& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::DDSTestMessage& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::DDSTestMessage& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::DDSTestMessage& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
    }
}

namespace rti { 
    namespace topic {

        template<>
        struct dynamic_type< ::DDSTestMessage > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::DDSTestMessage > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

    }
}

#endif // NDDS_STANDALONE_TYPE
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif // DDS_test_1934069347_hpp

