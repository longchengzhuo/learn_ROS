#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Talker: public rclcpp::Node
{
public:
  Talker():Node("talker_node_cpp"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("chartter", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&Talker::on_timer, this));
  }

private:
  void on_timer()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello world!" + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "发布的消息： '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[])
{

  rclcpp::init(argc, argv);
  spin(std::make_shared<Talker>());
  rclcpp::shutdown();

  return 0;
}