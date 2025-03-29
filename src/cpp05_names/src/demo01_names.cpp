#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include "std_msgs/msg/string.hpp"
class MyNode : public rclcpp::Node
{
public:
  MyNode() : Node("mynode_node_cpp","t1_ns")
  {
    //pub_ = this->create_publisher<std_msgs::msg::String>("/global_topic",10);
//    pub_ = this->create_publisher<std_msgs::msg::String>("relative_topic",10);
    pub_ = this->create_publisher<std_msgs::msg::String>("~/private_topic",10);
  }

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
};

int main(int argc, char *argv[])
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);

  // Create and spin the node
  auto node = std::make_shared<MyNode>();
  rclcpp::spin(node);

  // Shutdown ROS 2
  rclcpp::shutdown();
  return 0;
}