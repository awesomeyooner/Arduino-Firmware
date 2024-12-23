#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <string>
#include "../Constants.hpp"
#include <esp32-hal-ledc.h>
#include <Arduino.h>

namespace hardware_component{

    class Motor{

        private:
            int inputPin1, inputPin2;
            int channel1, channel2;

        public:

            bool inverted = false;
            bool isBrake = false;
            double command = 0;

            Motor(int inputPin1, int inputPin2, int channel1, int channel2) :  
                inputPin1(inputPin1), 
                inputPin2(inputPin2),
                channel1(channel1),
                channel2(channel2) {}

            Motor(MotorID id) :  
                inputPin1(id.inputPin1), 
                inputPin2(id.inputPin2),
                channel1(id.channel1),
                channel2(id.channel2) {}

            virtual void initialize(){
                //setup pins for pwm control
                ledcSetup(channel1, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);
                ledcSetup(channel2, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);

                //attach pins
                ledcAttachPin(inputPin1, channel1);
                ledcAttachPin(inputPin2, channel2);
            }

            virtual void update(){
                setSpeed(command);
            }

            virtual void off(){
                setSpeed(0);
            }

            /**
             * percent is from -1 to 1, 1 representing 100% output in forward direction
             */
            virtual void setSpeed(double percent){

                //out of bounds protection
                if(percent > 1)
                    percent = 1;
                else if(percent < -1)
                    percent = -1;

                if(inverted)
                    percent *= -1; //negate if inverted

                if(percent == 0 ){
                    if(isBrake){
                        setChannels(255, 255);
                    }
                    else{
                        setChannels(0, 0);
                    }
                }
                else if(percent > 0){ //positive
                    setChannels(
                        map(percent, 0, 1, 0, 255),
                        0
                    );
                }
                else if(percent < 0){ //negative
                    setChannels(
                        0,
                        map(percent, 0, 1, 0, 255)
                    );
                }
            }

            void setChannels(int value1, int value2){
                ledcWrite(channel1, value1);
                ledcWrite(channel2, value2);
            }
            
            void setChannels(double value1, double value2){
                ledcWrite(channel1, (int)value1);
                ledcWrite(channel2, (int)value2);
            }


    };
}

#endif