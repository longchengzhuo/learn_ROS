#include "rclcpp/rclcpp.hpp"


using namespace std::chrono_literals;
class ParamClient: public rclcpp::Node{
public:
    ParamClient():Node("param_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(),"param client create");
        param_client_ = std::make_shared<rclcpp::SyncParametersClient>(this,"param_server_node_cpp");
    }
    bool connect_server() {
        while (!param_client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                return false;
            }
            RCLCPP_INFO(this->get_logger(),"connecting...");
        }
        return true;
    }
    void get_param() {
        RCLCPP_INFO(this->get_logger(),"check parameters....");
        std::string car_name = param_client_->get_parameter<std::string>("car_name");
        double width = param_client_->get_parameter<double>("width");
        RCLCPP_INFO(this->get_logger(),"car_name = %s",car_name.c_str());
        RCLCPP_INFO(this->get_logger(),"width = %.2f",width);

        auto params = param_client_->get_parameters({"car_name","width","wheels"});
        for (auto &&param: params) {
            RCLCPP_INFO(this->get_logger(),"%s = %s",param.get_name().c_str(),param.value_to_string().c_str());
        }

    }
    void update_param() {
        RCLCPP_INFO(this->get_logger(),"update parameters....");
        param_client_->set_parameters({rclcpp::Parameter("car_name","pig"),rclcpp::Parameter("width",3.0),rclcpp::Parameter("length",5.0)});
    }
private:
    rclcpp::SyncParametersClient::SharedPtr param_client_;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto client = std::make_shared<ParamClient>();
    bool flag = client->connect_server();
    if (!flag) {
        return 0;
    }
    client->get_param();
    client->update_param();
    client->get_param();
    rclcpp::shutdown();


    return 0;
}
