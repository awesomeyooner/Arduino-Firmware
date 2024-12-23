#ifndef HARDWAREMANAGER_HPP
#define HARDWAREMANAGER_HPP

#include "devices/MotorController.hpp"
#include "Constants.hpp"

namespace hardware_component{


    class HardwareManager{

        private:
        
        public:

            MotorController leftWheel;
            //MotorController rightWheel;

            HardwareManager() : 
            leftWheel("left_motor", MotorConstants::LEFT_MOTOR_ID, MotorConstants::LEFT_FRONT_ENCODER_ID){}
            //rightWheel("right_motor", MotorConstants::RIGHT_MOTOR_ID, MotorConstants::RIGHT_FRONT_ENCODER_ID){}

            void initialize(rcl_node_t* node){
                leftWheel.initialize(node);
                //rightWheel.initialize(node);
            }

            void update(){
                leftWheel.update();
                //rightWheel.update();
            }

            int getNumberOfHandles(){
                int leftHandle = 1; //speed sub
                //int rightHandle = 1; //speed sub
                int timer = 1;
                return leftHandle + timer;
            }
    };

}

#endif