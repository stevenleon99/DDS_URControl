cmake_minimum_required(VERSION 3.8)
project(rostest_subpub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rostest_msgs REQUIRED)

include_directories(include)
add_library(subpub SHARED src/publisher.cpp src/subscriber.cpp)
ament_target_dependencies(subpub rostest_msgs rclcpp)

add_executable(pub src/publisher_node.cpp)
target_link_libraries(pub subpub)
ament_target_dependencies(pub rclcpp)

add_executable(sub src/subscriber_node.cpp)
target_link_libraries(sub subpub)
ament_target_dependencies(sub rclcpp)

install( TARGETS subpub LIBRARY DESTINATION lib)
install( TARGETS pub sub DESTINATION lib/${PROJECT_NAME})

ament_package()
