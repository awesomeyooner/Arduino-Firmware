#include <Arduino.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "utils.hpp"
#include "Motor.hpp"
#include "Sensor.hpp"
#include "SignalManager.hpp"
#include "Servo.hpp"
#include "Constants.hpp"
#include "heartbeat/HeartbeatManager.hpp"
#include <string>
#include "Superstructure.hpp"

#define null (char*)NULL

//managers
SignalManager signal_manager;// = SignalManager::getInstance();
HeartbeatManager heartbeat_manager;// = HeartbeatManager::getInstance();

//subsystems
subsystem::Superstructure superstructure;// = subsystem::Superstructure::getInstance();

void sendPacket();
void recievePacket();

void setup() {
  Serial.begin(115200);
  Serial.println("initializing");

  signal_manager.init();
  heartbeat_manager.init();

  //fill buffer
  sendPacket();
  recievePacket();
}

void loop() {
  sendPacket();
  recievePacket();
  
  superstructure.updateAll();

  heartbeat_manager.update();

  //voltage_sensor.update(millis());

  if(!heartbeat_manager.is_connected())
    superstructure.drive.stopAll();

}

void recievePacket(){
  JsonDocument recieve;
  
  deserializeJson(recieve, Serial.readStringUntil('\n'));

  JsonArray array = recieve.as<JsonArray>();

  // JsonObject object = array[0].as<JsonObject>();

  // voltage_sensor.update(object["value"]);

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

    superstructure.applyToAll(message);
    heartbeat_manager.apply(message);
  }
  //[{"device":"left_wheel_joint","message_type":"control","type_value":"percent","value":0.0},{"device":"right_wheel_joint","message_type":"control","type_value":"percent","value":0.0}]
}

void sendPacket(){
  
  JsonDocument send;

  JsonArray message_array = send.add<JsonArray>();

  for(ArduinoUtility::ArduinoMessage message : superstructure.getMessagesToSend()){

    JsonObject object = message_array.add<JsonObject>(); 

    object["device"] = message.device.empty() ? null : message.device;
    object["message_type"] = message.message_type.empty() ? null : message.message_type;
    object["type_value"] = message.type_value.empty() ? null : message.type_value;
    object["value"] = message.value;
  }
  
  serializeJson(send, Serial);
  Serial.print('\n');
  
} //end of method


