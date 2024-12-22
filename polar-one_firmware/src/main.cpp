#include <Arduino.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "utils.hpp"
#include "Motor.hpp"
#include "Sensor.hpp"
#include "SignalManager.hpp"
#include "Servo.hpp"
#include "Constants.hpp"
#include <string>
#include "DeviceManager.hpp"
#include "PacketManager.hpp"

#define null "null"//(char*)NULL

//managers
managers::SignalManager* signal_manager;
managers::PacketManager* packet_manager;
managers::DeviceManager* device_manager;

void setup() {
  signal_manager = managers::SignalManager::getInstance();
  packet_manager = managers::PacketManager::getInstance();
  device_manager = managers::DeviceManager::getInstance();
  
  Serial.begin(115200);

  signal_manager->init();

  //fill buffer
  packet_manager->sendPacket();
  packet_manager->recievePacket();
}

void loop() {
  packet_manager->update();
}

