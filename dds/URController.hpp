

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from URController.idl
using RTI Code Generator (rtiddsgen) version 4.3.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef URController_457231758_hpp
#define URController_457231758_hpp

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

class NDDSUSERDllExport DesireJoint {
  public:

    DesireJoint();

    DesireJoint(const ::dds::core::array< double, 6L>& oriThetaArr_,const ::dds::core::array< double, 6L>& desiredPosArr_);

    ::dds::core::array< double, 6L>& oriThetaArr() noexcept {
        return m_oriThetaArr_;
    }

    const ::dds::core::array< double, 6L>& oriThetaArr() const noexcept {
        return m_oriThetaArr_;
    }

    void oriThetaArr(const ::dds::core::array< double, 6L>& value) {

        m_oriThetaArr_ = value;
    }

    void oriThetaArr(::dds::core::array< double, 6L>&& value) {
        m_oriThetaArr_ = std::move(value);
    }
    ::dds::core::array< double, 6L>& desiredPosArr() noexcept {
        return m_desiredPosArr_;
    }

    const ::dds::core::array< double, 6L>& desiredPosArr() const noexcept {
        return m_desiredPosArr_;
    }

    void desiredPosArr(const ::dds::core::array< double, 6L>& value) {

        m_desiredPosArr_ = value;
    }

    void desiredPosArr(::dds::core::array< double, 6L>&& value) {
        m_desiredPosArr_ = std::move(value);
    }
    bool operator == (const DesireJoint& other_) const;
    bool operator != (const DesireJoint& other_) const;

    void swap(DesireJoint& other_) noexcept ;

  private:

    ::dds::core::array< double, 6L> m_oriThetaArr_ {};
    ::dds::core::array< double, 6L> m_desiredPosArr_ {};

};

inline void swap(DesireJoint& a, DesireJoint& b)  noexcept 
{
    a.swap(b);
}

NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const DesireJoint& sample);

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
        struct topic_type_name< ::DesireJoint > {
            NDDSUSERDllExport static std::string value() {
                return "DesireJoint";
            }
        };

        template<>
        struct is_topic_type< ::DesireJoint > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::DesireJoint > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::DesireJoint& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::DesireJoint& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::DesireJoint& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::DesireJoint& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
    }
}

namespace rti { 
    namespace topic {

        template<>
        struct dynamic_type< ::DesireJoint > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::DesireJoint > {
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

#endif // URController_457231758_hpp

