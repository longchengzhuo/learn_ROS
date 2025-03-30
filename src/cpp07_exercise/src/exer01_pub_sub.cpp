#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;


class Exer01PubSub : public rclcpp::Node
{
public:
  Exer01PubSub() : Node("exer01_pub_sub_node_cpp")
  {
    RCLCPP_INFO(this->get_logger(),"case01 create!");
    pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/t2/turtle1/cmd_vel",10);
    sub_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose",10,std::bind(&Exer01PubSub::pose_cb,this,std::placeholders::_1));
  }
private:
  void pose_cb(const turtlesim::msg::Pose &pose) {
    geometry_msgs::msg::Twist twist;
    twist.linear.x = pose.linear_velocity;
    twist.angular.z = -pose.angular_velocity;
    pub_->publish(twist);

  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
};

int main(int argc, char *argv[])
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);

  // Create and spin the node
  auto node = std::make_shared<Exer01PubSub>();
  rclcpp::spin(node);

  // Shutdown ROS 2
  rclcpp::shutdown();
  return 0;
}