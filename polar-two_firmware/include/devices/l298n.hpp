#ifndef L298N_HPP
#define L298N_HPP

#include "base/driver.hpp"
#include "Constants.hpp"
namespace drivers{
    
    class L298N : public Driver{

        public:

            L298N(int _enA, int _in1, int _in2, int _in3, int _in4, int _enB) : Driver(){

            }

            void initialize() override{
                //setup pins for pwm control
                ledcSetup(channelEnable, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);
                ledcSetup(channel1, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);
                ledcSetup(channel2, GeneralConstants::PWM_HERTZ, GeneralConstants::PWM_RESOLUTION);

                //attach pins
                ledcAttachPin(enablePin, channelEnable);
                ledcAttachPin(inputPin1, channel1);
                ledcAttachPin(inputPin2, channel2);
            }

            void update() override{

            }

            void set_percent(double command) override{

            }

            void set_raw(double raw){

            }

        private:

            int enA, in1, in2;
            int enB, in3, in4;


    }; // class L298N

} // namespace drivers

#endif