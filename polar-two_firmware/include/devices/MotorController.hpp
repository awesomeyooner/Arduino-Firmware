#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float64.h>

#include "Motor.hpp"
#include "Encoder.hpp"
#include "../util/Utility.hpp"
#include "../Constants.hpp"

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error handle loop
void error_loop() {
  while(1) {
    delay(100);
  }
}

namespace hardware_component{

    class MotorController{

        private:
            
        public:

            std::string name;

            rcl_publisher_t positionPublisher, velocityPublisher;
            std_msgs__msg__Float64 positionMessage, velocityMessage, commandMessage;

            rcl_subscription_t commandSubscriber;

            Motor motor;
            Encoder encoder;

            MotorController(std::string name, int inputPin1, int inputPin2, int channel1, int channel2, int channelA, int channelB) : 
                name(name),
                motor(inputPin1, inputPin2, channel1, channel2),
                encoder(channelA, channelB){}

            MotorController(std::string name, MotorID motorID, EncoderID encoderID) : 
                name(name),
                motor(motorID),
                encoder(encoderID){}

            void subscriberCallback(const void * msgin){
                const std_msgs__msg__Float64 * msg = (const std_msgs__msg__Float64 *)msgin;

                motor.command = msg->data;
            }

            void initialize(rcl_node_t* node){
                motor.initialize();
                encoder.initialize();

                RCCHECK(rclc_publisher_init_default(
                    &positionPublisher,
                    node,
                    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
                    (name + "/position").c_str()
                ));

                RCCHECK(rclc_publisher_init_default(
                    &velocityPublisher,
                    node,
                    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
                    (name + "/velocity").c_str()
                ));

                RCCHECK(rclc_subscription_init_default(
                    &commandSubscriber,
                    node,
                    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
                    (name + "/command").c_str()
                ));
            }

            void update(){
                motor.update();
                encoder.update();

                positionMessage.data = encoder.position.value;
                velocityMessage.data = encoder.velocity.value;

                RCSOFTCHECK(rcl_publish(&positionPublisher, &positionMessage, NULL));
                RCSOFTCHECK(rcl_publish(&velocityPublisher, &velocityMessage, NULL));
            }
    };
}

#endif