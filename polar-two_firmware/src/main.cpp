#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float64.h>

#include "../include/devices/Encoder.hpp"
#include "../include/devices/Motor.hpp"
#include "../include/HardwareManager.hpp"

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This example is only avaliable for Arduino framework with serial transport.
#endif
#include <exception>

hardware_component::HardwareManager hardwareManager;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// #define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// #define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// // Error handle loop
// void error_loop() {
//   while(1) {
//     delay(100);
//   }
// }

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    hardwareManager.update();
  }
}

void leftSubscriberCallback(const void * msgin){
  hardwareManager.leftWheel.subscriberCallback(msgin);
}

// void rightSubscriberCallback(const void * msgin){
//   hardwareManager->rightWheel.subscriberCallback(msgin);
// }

void setup() {

  // Configure serial transport
  Serial.begin(115200);
  set_microros_serial_transports(Serial);
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "esp32_bridge", "esp32", &support));

  hardwareManager.initialize(&node);

  // create timer,
  const unsigned int timer_timeout = 20;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, hardwareManager.getNumberOfHandles(), &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  RCCHECK(rclc_executor_add_subscription(
    &executor, 
    &hardwareManager.leftWheel.commandSubscriber, 
    &hardwareManager.leftWheel.commandMessage, 
    &leftSubscriberCallback, 
    ON_NEW_DATA
  ));

  // RCCHECK(rclc_executor_add_subscription(
  //   &executor, 
  //   &hardwareManager->rightWheel.commandSubscriber, 
  //   &hardwareManager->rightWheel.commandMessage, 
  //   &rightSubscriberCallback, 
  //   ON_NEW_DATA
  // ));
}

void loop() {
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10)));
}