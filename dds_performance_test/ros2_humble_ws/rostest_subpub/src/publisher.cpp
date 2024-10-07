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

using namespace std::chrono_literals;
using timeval = struct timeval;

static const uint32_t USEC_to_NANOSEC = 1000UL;
static const uint32_t SEC_to_NANOSEC = 1000000000UL;


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
  }

  void RosPublisher::publish_msg() {
    auto timestamp = getDDSTimeofday();
    RosPublisher::count_p++;
    auto message_a = rostest_msgs::msg::DdsTestMessage();
    message_a.msg = "UR5_" + std::to_string(RosPublisher::count_p);
    message_a.timestamp = timestamp.tv_sec*SEC_to_NANOSEC + timestamp.tv_usec*USEC_to_NANOSEC;
    RCLCPP_INFO(this->get_logger(), "Publishing message: '%s'", message_a.msg.c_str());
    publisher_msg->publish(message_a);
  }

} // namespace publish
