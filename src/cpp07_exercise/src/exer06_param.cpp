#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;


class Exer06Param : public rclcpp::Node
{
public:
    Exer06Param() : Node("exer06_param_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"param service create");
        client_ = std::make_shared<rclcpp::SyncParametersClient>(this,"/turtlesim");
    }
    bool connect_server() {
        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"client quit");
                return false;
            }
            RCLCPP_INFO(this->get_logger(),"connecting....");
        }
        return true;
    }
    void update_param() {
        int red = client_->get_parameter<int>("background_r");
        int increase = 1;
        rclcpp::Rate rate(30.0);
        while (rclcpp::ok()) {
            if ((red < 255 && increase) || (red <= 0 && !increase)) {
                red += 5;
                increase = 1;
            }else{
                red -= 5;
                increase = 0;
            }

            client_->set_parameters({rclcpp::Parameter("background_r",red)});
            rate.sleep();
        }
    }
private:
    rclcpp::SyncParametersClient::SharedPtr client_;
};

int main(int argc, char *argv[])
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    // Create and spin the node
    auto client = std::make_shared<Exer06Param>();
    if(!client->connect_server()) {
        return 1;
    }
    client->update_param();
    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}