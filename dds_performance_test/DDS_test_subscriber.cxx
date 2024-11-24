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

#include <algorithm>
#include <iostream>

#include <dds/sub/ddssub.hpp>
#include <dds/pub/ddspub.hpp>
#include <dds/core/ddscore.hpp>
#include <rti/config/Logger.hpp>  // for logging
// Or simply include <dds/dds.hpp> 
#include "application.hpp"  // Argument parsing
#include "DDS_test.hpp"

#include <dds/core/Time.hpp>
#include <sys/time.h>

// write data to file
#include <fstream>
#include <sstream>


using namespace application;
using Time = dds::core::Time;

static const DDS_UnsignedLong USEC_to_NANOSEC = 1000UL;
static const DDS_UnsignedLong SEC_to_NANOSEC = 1000000000UL;
static const double MSEC_to_NANOSEC = 1000000UL;

int writeFile(std::string msg, uint8_t number_node) {
    std::ofstream myfile;
    myfile.open ("DDS_test.txt"+std::to_string(number_node), std::ios::app);
    myfile << msg;
    myfile.close();
    return 0;
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

unsigned int process_data(dds::sub::DataReader<DDSTestMessage>& reader, 
                          dds::pub::DataWriter<DDSTestMessage>& writer,
                          u_int8_t number_node)
{
    // Take all samples.  Samples are loaned to application, loan is
    // returned when LoanedSamples destructor called.
    
    unsigned int samples_read = 0;
    dds::sub::LoanedSamples<DDSTestMessage> samples = reader.take();
    auto time = getDDSTimeofday();
    DDSTestMessage sample_w;

    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            samples_read++;
            DDS_UnsignedLong preTime = sample.data().timestamp();
            DDS_UnsignedLong curTime = time.nanosec()+time.sec()*SEC_to_NANOSEC;

            std::stringstream ss;
            ss << "sec, " << time.sec() << ",nano, " \
                << time.nanosec() << ",diff. ms," \
                << std::to_string((curTime - preTime)/MSEC_to_NANOSEC) << "\n";
            writeFile(ss.str(), number_node);

            sample_w.timestamp(curTime);
            sample_w.msg(sample.data().msg());
            writer.write(sample_w);
        }
    }

    return samples_read;
}


void run_example(unsigned int domain_id, 
                 unsigned int sample_count, 
                 const std::string topic_write, 
                 const std::string topic_read,
                 const uint8_t number_node,
                 const u_int32_t hertz)
{
    // A DomainParticipant allows an application to begin communicating in
    // a DDS domain. Typically there is one DomainParticipant per application.
    // Create a DomainParticipant with default Qos
    dds::core::QosProvider qos_provider("test_qos_file.xml");
    dds::domain::DomainParticipant participant(domain_id, 
                                               qos_provider.participant_qos(
                                               "DDSTest_Library::hello_world_Profile"));

    // A Topic has a name and a datatype. Create a Topic named
    // "HelloWorld Topic" with type HelloWorld
    dds::topic::Topic<DDSTestMessage> topic(participant, topic_read);

    // A Subscriber allows an application to create one or more DataReaders
    // Subscriber QoS is configured in USER_QOS_PROFILES.xml
    dds::sub::Subscriber subscriber(participant);

    // This DataReader will read data of type HelloWorld on Topic
    // "HelloWorld Topic". DataReader QoS is configured in
    // USER_QOS_PROFILES.xml
    dds::sub::DataReader<DDSTestMessage> reader(subscriber, topic);

    dds::topic::Topic<DDSTestMessage> topic2(participant, topic_write);
    dds::pub::Publisher publisher(participant);
    dds::pub::DataWriter<DDSTestMessage> writer(publisher, topic2);


    // Obtain the DataReader's Status Condition
    dds::core::cond::StatusCondition status_condition(reader);

    // Enable the 'data available' status.
    status_condition.enabled_statuses(
            dds::core::status::StatusMask::data_available());

    // Associate a handler with the status condition. This will run when the
    // condition is triggered, in the context of the dispatch call (see below)
    unsigned int samples_read = 0;
    status_condition.extensions().handler([&reader, &samples_read, &writer, number_node]() {
        samples_read += process_data(reader, writer, number_node);
    });

    // Create a WaitSet and attach the StatusCondition
    dds::core::cond::WaitSet waitset;
    waitset += status_condition;

    while (!shutdown_requested && samples_read < sample_count) {
        // Dispatch will call the handlers associated to the WaitSet conditions
        // when they activate
        std::cout << "DDS_test subscriber sleeping for 4 sec..."
                  << std::endl;

        waitset.dispatch(dds::core::Duration(1/hertz));  // Wait up to 4s each time
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
                    arguments.number_node,
                    arguments.hertz);
    } catch (const std::exception& ex) {
        // All DDS exceptions inherit from std::exception
        std::cerr << "Exception in run_example(): " << ex.what()
                  << std::endl;
        return EXIT_FAILURE;
    }

    // Releases the memory used by the participant factory.  Optional at
    // application shutdown
    dds::domain::DomainParticipant::finalize_participant_factory();

    return EXIT_SUCCESS;
}
