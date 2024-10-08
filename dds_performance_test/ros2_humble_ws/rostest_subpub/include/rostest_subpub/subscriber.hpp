#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rostest_msgs/msg/dds_test_message.hpp"

using std::placeholders::_1;

namespace subscribe
{
    class RosSubscriber : public rclcpp::Node
    {
    public:
        RosSubscriber(std::string subscriberName, uint8_t node_number, std::string topicName, std::string topiName_pub);

    private:
        void topic_callback_msg(const rostest_msgs::msg::DdsTestMessage & message) const;
        rclcpp::Subscription<rostest_msgs::msg::DdsTestMessage>::SharedPtr subscription_msg;

        rclcpp::Publisher<rostest_msgs::msg::DdsTestMessage>::SharedPtr publisher_msg;
        void publish_msg();

        uint8_t node_number;
    };
        
} // namespace subscribe

#endif