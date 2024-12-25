#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <string>
#include "../Constants.hpp"
#include <esp32-hal-ledc.h>
#include <Arduino.h>

namespace hardware_component{

    class Motor{

        private:
            int enablePin, inputPin1, inputPin2;
            int channelEnable, channel1, channel2;

        public:

            bool inverted = false;
            bool isBrake = false;
            double command = 0;

            Motor(int enablePin, int inputPin1, int inputPin2, int channelEnable, int channel1, int channel2) :  
                enablePin(enablePin),
                inputPin1(inputPin1), 
                inputPin2(inputPin2),
                channelEnable(channelEnable),
                channel1(channel1),
                channel2(channel2) {}

            Motor(MotorID id) :  
                enablePin(id.enablePin),
                inputPin1(id.inputPin1), 
                inputPin2(id.inputPin2),
                channelEnable(id.channelEnable),
                channel1(id.channel1),
                channel2(id.channel2) {}

            virtual void initialize(){
                //setup pins for pwm control
                ledcSetup(channelEnable, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);
                ledcSetup(channel1, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);
                ledcSetup(channel2, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);

                //attach pins
                ledcAttachPin(enablePin, channelEnable);
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
                        setChannels(0, 255, 255);
                    }
                    else{
                        setChannels(0, 0, 0);
                    }
                }
                else if(percent > 0){ //positive
                    setChannels(
                        map(percent * 1000, 0, 1000, 0, GeneralConstants::MAX_DUTY_CYCLE),
                        GeneralConstants::MAX_DUTY_CYCLE, //HIGH
                        0 //LOW
                    );
                }
                else if(percent < 0){ //negative
                    setChannels(
                        map(-percent * 1000, 0, 1000, 0, GeneralConstants::MAX_DUTY_CYCLE),
                        0,  //LOW
                        GeneralConstants::MAX_DUTY_CYCLE //HIGH
                    );
                }
            }

            void setChannels(int enableValue, int value1, int value2){
                ledcWrite(channelEnable, enableValue);
                ledcWrite(channel1, value1);
                ledcWrite(channel2, value2);
            }
            
            void setChannels(double enableValue, double value1, double value2){
                ledcWrite(channelEnable, (int)enableValue);
                ledcWrite(channel1, (int)value1);
                ledcWrite(channel2, (int)value2);
            }


    };
}

#endif