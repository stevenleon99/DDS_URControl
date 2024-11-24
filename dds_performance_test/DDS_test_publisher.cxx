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
#include "application.hpp"  // Argument parsing
#include "DDS_test.hpp"

#include <dds/core/Time.hpp>
#include <sys/time.h>

#include <fstream>
#include <sstream>

using namespace application;
using Time = dds::core::Time;

static const DDS_UnsignedLong USEC_to_NANOSEC = 1000UL;
static const DDS_UnsignedLong SEC_to_NANOSEC = 1000000000UL;

std::string readFile(){

    std::ifstream file("../resource/128b_test.txt");  // Open the file in read mode

    if (!file.is_open()) {  // Check if the file opened successfully
        std::cerr << "Unable to open file";
        return "";
    }

    std::stringstream buffer;  // Create a stringstream to hold file contents
    buffer << file.rdbuf();    // Read the whole file into the stringstream

    std::string fileContents = buffer.str();  // Convert the stringstream to a string

    file.close();  // Close the file
    return fileContents;

}

inline Time getDDSTimeofday() {
    
    struct timeval tv;

    // Check if gettimeofday is successful
    if (gettimeofday(&tv, NULL) != 0) {
        // Return a zero time if gettimeofday fails (can also use DDS_TIME_ZERO if defined)
        return Time(0, 0);
    }

    // Convert timeval to DDS time
    auto crtTime = Time(tv.tv_sec, tv.tv_usec * USEC_to_NANOSEC);

    return crtTime;
}


void run_example(unsigned int domain_id, 
    unsigned int sample_count, 
    const std::string topic_write, 
    const std::string topic_read,
    const uint32_t hertz)
{
    // A DomainParticipant allows an application to begin communicating in
    // a DDS domain. Typically there is one DomainParticipant per application.
    // DomainParticipant QoS is configured in USER_QOS_PROFILES.xml
    dds::core::QosProvider qos_provider("test_qos_file.xml");
    dds::domain::DomainParticipant participant(domain_id, 
                                               qos_provider.participant_qos(
                                               "DDSTest_Library::hello_world_Profile"));
    // A Topic has a name and a datatype. Create a Topic named
    // "HelloWorld Topic" with type HelloWorld
    dds::topic::Topic<DDSTestMessage> topic(participant, topic_write);

    // A Publisher allows an application to create one or more DataWriters
    // Publisher QoS is configured in USER_QOS_PROFILES.xml
    dds::pub::Publisher publisher(participant);

    // This DataWriter will write data on Topic "HelloWorld Topic"
    // DataWriter QoS is configured in USER_QOS_PROFILES.xml
    dds::pub::DataWriter<DDSTestMessage> writer(publisher, topic);

    // Create data sample for writing
    DDSTestMessage sample;


    for (unsigned int count = 0;
         !shutdown_requested && count < sample_count;
         count++) {
        
        std::cout << "Writing HelloWorld, count " << count << std::endl;
        auto time = getDDSTimeofday();
        std::cout << "sec: " << time.sec() << " nano: " << time.nanosec() << std::endl;

        sample.timestamp(time.nanosec()+time.sec()*SEC_to_NANOSEC);
        // sample.msg("Hello world! " + std::to_string(time.nanosec()));
        sample.msg(readFile());
        writer.write(sample);
        
        rti::util::sleep(dds::core::Duration(1/hertz));
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
        run_example(arguments.domain_id, 
                    arguments.sample_count, 
                    arguments.topic_write, 
                    arguments.topic_read, 
                    arguments.hertz);
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
