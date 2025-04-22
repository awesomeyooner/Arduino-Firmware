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

            MotorController left_motor;
            MotorController right_motor;

            BuiltinLED statusLight;

            std::vector<MotorController*> motors = {
                &left_motor,
                &right_motor
            };

            bool estop = false;

            HardwareManager() : 
            left_motor("left_motor", MotorConstants::LEFT_MOTOR_ID, MotorConstants::LEFT_ENCODER_ID),
            right_motor("right_motor", MotorConstants::RIGHT_MOTOR_ID, MotorConstants::RIGHT_ENCODER_ID){}

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