#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include "rclcpp/rclcpp.hpp"
#include "rostest_msgs/msg/angle.hpp"

namespace publish
{
    class MinimalPublisher : public rclcpp::Node
    {
    public:
        size_t count_p;
        size_t count_a;
        MinimalPublisher();
        void publish_agl(std::string name, double roll, double pitch, double yaw) const;

    private:
        // void timer_callback();
        // rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<rostest_msgs::msg::Angle>::SharedPtr publisher_agl;
    };
    
} // namespace publisher


#endif

