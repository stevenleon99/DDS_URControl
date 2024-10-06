#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rostest_msgs/msg/angle.hpp"

using std::placeholders::_1;

namespace subscribe
{
    class MinimalSubscriber_slow : public rclcpp::Node
    {
    public:
        MinimalSubscriber_slow();

    private:
        void topic_callback_agl(const rostest_msgs::msg::Angle & message) const;
        rclcpp::Subscription<rostest_msgs::msg::Angle>::SharedPtr subscription_a;
    };
        
} // namespace subscribe

#endif