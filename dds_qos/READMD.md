**basic qos xml**
<dds xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:noNamespaceSchemaLocation="https://community.rti.com/schema/current/rti_dds_qos_profiles.xsd">
    <!--
        QoS Library containing the QoS profile used in this example.
        A QoS library is a named set of QoS profiles.
    -->
    <qos_library name="URController_Library">
        <!-- 
            QoS profile: <used to configure reliable communication between the
            DataWriter and DataReader created in the example code. >
            base_name: <Communication is reliable because this profile inherits from
            the built-in profile "BuiltinQosLib::Generic.StrictReliable">
            is_default_qos: <These QoS profiles will be used as the default, as long as this
            file is in the working directory when running the example.>
        -->
        <qos_profile name="URController_Profile" 
                     base_name="BuiltinQosLib::Generic.StrictReliable"
                     is_default_qos="true">
            <!-- QoS specified to override the QoS in the base profile.
                 Configures the DataWriter in the example code. -->
            <datawriter_qos>
                <publication_name>
                    <name>URControllerDataWriter</name>
                </publication_name>
            </datawriter_qos>
            <!-- QoS specified to override the QoS in the base profile. 
                 Configures the DataReader in the example code. -->
            <datareader_qos>
                <subscription_name>
                    <name>URControllerDataReader</name>
                </subscription_name>
            </datareader_qos>
            <!-- QoS specified to override the QoS in the base profile. 
                 Configures the DomainParticipant in the example code. -->
            <domain_participant_qos>
                <!--
                The participant name, if it is set, will be displayed in the
                RTI tools, making it easier for you to tell one
                application from another when you're debugging.
                -->
                <participant_name>
                    <name>URControllerParticipant</name>
                </participant_name>
            </domain_participant_qos>
        </qos_profile>
    </qos_library>
</dds>


- *einstein_custom_qos_profile_library.xml.in* (define different qos profiles, with general element and properties)
  - define one datawrite_qos and datareader_qos
  - build-in base qos profile
    - BuiltinQosLib::Generic.StrictReliable

- *[sub-system-name]_participate_library.xml* (specific subsystem defined by different domains)
  - domain_ref is defined in [einstein_domain_library.xml]
  - domain_participant
    - a series of [data-reader]
      - has a topic_ref in [einstein_domain_library.xml]
      - define datareader_qos in qos_library [einstein_custom_qos_profile_library.xml.in]
      - and other properties
    - a series of [data_writer]
      - has a topic_ref in [einstein_domain_library.xml]
      - define datawriter_qos in qos_library [einstein_custom_qos_profile_library.xml.in]
      - and other properties
    - one participant 
      - define participant_qos in qos_library [einstein_custom_qos_profile_library.xml.in]
      - and other properties
  
- *einstein_domain_library.xml* (define different domain with topics and datatypes)
  - register a series of [datatype] used within domains
  - define a series of [topic] used within domains
    - topic_qos: refer to qos profile in qos_library [einstein_custom_qos_profile_library.xml.in]

**relationship**
in the specific subsystem xml, there are different domain participants divided by different domains; 
Each domain will have only one participant which will be used to create datareader and datawriter, and
many datawriters and datareaders; datawriter and datareader will be correlated with topic_ref; the
correlated datawriter_qos, datareader_qos and topic_qos should be the same.