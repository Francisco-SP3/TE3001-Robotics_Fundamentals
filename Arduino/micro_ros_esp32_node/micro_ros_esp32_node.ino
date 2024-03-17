// MicroROS Library
#include <micro_ros_arduino.h>
// ROS Client Libraries (RCL)
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
// ROS Standard Message Library
#include <std_msgs/msg/int32.h>
// Standard C Libraries
#include <stdio.h>

// ROS nodes
rcl_node_t node;
rcl_publisher_t rawPublisher;
rcl_publisher_t voltPublisher;
rcl_subscription_t pwmSubscriber;
// ROS messages
std_msgs__msg__Float32 dutyCycle;
// ROS timers
rcl_timer_t timer_1;
rcl_timer_t timer_2;
// microROS executor, support and allocator
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;

// PIN definition
#define LED_PIN 13
#define PWM_PIN 15
#define POT_PIN 36

// Constants and variables
pot_value = 0;
pwm_freq = 5000; //Hz
pwm_res = 8; //Bits
pwm_chan = 0;
pwm_duty = 0; //Percentage

// Timer callback 1
void timer1_callback(rcl_timer_t * timer, int64_t last_call_time){  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    pot_value =  analogRead(POT_PIN);
  } 
}

// Timer callback 2
void timer2_callback(rcl_timer_t * timer, int64_t last_call_time){  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    RCSOFTCHECK(rcl_publish(&rawPublisher, &msg, NULL)); 
    RCSOFTCHECK(rcl_publish(&voltPublisher, &msg, NULL));
  }
}

// Subscriber callback
void pwm_callback(const void * msgin){  
  // Cast the message to the correct type
  const std_msgs__msg__Float32 * msg = (const std_msgs__msg__Float32 *)msgin;
  // Set the PWM duty cycle
  pwm_duty = (int)(msg->data);

}

// Check the return value of each function. If an error occurs, it will enter the error_loop.
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error loop
void error_loop(){
  while(1){
    Serial.println("Error")
    delay(100);
  }
}

// Arduino setup
void setup() {
  set_microros_transports();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  
  
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_arduino_node_publisher"));

  // create subscriber
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_arduino_subscriber"));

  // create timer,
  const unsigned int timer_timeout = 1000;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  msg.data = 0;
}

// Arduino loop
void loop() {
  delay(100);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
