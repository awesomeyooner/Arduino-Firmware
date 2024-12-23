#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <string>
#include "../Constants.hpp"
#include <esp32-hal-ledc.h>
#include <Arduino.h>
#include "../util/Utility.hpp"
#include <map>
#include <FunctionalInterrupt.h>
#include "esp_timer.h"

namespace hardware_component{

    class Encoder{

        private:
            int channelA, channelB;

            Utility::TimestampedNumber previousPosition;
            Utility::TimestampedNumber positionRaw;

        public:
            double pulsesPerRevolution = 1.0;
            double sensorToMechanismRatio = 1.0;

            Utility::TimestampedNumber position;
            Utility::TimestampedNumber velocity;

            Encoder(int channelA, int channelB) : 
                channelA(channelA),
                channelB(channelB){
                    //set default values for position and velocity so that it doesn't freak out initially
                    double time = esp_timer_get_time() / 1000000;
                    previousPosition.timestamp = time;
                    position.timestamp = time;
                    velocity.timestamp = time;
            }

            virtual void initialize(){
                pinMode(channelA, INPUT_PULLDOWN);
                pinMode(channelB, INPUT_PULLDOWN);

                attachInterrupt(digitalPinToInterrupt(channelA), [this]() {handleA();}, CHANGE);
                attachInterrupt(digitalPinToInterrupt(channelB), [this]() {handleB();}, CHANGE);
            }

            void handleA(){

                if(digitalRead(channelA) == HIGH){
                    if(digitalRead(channelB) == LOW)
                        positionRaw.value += 1;
                    else if (digitalRead(channelB) == HIGH)
                        positionRaw.value -= 1;
                }

                else if(digitalRead(channelA) == LOW){
                    if(digitalRead(channelB) == HIGH)
                        positionRaw.value += 1;
                    else if (digitalRead(channelB) == LOW)
                        positionRaw.value -= 1;
                }
            }

            void handleB(){
                
                if(digitalRead(channelB) == HIGH){
                    if(digitalRead(channelA) == HIGH)
                        positionRaw.value += 1;
                    else if (digitalRead(channelA) == LOW)
                        positionRaw.value -= 1;
                }

                else if(digitalRead(channelB) == LOW){
                    if(digitalRead(channelA) == LOW)
                        positionRaw.value += 1;
                    else if (digitalRead(channelA) == HIGH)
                        positionRaw.value -= 1;
                }
            }
            /**
             * this NEEDS some sort of delay for it to work properly
             */
            virtual void update(){
                double time = (double)esp_timer_get_time() / 1000000.0;
                
                //pulses / ppr = motor rotations
                //motor rotations * sensorToMechRatio = total
                position.value = (positionRaw.value / pulsesPerRevolution) / sensorToMechanismRatio;
                position.timestamp = time;

                positionRaw.timestamp = time;

                velocity.value = (positionRaw.getRate(previousPosition) / pulsesPerRevolution) / sensorToMechanismRatio;
                velocity.timestamp = time;

                previousPosition = positionRaw;
            }
  
    };
}

#endif