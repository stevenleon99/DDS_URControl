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
#include <csignal>

bool shutdown_requested = false;

inline void stop_handler(int)
{
    shutdown_requested = true;
    std::cout << "preparing to shut down..." << std::endl;
}

inline void setup_signal_handlers()
{
    signal(SIGINT, stop_handler);
    signal(SIGTERM, stop_handler);
}

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    publish::RosPublisher publisher(argv[1], argv[4]);
    rclcpp::Rate rate_1(atoi(argv[5]));
    
    setup_signal_handlers();
    
    while(rclcpp::ok()){
        publisher.publish_msg();
        rate_1.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
