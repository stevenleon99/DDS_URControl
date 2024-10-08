/*
 * Created on Tue Jan 30 2024 21:48:21
 *
 * Author by Steve Liu
 *
 * Discription: instantiaition of publish two messages. One is point message and 
 * another one is angle message 
 */

#include "rostest_subpub/publisher.hpp"
#include <sys/time.h>

#include <fstream>
#include <sstream>


using namespace std::chrono_literals;
using timeval = struct timeval;

static const uint32_t USEC_to_NANOSEC = 1000UL;
static const uint32_t SEC_to_NANOSEC = 1000000000UL;


std::string readFile(){

    std::ifstream file("/home/steve/rticonnextdds-getting-started/DDS_URControl/dds_performance_test/resource/128b_test.txt");  // Open the file in read mode

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

namespace publish
{
  inline timeval getDDSTimeofday() {
    
    timeval tv;

    // Check if gettimeofday is successful
    if (gettimeofday(&tv, NULL) != 0) {
        // Return a zero time if gettimeofday fails (can also use DDS_TIME_ZERO if defined)
        return tv;
    }
    std::cout << "get time is: " << tv.tv_sec << " " << tv.tv_usec << std::endl;

    return tv;
  }

  RosPublisher::RosPublisher(std::string publisherName, std::string topicName)
  : Node(publisherName), count_p(0), count_a(0)
  {
    publisher_msg = this->create_publisher<rostest_msgs::msg::DdsTestMessage>(topicName, 1);
    RosPublisher::File = readFile();
  }

  void RosPublisher::publish_msg() {
    auto timestamp = getDDSTimeofday();
    RosPublisher::count_p++;
    auto message_pub = rostest_msgs::msg::DdsTestMessage();
    // message_pub.msg = "UR5_" + std::to_string(RosPublisher::count_p);
    message_pub.msg = RosPublisher::File;
    message_pub.timestamp = timestamp.tv_sec*SEC_to_NANOSEC + timestamp.tv_usec*USEC_to_NANOSEC;
    // RCLCPP_INFO(this->get_logger(), "Publishing message: '%s'", message_pub.msg.c_str());
    RCLCPP_INFO(this->get_logger(), "Publishing message...");
    publisher_msg->publish(message_pub);
  }

} // namespace publish
