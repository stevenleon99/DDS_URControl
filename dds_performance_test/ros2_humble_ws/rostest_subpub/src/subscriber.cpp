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

  RosSubscriber::RosSubscriber(std::string subscriberName, std::string topicName): Node(subscriberName)
  {
    subscription_msg = this->create_subscription<rostest_msgs::msg::DdsTestMessage>(
      topicName, 10, std::bind(&RosSubscriber::topic_callback_msg, this, _1));
  }

   void RosSubscriber::topic_callback_msg(const rostest_msgs::msg::DdsTestMessage & message) const
  {
    auto timeval = getDDSTimeofday();
    uint64_t timestamp = timeval.tv_sec*SEC_to_NANOSEC + timeval.tv_usec*USEC_to_NANOSEC;
    RCLCPP_INFO(this->get_logger(), "I heard message: '%s'", message.msg.c_str());
    RCLCPP_INFO(this->get_logger(), "I heard timestamp diff: %f", (timestamp-message.timestamp)/MSEC_to_NANOSEC);
    // sleep(5);
  }
  
} // namespace subscriber