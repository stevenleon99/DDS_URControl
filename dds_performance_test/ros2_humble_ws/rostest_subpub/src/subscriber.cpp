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

#include <sstream>
#include <fstream>

using std::placeholders::_1;
using timeval = struct timeval;

static const uint32_t USEC_to_NANOSEC = 1000UL;
static const uint32_t SEC_to_NANOSEC = 1000000000UL;
static const uint32_t MSEC_to_NANOSEC = 1000000UL;


int writeFile(std::string msg, uint8_t number_node) {
    std::ofstream myfile;
    myfile.open ("/home/steve/rticonnextdds-getting-started/DDS_URControl/dds_performance_test/ros2_humble_ws/script/DDS_test.txt"+std::to_string(number_node), std::ios::app);
    myfile << msg;
    myfile.close();
    return 0;
}


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

  RosSubscriber::RosSubscriber(std::string subscriberName, uint8_t node_number, std::string topicName, std::string topicName_pub): 
    Node(subscriberName), node_number(node_number)
  {
    rclcpp::QoS qos_profile(10);
    qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
    RosSubscriber::publisher_msg = this->create_publisher<rostest_msgs::msg::DdsTestMessage>(topicName_pub, qos_profile);
    RosSubscriber::subscription_msg = this->create_subscription<rostest_msgs::msg::DdsTestMessage>(
      topicName, qos_profile, std::bind(&RosSubscriber::topic_callback_msg, this, _1));
  }

   void RosSubscriber::topic_callback_msg(const rostest_msgs::msg::DdsTestMessage & message) const
  {
    auto timeval = getDDSTimeofday();
    uint64_t timestamp = timeval.tv_sec*SEC_to_NANOSEC + timeval.tv_usec*USEC_to_NANOSEC;
    // RCLCPP_INFO(this->get_logger(), "I heard message: '%s'", message.msg.c_str());
    RCLCPP_INFO(this->get_logger(), "I heard timestamp diff: %f", (timestamp-message.timestamp)/MSEC_to_NANOSEC);

    std::stringstream ss;
    ss << "sec, " << timeval.tv_sec << ",us, " \
        << timeval.tv_usec << ",diff. ms," \
        << std::to_string((timestamp-message.timestamp)/MSEC_to_NANOSEC) << "\n";
    writeFile(ss.str(), RosSubscriber::node_number);
    // sleep(5);

    auto message_pub = rostest_msgs::msg::DdsTestMessage();
    message_pub.msg = message.msg;
    message_pub.timestamp = timestamp;

    RCLCPP_INFO(this->get_logger(), "Publishing message...");
    publisher_msg->publish(message_pub);
    

  }
  
} // namespace subscriber