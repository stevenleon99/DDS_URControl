/*
 * Created on Sun Jan 28 2024 23:35:03
 *
 * Author by Steve Liu
 *
 * Discription: contain main function,
 *              instantiate a publisher and have it publish msg.
 *              one(1) second pause between each iteration
 *              use ros functions from rclcpp to implement the pause
 */

#include "rostest_subpub/publisher.hpp"
#include "rclcpp/rclcpp.hpp"


int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    
    publish::RosPublisher publisher("publish_node", "ur5");
    rclcpp::Rate rate_1(1);
    

    while(rclcpp::ok()){
        publisher.publish_msg();
        rate_1.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
