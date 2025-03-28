#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/progress.hpp"

using base_interfaces_demo::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;


class ProgressActionServer: public rclcpp::Node {
public:
    ProgressActionServer():Node("progress_action_server_node_cpp") {
        RCLCPP_INFO(this->get_logger(),"action server create!");
        server_ = rclcpp_action::create_server<Progress>(
            this,
            "get_sum",
            std::bind(&ProgressActionServer::handle_goal,this,_1,_2),
            std::bind(&ProgressActionServer::handle_cancel,this,_1),
            std::bind(&ProgressActionServer::handle_accepted,this,_1)
            );
    }
    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const typename Progress::Goal> goal) {
        (void) uuid;
        if (goal->num <= 1) {
            RCLCPP_INFO(this->get_logger(),"goal num must > 1");
            return rclcpp_action::GoalResponse::REJECT;
        }
        RCLCPP_INFO(this->get_logger(),"num_size legal");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    rclcpp_action::CancelResponse handle_cancel(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle) {
        (void)goal_handle;
        RCLCPP_INFO(this->get_logger(),"receive cancel command");
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    void execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle) {
        int num = goal_handle->get_goal()->num;
        int sum = 0;
        auto feedback = std::make_shared<Progress::Feedback>();

        rclcpp::Rate rate(1.0);
        auto result = std::make_shared<Progress::Result>();

        for (int i = 1;i <= num; i++) {
            sum += i;
            double progress = i / (double)num;
            feedback->progress = progress;
            goal_handle->publish_feedback(feedback);
            RCLCPP_INFO(this->get_logger(),"progress:%.2f",progress);

            if (goal_handle->is_canceling()){
                result->sum = sum;
                goal_handle->canceled(result);
                RCLCPP_INFO(this->get_logger(),"mission is canceled");
                return;
            }

            rate.sleep();
        }

        if (rclcpp::ok()) {
            result->sum = sum;
            goal_handle->succeed(result);
        }
    }
    void handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle) {
        std::thread(std::bind(&ProgressActionServer::execute, this, goal_handle)).detach();
    }

private:
    rclcpp_action::Server<Progress>::SharedPtr server_;

};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ProgressActionServer>());
    rclcpp::shutdown();
    return 0;
}
