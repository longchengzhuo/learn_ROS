#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class Listener : public rclcpp::Node
{
public:
    Listener() : Node("listener_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(), "订阅方创建!");
        subcription_ = this->create_subscription<std_msgs::msg::String>("chartter", 10, std::bind(&Listener::do_cb, this, std::placeholders::_1));
    }

private:
    void do_cb(const std_msgs::msg::String &msg)
    {
        RCLCPP_INFO(this->get_logger(), "订阅到的消息为:%s", msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subcription_;
};

int main(int argc, char const *argv[])
{

    rclcpp::init(argc, argv);
    spin(std::make_shared<Listener>());
    rclcpp::shutdown();

    return 0;
}