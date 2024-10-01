/*
 * (c) Copyright, Real-Time Innovations, 2020.  All rights reserved.
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS. Licensee may
 * redistribute copies of the software provided that all such copies are subject
 * to this license. The software is provided "as is", with no warranty of any
 * type, including any warranty for fitness for any purpose. RTI is under no
 * obligation to maintain or support the software. RTI shall not be liable for
 * any incidental or consequential damages arising out of the use or inability
 * to use the software.
 */

#include <iostream>

#include <dds/pub/ddspub.hpp>
#include <rti/util/util.hpp>  // for sleep()
#include <rti/config/Logger.hpp>  // for logging
// Or simply include <dds/dds.hpp> 

#include "URController.hpp"
#include "application.hpp"  // Argument parsing


#include "../mouse_movement/captureMouse.hpp"


using namespace application;


void run_example(unsigned int domain_id, unsigned int sample_count)
{
    // Loads the QoS from the qos_profiles.xml file. 
    dds::core::QosProvider qos_provider("../dds/USER_QOS_PROFILES.xml");
    // A DomainParticipant allows an application to begin communicating in
    // a DDS domain. Typically there is one DomainParticipant per application.
    // DomainParticipant QoS is configured in USER_QOS_PROFILES.xml
    dds::domain::DomainParticipant participant(domain_id, 
                                               qos_provider.participant_qos(
                                               "UR5Controller_Library::UR5Controller_Profile"));
    // check participant qos type
    // auto qos = participant.qos();
    // std::cout << "participant qos type: " << to_string(qos) << std::endl;

    // A Topic has a name and a datatype. Create a Topic named
    // "URController_Topic" with type URController
    dds::topic::Topic<DesireJoint> topic(participant, "URController topic");

    // A Publisher allows an application to create one or more DataWriters
    // Publisher QoS is configured in USER_QOS_PROFILES.xml
    dds::pub::Publisher publisher(participant);

    // This DataWriter will write data on Topic "URController topic"
    // DataWriter QoS is configured in USER_QOS_PROFILES.xml
    dds::pub::DataWriter<DesireJoint> writer(publisher, topic);

    // Create data sample for writing
    DesireJoint sample;


    for (unsigned int count = 0;
         !shutdown_requested && count < sample_count;
         count++) {
        
        vector<double> xy = trackMousePos();
        // Modify the data to be written here
        sample.oriThetaArr({0, 1.57, 0, 0, -1.57, 0});
        sample.desiredPosArr({xy[0], xy[1], -0.2, 1.56, 1.48, 2.93});

        std::cout << "Writing desiredJoint, count " << count << std::endl;

        writer.write(sample);

        rti::util::sleep(dds::core::Duration(4));
    }

}



int main(int argc, char *argv[])
{
    // Parse arguments and handle control-C
    auto arguments = parse_arguments(argc, argv);
    if (arguments.parse_result == ParseReturn::exit) {
        return EXIT_SUCCESS;
    } else if (arguments.parse_result == ParseReturn::failure) {
        return EXIT_FAILURE;
    }
    setup_signal_handlers();

    // Sets Connext verbosity to help debugging
    rti::config::Logger::instance().verbosity(arguments.verbosity);

    try {
        run_example(arguments.domain_id, arguments.sample_count);
    } catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in run_example(): " << ex.what()
                  << std::endl;
        return EXIT_FAILURE;
    }

    // Releases the memory used by the participant factory.  Optional at
    // application shutdown
    dds::domain::DomainParticipant::finalize_participant_factory();

    return EXIT_SUCCESS;
}
