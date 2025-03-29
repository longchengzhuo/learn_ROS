from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    # change node name
    # return LaunchDescription(
    #     [Node(package="turtlesim",executable="turtlesim_node",name="turtle1"),
    #      Node(package="turtlesim",executable="turtlesim_node",namespace="t1"),
    #      Node(package="turtlesim",executable="turtlesim_node",namespace="t1",name="turtle1")]
    # )
    #change topic name
    return LaunchDescription(
        [Node(package="turtlesim",executable="turtlesim_node",name="turtle1"),
         Node(package="turtlesim",executable="turtlesim_node",remappings=[("/turtle1/cmd_vel","cmd_vel")]),
         Node(package="turtlesim",executable="turtlesim_node",namespace="t1",name="turtle1")]
    )