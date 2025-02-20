#ifndef HARDWAREMANAGER_HPP
#define HARDWAREMANAGER_HPP

#include "devices/MotorController.hpp"
#include "Constants.hpp"

namespace hardware_component{

    class HardwareManager{

        private:
        
        public:

            MotorController leftWheel;
            MotorController rightWheel;

            HardwareManager() : 
            leftWheel("front_left_motor", MotorConstants::LEFT_MOTOR_ID, MotorConstants::LEFT_FRONT_ENCODER_ID),
            rightWheel("front_right_motor", MotorConstants::RIGHT_MOTOR_ID, MotorConstants::RIGHT_FRONT_ENCODER_ID){}

            void initialize(rcl_node_t* node, rclc_executor_t* executor){
                leftWheel.initialize(node, executor);
                rightWheel.initialize(node, executor);

                leftWheel.motor.inverted = false;
                leftWheel.motor.isBrake = true;

                rightWheel.motor.inverted = true;
                rightWheel.motor.isBrake = true;

                leftWheel.encoder.countsPerRevolution = MotorConstants::ENCODER_CPR;
                leftWheel.encoder.sensorToMechanismRatio = MotorConstants::GEAR_RATIO;

                rightWheel.encoder.countsPerRevolution = MotorConstants::ENCODER_CPR;
                rightWheel.encoder.sensorToMechanismRatio = MotorConstants::GEAR_RATIO;
            }

            void update(){
                leftWheel.update();
                rightWheel.update();
            }

            int getNumberOfHandles(){
                int timer = 1;
                return leftWheel.getNumberOfHandles() + rightWheel.getNumberOfHandles() + timer;
            }
    };

}

#endif