#ifndef HARDWAREMANAGER_HPP
#define HARDWAREMANAGER_HPP

#include "devices/MotorController.hpp"
#include "util/builtin_led.hpp"
#include "Constants.hpp"
#include <vector>

namespace hardware_component{

    class HardwareManager{

        private:
        
        public:

            MotorController front_left_motor;
            MotorController front_right_motor;
            MotorController rear_left_motor;
            MotorController rear_right_motor;

            BuiltinLED statusLight;

            std::vector<MotorController*> motors = {
                &front_left_motor,
                &front_right_motor,
                &rear_left_motor,
                &rear_right_motor
            };

            bool estop = false;

            HardwareManager() : 
            front_left_motor("front_left_motor", MotorConstants::LEFT_MOTOR_ID, MotorConstants::FRONT_LEFT_ENCODER_ID),
            front_right_motor("front_right_motor", MotorConstants::RIGHT_MOTOR_ID, MotorConstants::FRONT_RIGHT_ENCODER_ID),
            rear_left_motor("rear_left_motor", MotorConstants::REAR_LEFT_ENCODER_ID),
            rear_right_motor("rear_right_motor", MotorConstants::REAR_RIGHT_ENCODER_ID){}

            void initialize(rcl_node_t* node, rclc_executor_t* executor){

                for(MotorController* motor : motors){
                    motor->initialize(node, executor);
                    motor->motor.isBrake = true;
                }
                statusLight.initialize();
            }

            void update(){
                for(MotorController* motor : motors){
                    motor->update(estop);
                }
            }

            void toggleEstop(bool toggle){
                estop = toggle;
            }

            int getNumberOfHandles(){
                int sum = 1; //1 for the timer

                for(MotorController* motor : motors){
                    sum += motor->getNumberOfHandles();
                }
                return sum;
            }
    };

}

#endif