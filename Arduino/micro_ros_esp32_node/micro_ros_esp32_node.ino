// MicroROS Library
#include <micro_ros_arduino.h>
// ROS Client Libraries (RCL)
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
// ROS Standard Message Library
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32.h>
// Standard C Libraries
#include <stdio.h>

// ROS nodes
rcl_node_t node;
rcl_publisher_t rawPublisher;
rcl_publisher_t voltPublisher;
rcl_subscription_t pwmSubscriber;
// ROS messages
std_msgs__msg__Float32 dutyCycle;
std_msgs__msg__Float32 voltage;
std_msgs__msg__Int32 raw_pot;
// ROS timers
rcl_timer_t timer_1;
rcl_timer_t timer_2;
// microROS executor, support and allocator
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;

// PIN definition
#define LED_PIN 32
#define PWM_PIN 25
#define POT_PIN 33

// Constants and variables
int pwm_freq = 5000;
float pwm_T = 1/pwm_freq;
int pwm_res = 8;
int pwm_resolution = (int)(pow(2, pwm_res) - 1);
int pwm_chan = 0;

// Timer callback 1
void timer1_callback(rcl_timer_t * timer, int64_t last_call_time){  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    raw_pot.data =  analogRead(POT_PIN);
  } 
}

// Timer callback 2
void timer2_callback(rcl_timer_t * timer, int64_t last_call_time){  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    // Calculate the voltage
    voltage.data = map(raw_pot.data, 0, 4096, 0, 3.3 * 100) / 100.0;
    // Publish the voltage and the raw potentiometer value
    RCSOFTCHECK(rcl_publish(&rawPublisher, &raw_pot, NULL)); 
    RCSOFTCHECK(rcl_publish(&voltPublisher, &voltage, NULL));
  }
}

// Subscriber callback
void pwm_callback(const void * msgin){  
  // Cast the message to the correct type
  const std_msgs__msg__Float32 * msg = (const std_msgs__msg__Float32 *)msgin;
  // Set the PWM duty cycle
  int pwm = (msgin.data)/100 * pwm_res;
  ledcWrite(pwm_chan, pwm);
}

// Check the return value of each function. If an error occurs, it will enter the error_loop.
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error loop
void error_loop(){
  while(1){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
}

// Arduino setup
void setup() {
  set_microros_transports();

  // LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // PWM
  ledcSetup(pwm_chan, pwm_freq, pwm_res);
  ledcAttachPin(PWM_PIN, pwm_chan);
  
  delay(2000);

  allocator = rcl_get_default_allocator();

  // Create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // Create node
  RCCHECK(rclc_node_init_default(&node, "pwm_node", "", &support));

  // Create publishers
  RCCHECK(rclc_publisher_init_default(
    &rawPublisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "/raw_pot"));

  RCCHECK(rclc_publisher_init_default(
    &voltPublisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "/voltage"));

  // Create subscriber
  RCCHECK(rclc_subscription_init_default(
    &pwmSubscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "pwm_duty_cycle"));

  // Create timers for publishing
  const unsigned int timer_timeout = 1000;
  RCCHECK(rclc_timer_init_default(
    &timer_1,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer1_callback));

  const unsigned int timer_timeout2 = 100;
  RCCHECK(rclc_timer_init_default(
    &timer_2,
    &support,
    RCL_MS_TO_NS(timer_timeout2),
    timer2_callback));

  // Create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer_1));
  RCCHECK(rclc_executor_add_timer(&executor, &timer_2));
  RCCHECK(rclc_executor_add_subscription(&executor, &pwmSubscriber, &dutyCycle, &pwm_callback, ON_NEW_DATA))

  dutyCycle.data = 0.0;
  voltage.data = 0;
  raw_pot.data = 0;
}

// Arduino loop
void loop() {
  delay(100);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
