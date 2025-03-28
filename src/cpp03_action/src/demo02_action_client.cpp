#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/progress.hpp"
using base_interfaces_demo::action::Progress;
using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class ProgressActionClient: public rclcpp::Node {
public:
    ProgressActionClient():Node("progress_action_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(),"action client create!");
        client_ = rclcpp_action::create_client<Progress>(this,"get_sum");

    }
    void send_goal(int num) {
        if(!client_->wait_for_action_server(10s)) {
            RCLCPP_ERROR(this->get_logger(),"cannot connect to server");
            return;
        }
        auto goal = Progress::Goal();
        goal.num = num;
        rclcpp_action::Client<Progress>::SendGoalOptions options;
        options.goal_response_callback = std::bind(&ProgressActionClient::goal_response_callback,this,_1);
        options.feedback_callback = std::bind(&ProgressActionClient::feedback_callback,this,_1,_2);
        options.result_callback = std::bind(&ProgressActionClient::result_callback,this,_1);
        auto future = client_->async_send_goal(goal,options);
    }
    void goal_response_callback(rclcpp_action::ClientGoalHandle<Progress>::SharedPtr goal_handle) {
        if (!goal_handle) {
            RCLCPP_INFO(this->get_logger(),"request has been declined");
        }else {
            RCLCPP_INFO(this->get_logger(),"processing...");
        }
    }
    void feedback_callback(rclcpp_action::ClientGoalHandle<Progress>::SharedPtr goal_handle,const std::shared_ptr<const Progress::Feedback> feedback) {
        (void)goal_handle;
        double progress = feedback->progress;
        RCLCPP_INFO(this->get_logger(),"curent progress:%.2f", progress);
    }
    void result_callback(const rclcpp_action::ClientGoalHandle<Progress>::WrappedResult & result) {
        if(result.code == rclcpp_action::ResultCode::SUCCEEDED) {
            RCLCPP_INFO(this->get_logger(),"final result:%d", result.result->sum);
        }else if (result.code == rclcpp_action::ResultCode::ABORTED) {
            RCLCPP_INFO(this->get_logger(),"ABORTED!");
        }else if (result.code == rclcpp_action::ResultCode::CANCELED) {
            RCLCPP_INFO(this->get_logger(),"CANCELED!");
        }else {
            RCLCPP_INFO(this->get_logger(),"UNKNOWN ERROR");
        }
    }
private:
    rclcpp_action::Client<Progress>::SharedPtr client_;
};

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"must be a int num");
    }
    rclcpp::init(argc,argv);
    auto node = std::make_shared<ProgressActionClient>();
    node->send_goal(atoi(argv[1]));
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
