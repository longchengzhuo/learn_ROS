#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "base_interfaces_demo/srv/distance.hpp"

using std::placeholders::_1;
using std::placeholders::_2;
using base_interfaces_demo::srv::Distance;

class Exer02Server : public rclcpp::Node
{
public:
    Exer02Server() : Node("exer02_server_node_cpp"), x(0.0), y(0.0)
    {
        RCLCPP_INFO(this->get_logger(),"case02 server create!");
        sub_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose",10,std::bind(&Exer02Server::pose_cb,this,_1));
        server_ = this->create_service<Distance>("distance",std::bind(&Exer02Server::distance_cb,this,_1,_2));
    }
private:
    float x,y;
    void pose_cb(const turtlesim::msg::Pose::SharedPtr pose) {
        x = pose->x;
        y = pose->y;
    }
    void distance_cb(const Distance::Request::SharedPtr request, Distance::Response::SharedPtr response) {
        float goal_x = request->x;
        float goal_y = request->y;
        float distance_x = goal_x - x;
        float distance_y = goal_y - y;
        float distance = std::sqrt(distance_x*distance_x + distance_y*distance_y);
        response->distance = distance;
        RCLCPP_INFO(this->get_logger(),"distance is %.2f",distance);
    }
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
    rclcpp::Service<Distance>::SharedPtr server_;
};

int main(int argc, char *argv[])
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    // Create and spin the node
    auto node = std::make_shared<Exer02Server>();
    rclcpp::spin(node);

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}