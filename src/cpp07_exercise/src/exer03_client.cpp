#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/distance.hpp"

using base_interfaces_demo::srv::Distance;
using namespace std::chrono_literals;


class Exer03Client : public rclcpp::Node
{
public:
    Exer03Client() : Node("exer03_client_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"case03 client create!");
        client_ = this->create_client<Distance>("distance");
    }
    bool connect_server() {
        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                return false;
            }
            RCLCPP_INFO(this->get_logger(),"CONNECTING...");
        }
        return true;
    }
    rclcpp::Client<Distance>::FutureAndRequestId send_goal(float x,float y,float theta) {
        auto request = std::make_shared<Distance::Request>();
        request->x = x;
        request->y = y;
        request->theta = theta;

        return client_->async_send_request(request);
    }
private:
    rclcpp::Client<Distance>::SharedPtr client_;
};

int main(int argc, char *argv[])
{
    if (argc != 5) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"please provide x,y,theta");
        return 1;
    }
    float goal_x = atof(argv[1]);
    float goal_y = atof(argv[2]);
    float goal_theta = atof(argv[3]);

    // Initialize ROS 2
    rclcpp::init(argc, argv);

    // Create and spin the node
    auto client = std::make_shared<Exer03Client>();
    bool flag = client->connect_server();
    if (!flag) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"connect fail");
        return 1;
    }
    auto future = client->send_goal(goal_x,goal_y,goal_theta);
    if (rclcpp::spin_until_future_complete(client,future) == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(client->get_logger(),"distance:%.2f",future.get()->distance);

    }else {
        RCLCPP_INFO(client->get_logger(),"sevice fail");

    }
    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}