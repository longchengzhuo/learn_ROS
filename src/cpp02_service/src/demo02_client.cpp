# include "rclcpp/rclcpp.hpp"
# include "base_interfaces_demo/srv/addints.hpp"
using namespace std::chrono_literals;


using base_interfaces_demo::srv::Addints;
class  AddintsClient:public rclcpp::Node {
public:
    AddintsClient():Node("add_int_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "client node create");
        client_ = this->create_client<Addints>("add_ints");
    }
    bool connect_server() {
        // client_->wait_for_service(1s);
        while (!client_->wait_for_service(1s)) {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "connecting...");
            if (!rclcpp::ok()) {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "force stop");
                return false;
            }
        }
        return true;
    }
    rclcpp::Client<Addints>::FutureAndRequestId send_request(int num1, int num2) {
        auto request = std::make_shared<Addints::Request>();
        request->num1 = num1;
        request->num2 = num2;
        return client_->async_send_request(request);
    }
private:
    rclcpp::Client<Addints>::SharedPtr client_;
};

int main(int argc, char const *argv[]){
    if (argc != 3) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "2 parameters pls!");
        return 1;
    }

    rclcpp::init(argc,argv);
    auto client = std::make_shared<AddintsClient>();
    bool flag  = client->connect_server();
    if (!flag) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "connect fail");
        return 0;
    }
    auto future = client->send_request(atoi(argv[1]),atoi(argv[2]));
    if (rclcpp::spin_until_future_complete(client, future) == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(client->get_logger(), "respond success, sum = %d", future.get()->num);

    }
    else {
        RCLCPP_INFO(client->get_logger(), "respond fail");
    }
    rclcpp::shutdown();
    return 0;
}