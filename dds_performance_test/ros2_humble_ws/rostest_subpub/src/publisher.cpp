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

  MinimalPublisher::MinimalPublisher()
  : Node("minimal_publisher"), count_p(0), count_a(0)
  {
    publisher_agl = this->create_publisher<rostest_msgs::msg::Angle>("angle", 10);
  }

  void MinimalPublisher::publish_agl(std::string name, double roll, double pitch, double yaw) const {
    auto timestamp = getDDSTimeofday();
    auto message_a = rostest_msgs::msg::Angle();
    message_a.name = name;
    message_a.pitch = pitch;
    message_a.roll = roll;
    message_a.yaw = yaw;
    message_a.timestamp = timestamp.tv_sec*SEC_to_NANOSEC + timestamp.tv_usec*USEC_to_NANOSEC;
    RCLCPP_INFO(this->get_logger(), "Publishing Angle: '%s', roll: %f, yall:%f, pitch:%f", message_a.name.c_str(),message_a.roll, message_a.yaw, message_a.pitch);
    publisher_agl->publish(message_a);
  }

} // namespace publish
