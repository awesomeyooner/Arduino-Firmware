#ifndef PACKETMANAGER_PACKETMANAGER_HPP
#define PACKETMANAGER_PACKETMANAGER_HPP

#include "utils.hpp"
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>


class SignalManager{

  private:
    

  public:

    PacketManager(){
    }

    void init(){

    }

    void recievePacket(){
      JsonDocument recieve;
      
      deserializeJson(recieve, Serial.readStringUntil('\n'));

      JsonArray array = recieve.as<JsonArray>();

      // JsonObject object = array[0].as<JsonObject>();

      // voltage_sensor.update(object["value"]);

      for(JsonObject object : array){
        Utility::ArduinoMessage message;
          String device = object["device"];
          String message_type = object["message_type"];
          String type_value = object["type_value"];
          double value = object["value"];

          message.device = device;
          message.message_type = message_type;
          message.type_value = type_value;
          message.value = value;

        drive_motor.apply(message);
        steer_motor.apply(message);
      }
      //[{"device":"left_wheel_joint","message_type":"control","type_value":"percent","value":0.0},{"device":"right_wheel_joint","message_type":"control","type_value":"percent","value":0.0}]
    }

    void sendPacket(){
    
      Utility::ArduinoMessage messages[] = {
        drive_motor.getPosition(), drive_motor.getVelocity(),
        steer_motor.getPosition(),
        voltage_sensor.getStatus()
      };
      
      JsonDocument send;

      JsonArray message_array = send.add<JsonArray>();

      for(Utility::ArduinoMessage message : messages){

        JsonObject object = message_array.add<JsonObject>(); 

        object["device"] = message.device == NULL ? null : message.device;
        object["message_type"] = message.message_type == NULL ? null : message.message_type;
        object["type_value"] = message.type_value == NULL ? null : message.type_value;
        object["value"] = message.value;
      }
      
      serializeJson(send, Serial);
      Serial.print('\n');
      
    } //end of method

};

#endif