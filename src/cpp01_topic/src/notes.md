# demo01_talker_str
1. The actual path of rclcpp/rclcpp.hpp is /opt/ros/humble/include/rclcpp/rclcpp/rclcpp.hpp
   1. i guess "rclcpp/rclcpp.hpp" has some relationship with cmakelists and package.xml
   2. Because rclcpp appears twice in the path, while it only appears once in the header file inclusion of the C++ source code.
2. std::chrono_literals is a namespace in the C++ standard library that provides convenient representations for time literals.
   1. Directly using 1s to represent 1 second is more intuitive than std::chrono::seconds(1).
3. message.data ,what is data
   1. In C++, a field is a member variable of a class or struct
   2. In ROS 2, message types (Message Types) are defined using classes or structs, and fields are used to store message data. For example:
      data is a field of std_msgs::msg::String, used to store string data.