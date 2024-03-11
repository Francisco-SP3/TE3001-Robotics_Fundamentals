# Francisco Salas Porras

# Libraries
import rclpy
import numpy as np
from rclpy.node import Node
from std_msgs.msg import Float32
from custom_msgs.msg import SignalParams
from scipy import signal


# Node class
class Signal_Generator(Node):
    # Construction
    def __init__(self):
        # Node inicialization
        super().__init__('signal_generator')
        # Declare parameters
        self.declare_parameters(
            namespace='',
            parameters=[
                ('type', rclpy.Parameter.Type.INTEGER),
                ('amplitude', rclpy.Parameter.Type.DOUBLE),
                ('frequency', rclpy.Parameter.Type.DOUBLE),
                ('offset', rclpy.Parameter.Type.DOUBLE),
                ('phase', rclpy.Parameter.Type.DOUBLE),
            ]
        )
        # Publish topics
        self.sig_pub = self.create_publisher(Float32, 'signal', 10)
        self.param_pub = self.create_publisher(SignalParams, 'SignalParams', 10)
        # Timer definitions
        self.time = 0.0
        self.sig_timer_period = 1000 #hz
        self.param_timer_period = 10 #hz
        self.sig_timer = self.create_timer(1/self.sig_timer_period, self.sig_timer_callback)
        self.param_timer = self.create_timer(1/self.param_timer_period, self.param_timer_callback)
        # Signal definition
        self.signal = 0.0
        self.sig_msg = Float32()
        # Parameters definition
        self.type = self.get_parameter('type').get_parameter_value().integer_value
        self.amplitude = self.get_parameter('amplitude').get_parameter_value().double_value
        self.frequency = self.get_parameter('frequency').get_parameter_value().double_value
        self.offset = self.get_parameter('offset').get_parameter_value().double_value
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
        #self.signal = 1.0
        # Publish topics
        self.sig_msg.data = self.signal
        self.sig_pub.publish(self.sig_msg)
        # Show data
        self.get_logger().info('Signal: %f' % self.signal)

    # Parameter timer callback
    def param_timer_callback(self):
        # Update parameters
        self.type = self.get_parameter('type').get_parameter_value().integer_value
        self.amplitude = self.get_parameter('amplitude').get_parameter_value().double_value
        self.frequency = self.get_parameter('frequency').get_parameter_value().double_value
        self.offset = self.get_parameter('offset').get_parameter_value().double_value
        # Publish parameters
        self.param_msg.type = self.type
        self.param_msg.amplitude = self.amplitude
        self.param_msg.frequency = self.frequency
        self.param_msg.offset = self.offset
        self.param_msg.time = self.time
        self.param_pub.publish(self.param_msg)
        # Show data
        self.get_logger().info('time = %0.1f, signal = %0.3f, type = %1d, amp = %0.1f, freq = %0.1f, off = %0.1f' % (self.time, self.signal, self.type, self.amplitude, self.frequency, self.offset))

def main(args=None):
    rclpy.init(args=args)
    sg_node = Signal_Generator()
    rclpy.spin(sg_node)
    sg_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()