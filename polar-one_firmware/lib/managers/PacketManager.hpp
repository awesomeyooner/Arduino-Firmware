#ifndef PACKETMANAGER_PACKETMANAGER_HPP
#define PACKETMANAGER_PACKETMANAGER_HPP

#include "utils.hpp"
#include "DeviceManager.hpp"
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <string>

#define null "null"//(char*)NULL

namespace managers{


    class PacketManager{

        private:
            managers::DeviceManager* device_manager;

        public:

            static PacketManager instance;

            PacketManager() : device_manager(managers::DeviceManager::getInstance()){}

            static PacketManager* getInstance();

            void update(){
                sendPacket();
                recievePacket();
                device_manager->update();
            }

            void recievePacket(){
                JsonDocument recieve;
                
                deserializeJson(recieve, Serial.readStringUntil('\n'));

                JsonArray array = recieve.as<JsonArray>();

                for(JsonObject object : array){
                    ArduinoUtility::ArduinoMessage message;

                    std::string device = object["device"];
                    std::string message_type = object["message_type"];
                    std::string type_value = object["type_value"];
                    double value = object["value"];

                    message.device = device;
                    message.message_type = message_type;
                    message.type_value = type_value;
                    message.value = value;

                    device_manager->applyToAll(message);
                }
            }

            void sendPacket(){
            
                JsonDocument send;

                JsonArray message_array = send.add<JsonArray>();

                for(ArduinoUtility::ArduinoMessage message : device_manager->getMessagesToSend()){

                    JsonObject object = message_array.add<JsonObject>(); 

                    object["device"] = message.device.empty() ? null : message.device;
                    object["message_type"] = message.message_type.empty() ? null : message.message_type;
                    object["type_value"] = message.type_value.empty() ? null : message.type_value;
                    object["value"] = message.value;
                }
                
                serializeJson(send, Serial);
                Serial.print('\n');
            
            }
    };

    managers::PacketManager managers::PacketManager::instance;

    managers::PacketManager* managers::PacketManager::getInstance(){
        return &instance;
    }    
}

#endif