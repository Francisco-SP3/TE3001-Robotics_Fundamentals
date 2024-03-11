# Francisco Salas Porras

# Libraries
import rclpy
import numpy as np
from rclpy.node import Node
from std_msgs.msg import Float32
from custom_msgs.msg import SignalParams
from scipy import signal


# Node class
class Reconstruction(Node):
    # Construction
    def __init__(self):
        # Node inicialization
        super().__init__('reconstruction')
        # Subscribe to topics
        self.create_subscription(SignalParams, 'SignalParams', self.param_callback, 10)
        # Publish topics
        self.sig_pub = self.create_publisher(Float32, 'signal_reconstructed', 10)
        # Timer definitions
        self.time = 0.0
        self.sig_timer_period = 1000 #hz
        self.sig_timer = self.create_timer(1/self.sig_timer_period, self.sig_timer_callback)
        # Signal definition
        self.signal = 0.0
        self.sig_msg = Float32()
        # Parameters definition
        self.param_msg = SignalParams()
        # Indicate succesful inicialization
        self.get_logger().info('Signal generation node successfully initialized!!!')
        
    # Signal timer callback
    def sig_timer_callback(self):
        # Update time and signal
        self.time += 1/self.sig_timer_period
        if(self.type == 1):
            self.signal = self.amplitude*np.sin(2*np.pi*self.frequency*self.time) + self.offset
        elif(self.type == 2):
            self.signal = self.amplitude*signal.square(2*np.pi*self.frequency*self.time) + self.offset
        elif(self.type == 3):
            self.signal = self.amplitude*signal.sawtooth(2*np.pi*self.frequency*self.time) + self.offset
        # Publish topics
        self.sig_msg.data = self.signal
        self.sig_pub.publish(self.sig_msg)
        # Show data
        self.get_logger().info('Signal: %f' % self.signal)

def main(args=None):
    rclpy.init(args=args)
    rec_node = Reconstruction()
    rclpy.spin(rec_node)
    rec_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()