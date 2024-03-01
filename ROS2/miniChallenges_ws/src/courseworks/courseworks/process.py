# Francisco Salas Porras 18/02/24

# Libraries
import rclpy
import numpy as np
from rclpy.node import Node
from std_msgs.msg import Float32

# Node class
class Signal_Processor(Node):
    # Construction
    def __init__(self):
        # Node inicialization
        super().__init__('process')
        # Subscription topics
        self.tim_sub = self.create_subscription(Float32, 'time', self.tim_callback, 10)
        self.sig_sub = self.create_subscription(Float32, 'signal', self.sig_callback, 10)
        # Publisher topics
        self.sig_pub = self.create_publisher(Float32, 'proc_signal', 10)
        # Timer definition
        self.time = 0.0
        self.timer_period = 10 #hz
        self.timer = self.create_timer(1/self.timer_period, self.timer_callback)
        # Signal definition
        self.signal = 0.0
        self.sig_msg = Float32()
        # Indicate succesful inicialization
        self.get_logger().info('Signal processor node successfully initialized!!!')

    # Signal time callback
    def tim_callback(self, msg):
        # Update time
        self.time = msg.data
    
    # Signal callback
    def sig_callback(self, msg):
        # Update signal
        self.signal = self.process(msg.data)

    # Acting timer callback
    def timer_callback(self):
        # Show & publish topic
        self.sig_msg.data = self.signal
        self.sig_pub.publish(self.sig_msg)
        self.get_logger().info('time = %0.1f, signal = %0.3f' % (self.time, self.signal))

    # Process function
    def process(self, sig_in):
        # User variables
        P = (1)*np.pi # Phase shift
        # Signal processing
        sig_out = sig_in * np.cos(P) + np.cos(self.time) * np.sin(P)
        sig_out = sig_out / 2 + 1/2
        return sig_out

def main(args=None):
    rclpy.init(args=args)
    s_p = Signal_Processor()
    rclpy.spin(s_p)
    s_p.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()