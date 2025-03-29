import rclpy
from rclpy.node import Node

class MyNode(Node):
    def __init__(self):
        super().__init__('time_node_py',namespace="t1_ns_py")


def main(args=None):
    # Initialize ROS 2
    rclpy.init(args=args)

    # Create and spin the node
    node = MyNode()
    rclpy.spin(node)

    # Shutdown ROS 2
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()