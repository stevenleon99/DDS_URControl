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
        RosSubscriber(std::string subscriberName, std::string topicName);

    private:
        void topic_callback_msg(const rostest_msgs::msg::DdsTestMessage & message) const;
        rclcpp::Subscription<rostest_msgs::msg::DdsTestMessage>::SharedPtr subscription_msg;
    };
        
} // namespace subscribe

#endif