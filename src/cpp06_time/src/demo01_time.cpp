#include "rclcpp/rclcpp.hpp"
using namespace std::chrono_literals;
class MyNode : public rclcpp::Node
{
public:
  MyNode() : Node("time_node_cpp")
  {
    // demo_rate();
    demo_time();
  }

private:
  void demo_time() {
    rclcpp::Time t1(2,500000000L);
    rclcpp::Time right_now = this->now();
    RCLCPP_INFO(this->get_logger(),"s = %.2f, ns = %ld",t1.seconds(),t1.nanoseconds());

  }
  void demo_rate(){
    rclcpp::Rate rate1(500ms);
    rclcpp::Rate rate2(1.0);
    while (rclcpp::ok()) {
      RCLCPP_INFO(this->get_logger(),"------");
      rate1.sleep();
    }
  }
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