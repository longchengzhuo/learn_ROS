#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/nav.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

using base_interfaces_demo::action::Nav;

class Exer04ActionServer : public rclcpp::Node
{
public:
    Exer04ActionServer() : Node("exer05_action_server_node_cpp"),x(0.0),y(0.0)
    {
        RCLCPP_INFO(this->get_logger(),"action_server create!");
        sub_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose",10,std::bind(&Exer04ActionServer::pose_cb,this,std::placeholders::_1));
        cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
        action_server_ = rclcpp_action::create_server<Nav>(this,
            "nav",
            std::bind(&Exer04ActionServer::handle_goal,this,_1,_2),
            std::bind(&Exer04ActionServer::handle_cancel,this,_1),
            std::bind(&Exer04ActionServer::handle_accepted,this,_1));
    }
private:
    float x,y;
    void pose_cb(const turtlesim::msg::Pose::SharedPtr pose) {
        x = pose->x;
        y = pose->y;
    }
    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const Nav::Goal> goal) {
        (void)uuid;

        if (goal->goal_x < 0 || goal->goal_y < 0 || goal->goal_x > 11.08 || goal->goal_y > 11.08) {
            RCLCPP_INFO(this->get_logger(),"goal_x or goal_y is not valid");
            return rclcpp_action::GoalResponse::REJECT;
        }
        RCLCPP_INFO(this->get_logger(),"goal_x or goal_y is valid");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    rclcpp_action::CancelResponse handle_cancel(std::shared_ptr<rclcpp_action::ServerGoalHandle<Nav>> goal_handle) {
        (void)goal_handle;
        RCLCPP_INFO(this->get_logger(),"cancel action mission success");
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    void execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<Nav>> goal_handle) {
        RCLCPP_INFO(this->get_logger(),"START.........");
        auto result = std::make_shared<Nav::Result>();
        auto feedback = std::make_shared<Nav::Feedback>();
        geometry_msgs::msg::Twist twist;
        rclcpp::Rate rate(1.0);
        while (true) {
            if (goal_handle->is_canceling()) {
                goal_handle->canceled(result);
                return;
            }

            float goal_x = goal_handle->get_goal()->goal_x;
            float goal_y = goal_handle->get_goal()->goal_y;
            float distance = std::sqrt(float((goal_x-x)*(goal_x-x))+float((goal_y-y)*(goal_y-y)));
            feedback->distance = distance;
            goal_handle->publish_feedback(feedback);

            auto linear_x = float(goal_x-x);
            auto linear_y = float(goal_y-y);
            twist.linear.x = 0.1*linear_x;
            twist.linear.y = 0.1*linear_y;
            cmd_pub_->publish(twist);

            if (distance <= 0.05) {
                RCLCPP_INFO(this->get_logger(),"----------FINISHED----------");
                break;
            }

            rate.sleep();
        }
        if (rclcpp::ok()) {
            result->turtle_x = x;
            result->turtle_y = y;
            goal_handle->succeed(result);
        }
    }
    void handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<Nav>> goal_handle) {
        std::thread(std::bind(&Exer04ActionServer::execute,this,goal_handle)).detach();
    }
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
    rclcpp_action::Server<Nav>::SharedPtr action_server_;

};

int main(int argc, char *argv[])
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    // Create and spin the node
    auto node = std::make_shared<Exer04ActionServer>();
    rclcpp::spin(node);

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}