#ifndef DEVICEMANAGER_DEVICEMANAGER_HPP
#define DEVICEMANAGER_DEVICEMANAGER_HPP

#include "utils.hpp"
#include <string>
#include "Heartbeat.hpp"


namespace managers{

    class DeviceManager{

        private:

                      
            
        public:
            std::vector<hardware_component::Device*> devices;

            hardware_component::Heartbeat heartbeat_monitor;

            hardware_component::Motor drive_motor;
            hardware_component::Servo steer_motor;  
            DeviceManager() :
                heartbeat_monitor(HeartbeatConstants::CONFIG),
                drive_motor(MotorConstants::CONFIG),
                steer_motor(ServoConstants::CONFIG){
          
                devices.emplace_back(&drive_motor);
                devices.emplace_back(&steer_motor);
                devices.emplace_back(&heartbeat_monitor);
            }

            static DeviceManager& getInstance(){
                static DeviceManager instance;
                
                return instance;
            }

            std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend(){
            
                return {
                    heartbeat_monitor.getStatus(heartbeat_monitor.beat),
                    heartbeat_monitor.getStatus(heartbeat_monitor.delta),

                    drive_motor.getStatus(drive_motor.effort),
                    drive_motor.getStatus(drive_motor.position),
                    drive_motor.getStatus(drive_motor.velocity),

                    steer_motor.getStatus(steer_motor.effort),
                    steer_motor.getStatus(steer_motor.position)
                };
            }

            void applyToAll(ArduinoUtility::ArduinoMessage message){
                for(hardware_component::Device* device : devices){
                    device->apply(message);
                }

                drive_motor.apply(message);
                steer_motor.apply(message);
            }

            void update(){
                heartbeat_monitor.update();

                drive_motor.update();
                steer_motor.update();

                // if(heartbeat_monitor.is_connected()){
                //     for(hardware_component::Device* device : devices){
                //         device->update();
                //     }
                // }

                // else{
                //     stopAll();
                // }

                // Serial.println("==============");
                // Serial.println(std::to_string(drive_motor.velocity.value).c_str());
            }

            void stopAll(){
                drive_motor.off();
                steer_motor.off();
            }
    };
}

#endif