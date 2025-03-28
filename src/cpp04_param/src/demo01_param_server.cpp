#include "rclcpp/rclcpp.hpp"



class ParamServer: public rclcpp::Node{
public:
    ParamServer():Node("param_server_node_cpp",rclcpp::NodeOptions().allow_undeclared_parameters(true)){
        RCLCPP_INFO(this->get_logger(),"param server create");
    }
    void declare_param() {
        RCLCPP_INFO(this->get_logger(),"----add----");
        this->declare_parameter("car_name","tiger");
        this->declare_parameter("width",1.55);
        this->declare_parameter("wheels",5);
        this->set_parameter(rclcpp::Parameter("height",2.00));

    }
    void get_param() {
        RCLCPP_INFO(this->get_logger(),"----get----");
        auto car = this->get_parameter("car_name");
        RCLCPP_INFO(this->get_logger(),"key = %s, value = %s", car.get_name().c_str(),car.as_string().c_str());
        auto params = this->get_parameters({"car_name","width","wheels"});
        for (auto &&param: params) {
            RCLCPP_INFO(this->get_logger(),"(%s = %s)",param.get_name().c_str(),param.value_to_string().c_str());
        }
        RCLCPP_INFO(this->get_logger(),"contain car_name? %d",this->has_parameter("car_name"));
        RCLCPP_INFO(this->get_logger(),"contain height? %d",this->has_parameter("height"));

    }
    void update_param() {
        RCLCPP_INFO(this->get_logger(),"----update----");
        this->set_parameter(rclcpp::Parameter("width",1.75));
        RCLCPP_INFO(this->get_logger(),"width = %.2f", this->get_parameter("width").as_double());
    }
    void del_param() {
        RCLCPP_INFO(this->get_logger(),"----delete----");
        this->undeclare_parameter("height");
        RCLCPP_INFO(this->get_logger(),"contain carname after undelete? %d",this->has_parameter("height"));

    }
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<ParamServer>();
    node->declare_param();
    node->get_param();
    node->update_param();
    node->del_param();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
