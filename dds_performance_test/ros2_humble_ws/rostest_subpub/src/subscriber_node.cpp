/*
 * Created on Tue Jan 30 2024 21:47:50
 *
 * Author by Steve Liu
 *
 * Discription: subscriber main function
 */


#include "rclcpp/rclcpp.hpp"
#include "rostest_subpub/subscriber.hpp"
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

int main(int argc, char * argv[])
{
  rclcpp::init( argc, argv );
  auto node_s = std::make_shared<subscribe::RosSubscriber>(argv[1], atoi(argv[2]), argv[3], argv[4]);
  
  setup_signal_handlers();

  rclcpp::spin( node_s );
  rclcpp::shutdown();
  return 0;
}
