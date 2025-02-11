# include "rclcpp/rclcpp.hpp"
# include "base_interfaces_demo/srv/addints.hpp"

using base_interfaces_demo::srv::Addints;
using std::placeholders::_1;
using std::placeholders::_2;


class  AddintsServer:public rclcpp::Node {
public:
    AddintsServer():Node("add_int_server_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "server node create");
        server_ = this->create_service<Addints>("add_ints",std::bind(&AddintsServer::add, this, _1, _2));
    }

private:
    void add(const Addints::Request::SharedPtr req, const Addints::Response::SharedPtr res) {
        res->num = req->num1 + req->num2;
        RCLCPP_INFO(this->get_logger(), "%d + %d = %d", req->num1, req->num2, res->num);
    }
    rclcpp::Service<Addints>::SharedPtr server_;

};

int main(int argc, char const *argv[]){
    rclcpp::init(argc,argv);
    spin(std::make_shared<AddintsServer>());
    rclcpp::shutdown();
    return 0;
}