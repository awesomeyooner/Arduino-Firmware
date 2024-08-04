#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "utils.hpp"
#include "Motor.hpp"
#include "Sensor.hpp"
#include "SignalManager.hpp"
#include "Servo.hpp"
#include "Constants.hpp"

#define null (char*)NULL

SignalManager signal_manager;

Servo steer_motor(
  ServoConstants::DEVICE, 
  ServoConstants::CHANNEL, 
  &signal_manager, 
  ServoConstants::MAX_LEFT, 
  ServoConstants::NEUTRAL, 
  ServoConstants::MAX_RIGHT
);

Motor drive_motor(
  MotorConstants::DEVICE,
  MotorConstants::CHANNEL, 
  &signal_manager, 
  MotorConstants::MAX_FORWARD, 
  MotorConstants::NEUTRAL, 
  MotorConstants::MAX_REVERSE
);

Sensor voltage_sensor(
  VoltageSensorConstants::DEVICE, 
  VoltageSensorConstants::CHANNEL, 
  TypeValue::VOLTAGE
);

void setup() {
  Serial.begin(115200);
  Serial.println("initializing");

  signal_manager.init();

  //fill buffer
  sendPacket();
  recievePacket();
}

void loop() {
  sendPacket();
  recievePacket();
  
  drive_motor.update();
  steer_motor.update();

  voltage_sensor.update(millis());
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
    drive_motor.getPosition(), 
    drive_motor.getVelocity(),

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


