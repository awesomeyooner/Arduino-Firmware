#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include "motor.hpp"
#include "quadrature_encoder.hpp"
#include "l298n.hpp"
#include "../util/utility.hpp"
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

        public:

            std::string name;

            MotorController(std::string name, int index, int enA, int in1, int in2, int chA, int chB) : 
                name(name),
                motor(false),
                encoder(chA, chB),
                driver(enA, in1, in2){

                }

            MotorController(std::string name, int index, SensoredMotorID id) : 
                MotorController(name, index, id.enA, id.in1, id.in2, id.chA, id.chB){}

            void initialize(){
                motor.link_driver(&driver);
                motor.link_encoder(&encoder);
                motor.initialize();

                encoder.initialize([](){encoder.handleA();});
            }

            void update(bool enabled){
                motor.update(enabled);

                motor.set_command(commandMessage.data);

               
            }

            private:
                Motor motor;
                QuadratureEncoder encoder;
                L298N driver;

    }; // class MotorController
} // namespace hardware_component 

#endif