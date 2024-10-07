#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include "rclcpp/rclcpp.hpp"
#include "rostest_msgs/msg/dds_test_message.hpp"

namespace publish
{
    class RosPublisher : public rclcpp::Node
    {
    public:
        size_t count_p;
        size_t count_a;
        RosPublisher(std::string publisherName, std::string topicName);
        void publish_msg();

    private:
        // void timer_callback();
        // rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<rostest_msgs::msg::DdsTestMessage>::SharedPtr publisher_msg;
    };
    
} // namespace publisher


#endif

