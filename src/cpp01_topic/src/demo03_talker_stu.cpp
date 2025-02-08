#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"
using namespace std::chrono_literals;
using base_interfaces_demo::msg::Student;

class TalkerStu: public rclcpp::Node
{
public:
    TalkerStu():Node("talkerstu_node_cpp"), age(0)
    {
        publisher_ = this->create_publisher<Student>("chatter_stu", 10);
        timer_ = this-> create_wall_timer(500ms, std::bind(&TalkerStu::on_timer, this));

    }

private:
    void on_timer() {
        auto stu = Student();
        stu.name = "jack";
        stu.age = age;
        stu.height = 2.00;
        age++;
        publisher_->publish(stu);
        RCLCPP_INFO(this->get_logger(),"msgs:(%s,%d,%.2f)", stu.name.c_str(), stu.age, stu.height);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<Student>::SharedPtr publisher_;
    int age;
};

int main(int argc, char *argv[])
{

    rclcpp::init(argc, argv);
    spin(std::make_shared<TalkerStu>());
    rclcpp::shutdown();

    return 0;
}