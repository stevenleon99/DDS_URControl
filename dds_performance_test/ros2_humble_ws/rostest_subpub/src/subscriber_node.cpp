/*
 * Created on Tue Jan 30 2024 21:47:50
 *
 * Author by Steve Liu
 *
 * Discription: subscriber main function
 */


#include "rclcpp/rclcpp.hpp"
#include "rostest_subpub/subscriber.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init( argc, argv );
  auto node_s = std::make_shared<subscribe::RosSubscriber>("subscriber_node", "ur5");
  rclcpp::spin( node_s );
  rclcpp::shutdown();
  return 0;
}
