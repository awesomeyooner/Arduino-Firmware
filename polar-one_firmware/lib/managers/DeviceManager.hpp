#ifndef DEVICEMANAGER_DEVICEMANAGER_HPP
#define DEVICEMANAGER_DEVICEMANAGER_HPP

#include "utils.hpp"
#include <string>
#include "Heartbeat.hpp"


namespace managers{

    class DeviceManager{

        private:

            std::vector<hardware_component::Device*> devices;

            hardware_component::Heartbeat heartbeat_monitor;

            hardware_component::Motor drive_motor;
            hardware_component::Servo steer_motor;            
            
        public:
 
            DeviceManager() :
                heartbeat_monitor(HeartbeatConstants::CONFIG),
                drive_motor(ServoConstants::CONFIG),
                steer_motor(ServoConstants::CONFIG){
                
                devices.emplace_back(&heartbeat_monitor);
                devices.emplace_back(&drive_motor);
                devices.emplace_back(&steer_motor);
            }

            static DeviceManager getInstance(){
                static DeviceManager instance;
                
                return instance;
            }

            std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend(){
                std::vector<ArduinoUtility::ArduinoMessage> messages;
                
                messages.emplace_back(heartbeat_monitor.getStatus(heartbeat_monitor.beat));

                messages.emplace_back(drive_motor.getStatus(drive_motor.effort));
                messages.emplace_back(drive_motor.getStatus(drive_motor.position));
                messages.emplace_back(drive_motor.getStatus(drive_motor.velocity));

                messages.emplace_back(steer_motor.getStatus(drive_motor.effort));
                messages.emplace_back(steer_motor.getStatus(drive_motor.position));

                return messages;
            }

            void applyToAll(ArduinoUtility::ArduinoMessage message){
                for(hardware_component::Device* device : devices){
                    device->apply(message);
                }
            }

            void update(){
                if(heartbeat_monitor.is_connected()){
                    for(hardware_component::Device* device : devices){
                        device->update();
                    }
                }

                else{
                    stopAll();
                }
            }

            void stopAll(){
                drive_motor.off();
                steer_motor.off();
            }
    };
}

#endif