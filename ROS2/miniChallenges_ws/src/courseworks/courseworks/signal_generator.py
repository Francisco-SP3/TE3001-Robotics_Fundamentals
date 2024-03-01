# Francisco Salas Porras 18/02/24

# Libraries
import rclpy
import numpy as np
from rclpy.node import Node
from std_msgs.msg import Float32

# Node class
class Signal_Generator(Node):
    # Construction
    def __init__(self):
        # Node inicialization
        super().__init__('signal_generator')
        # Publisher topics
        self.tim_pub = self.create_publisher(Float32, 'time', 10)
        self.sig_pub = self.create_publisher(Float32, 'signal', 10)
        # Timer definition
        self.time = 0.0
        self.tim_msg = Float32()
        self.timer_period = 10 #hz
        self.timer = self.create_timer(1/self.timer_period, self.timer_callback)
        # Signal definition
        self.signal = 0.0
        self.sig_msg = Float32()
        # Indicate succesful inicialization
        self.get_logger().info('Signal generation node successfully initialized!!!')
        
    # Acting timer callback
    def timer_callback(self):
        # Update time and signal
        self.time += 1/self.timer_period
        self.signal = np.sin(self.time)
        # Show & publish topics
        self.tim_msg.data = self.time
        self.sig_msg.data = self.signal
        self.tim_pub.publish(self.tim_msg)
        self.sig_pub.publish(self.sig_msg)
        # Show result
        self.get_logger().info('time = %0.1f, signal = %0.3f' % (self.time, self.signal))

def main(args=None):
    rclpy.init(args=args)
    s_g = Signal_Generator()
    rclpy.spin(s_g)
    s_g.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()