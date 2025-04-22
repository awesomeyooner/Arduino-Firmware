#ifndef HARDWARE_MANAGER_HPP
#define HARDWARE_MANAGER_HPP

#include "util/singleton.hpp"
#include "SimpleFOC.h"

// https://docs.simplefoc.com/stepper_control_nucleo#:~:text=Motor%20phases%20A1%20%2C%20A2%20%2C%20B1,0;%20//%20default%20voltage_power_supply%20motor.

namespace managers{

    class HardwareManager : public util::Singleton<HardwareManager>{

        public:

            HardwareManager(){}

            void initialize(){
                driver.init();
                motor.linkDriver(&driver);

                sensor.init();
                motor.linkSensor(&sensor);

                motor.init();
                motor.initFOC();
            }

            void update(){
                motor.loopFOC();
                motor.move();
            }

        private:

            // 50 Pole Pairs
            StepperMotor motor = StepperMotor(50);

            StepperDriver4PWM driver = StepperDriver4PWM(5, 6, 9, 10, 8, 7);

            MagneticSensorSPI sensor = MagneticSensorSPI(10, 14, 0x3FFF);

    }; // class HardwareManager

} // namespace managers

#endif // HARDWARE_MANAGER_HPP