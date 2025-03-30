#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/nav.hpp"

using base_interfaces_demo::action::Nav;

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class Exer05ActionCLient : public rclcpp::Node
{
public:
    Exer05ActionCLient() : Node("exer05_action_client_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"action_client create!");
        client_ = rclcpp_action::create_client<Nav>(this,"nav");
    }
    void send_goal(float x,float y,float theta) {
        if(!client_->wait_for_action_server(10s)) {
            RCLCPP_INFO(this->get_logger(),"service connect fail");
            return;
        }
        Nav::Goal goal;
        goal.goal_x = x;
        goal.goal_y = y;
        goal.goal_theta = theta;
        rclcpp_action::Client<Nav>::SendGoalOptions options;
        options.goal_response_callback = std::bind(&Exer05ActionCLient::goal_response_callback,this,_1);
        options.feedback_callback = std::bind(&Exer05ActionCLient::feedback_callback,this,_1,_2);
        options.result_callback = std::bind(&Exer05ActionCLient::result_callback,this,_1);
        client_->async_send_goal(goal,options);
    }
    void goal_response_callback(std::shared_ptr<rclcpp_action::ClientGoalHandle<Nav>> goal_handle) {
        if (!goal_handle) {
            RCLCPP_INFO(this->get_logger(),"action request invalid");
        }else {
            RCLCPP_INFO(this->get_logger(),"action request valid");
        }

    }
    void feedback_callback(std::shared_ptr<rclcpp_action::ClientGoalHandle<Nav>> goal_handle, std::shared_ptr<const Nav::Feedback> feedback) {
        (void) goal_handle;
        RCLCPP_INFO(this->get_logger(),"remain %.2f",feedback->distance);
    }
    void result_callback(const rclcpp_action::ClientGoalHandle<Nav>::WrappedResult &result) {
        if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
            RCLCPP_INFO(this->get_logger(),"final x and y :(%.2f,%.2f)",result.result->turtle_x,result.result->turtle_y);
        }else {
            RCLCPP_INFO(this->get_logger(),"response fail");
        }
    }
private:
    rclcpp_action::Client<Nav>::SharedPtr client_;
};

int main(int argc, char *argv[])
{
    if (argc != 5) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"input is invalid");
        return 1;
    }
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    auto client = std::make_shared<Exer05ActionCLient>();
    client->send_goal(atof(argv[1]),atof(argv[2]),atof(argv[3]));
    // Create and spin the node
    rclcpp::spin(client);

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}