/*
 * Created on Sun Jan 28 2024 23:40:38
 *
 * Author by Steve Liu
 *
 * Discription: called each time publisher publishes its messages
 *              callback to print the message on the screen
 *              in one of the callbacks add a five seconds pause after print
 *              use rclcpp to implement pause
 */

#include "rostest_subpub/subscriber.hpp"
#include <sys/time.h>


using std::placeholders::_1;
using timeval = struct timeval;

static const uint32_t USEC_to_NANOSEC = 1000UL;
static const uint32_t SEC_to_NANOSEC = 1000000000UL;
static const uint32_t MSEC_to_NANOSEC = 1000000UL;


namespace subscribe
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

  MinimalSubscriber_slow::MinimalSubscriber_slow(): Node("minimal_subscriber_slow")
  {
    subscription_a = this->create_subscription<rostest_msgs::msg::Angle>(
      "angle", 10, std::bind(&MinimalSubscriber_slow::topic_callback_agl, this, _1));
  }

   void MinimalSubscriber_slow::topic_callback_agl(const rostest_msgs::msg::Angle & message) const
  {
    auto timeval = getDDSTimeofday();
    uint64_t timestamp = timeval.tv_sec*SEC_to_NANOSEC + timeval.tv_usec*USEC_to_NANOSEC;
    RCLCPP_INFO(this->get_logger(), "I heard angle: '%s', roll: %f, yall:%f, pitch:%f", message.name.c_str(),message.roll, message.yaw, message.pitch);
    RCLCPP_INFO(this->get_logger(), "I heard timestamp diff: %f", (timestamp-message.timestamp)/MSEC_to_NANOSEC);
    // sleep(5);
  }
  
} // namespace subscriber