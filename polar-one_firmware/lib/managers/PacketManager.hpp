// #ifndef PACKETMANAGER_PACKETMANAGER_HPP
// #define PACKETMANAGER_PACKETMANAGER_HPP

// #include "utils.hpp"
// #include <ArduinoJson.h>
// #include <ArduinoJson.hpp>
// #include <string>

// class SignalManager{

//   private:
    

//   public:

//     PacketManager(){
//     }

//     void init(){

//     }

//     void recievePacket(){
//       JsonDocument recieve;
      
//       deserializeJson(recieve, Serial.readstd::stringUntil('\n'));

//       JsonArray array = recieve.as<JsonArray>();

//       // JsonObject object = array[0].as<JsonObject>();

//       // voltage_sensor.update(object["value"]);

//       for(JsonObject object : array){
//         ArduinoUtility::ArduinoMessage message;
//           std::string device = object["device"];
//           std::string message_type = object["message_type"];
//           std::string type_value = object["type_value"];
//           double value = object["value"];

//           message.device = device;
//           message.message_type = message_type;
//           message.type_value = type_value;
//           message.value = value;

//         drive_motor.apply(message);
//         steer_motor.apply(message);
//       }
//       //[{"device":"left_wheel_joint","message_type":"control","type_value":"percent","value":0.0},{"device":"right_wheel_joint","message_type":"control","type_value":"percent","value":0.0}]
//     }

//     void sendPacket(){
    
//       ArduinoUtility::ArduinoMessage messages[] = {
//         drive_motor.getPosition(), drive_motor.getVelocity(),
//         steer_motor.getPosition(),
//         voltage_sensor.getStatus()
//       };
      
//       JsonDocument send;

//       JsonArray message_array = send.add<JsonArray>();

//       for(ArduinoUtility::ArduinoMessage message : messages){

//         JsonObject object = message_array.add<JsonObject>(); 

//         object["device"] = message.device == NULL ? null : message.device;
//         object["message_type"] = message.message_type == NULL ? null : message.message_type;
//         object["type_value"] = message.type_value == NULL ? null : message.type_value;
//         object["value"] = message.value;
//       }
      
//       serializeJson(send, Serial);
//       Serial.print('\n');
      
//     } //end of method

// };

// #endif