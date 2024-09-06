#ifndef DRIVE_DRIVE_HPP
#define DRIVE_DRIVE_HPP

#include <vector>
#include "utils.hpp"
#include "Motor.hpp"
#include "Servo.hpp"
#include "Sensor.hpp"
#include "Constants.hpp"
#include "Subsystem.hpp"

namespace subsystem{

    class Drive : public Subsystem{

        private:    
            static Drive instance;

            std::vector<hardware_component::Device*> devices;

            hardware_component::Motor drive_motor;
            hardware_component::Servo steer_motor;

        public:

            Drive() : Subsystem(), drive_motor(ServoConstants::CONFIG), steer_motor(ServoConstants::CONFIG){
                devices.emplace_back(&drive_motor);
                devices.emplace_back(&steer_motor);
            }

            static Drive getInstance(){
                return instance;
            }

            void stopAll(){
                drive_motor.off();
                steer_motor.off();
            }

            std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend() override{
                std::vector<ArduinoUtility::ArduinoMessage> messages;

                messages.emplace_back(drive_motor.getStatus(drive_motor.effort));
                messages.emplace_back(drive_motor.getStatus(drive_motor.position));
                messages.emplace_back(drive_motor.getStatus(drive_motor.velocity));

                messages.emplace_back(steer_motor.getStatus(drive_motor.effort));
                messages.emplace_back(steer_motor.getStatus(drive_motor.position));

                return messages;
            }

            void applyToAll(ArduinoUtility::ArduinoMessage message) override{
                for(hardware_component::Device* device : devices){
                    device->apply(message);
                }
            }

            void updateAll() override{
                for(hardware_component::Device* device : devices){
                    device->update();
                }
            }
    };
}

#endif