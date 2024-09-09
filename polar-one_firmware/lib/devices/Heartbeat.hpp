#ifndef HEARTBEAT_HEARTBEAT_HPP
#define HEARTBEAT_HEARTBEAT_HPP

#include "utils.hpp"
#include <string>
#include <Constants.hpp>
#include "Device.hpp"

namespace hardware_component{

    struct HeartbeatConfig{
        std::string device;
        int pin;
        int max_latency;

        HeartbeatConfig(std::string device, int pin, int max_latency) : device(device), pin(pin), max_latency(max_latency){}
        HeartbeatConfig(std::string device) : device(device), pin(0), max_latency(100){}
        HeartbeatConfig(){}
  };

  class Heartbeat : public Device{

    private:

        HeartbeatConfig config;
        
        double last_message = 0;

        bool is_alive = false;

    public:

      hardware_component::InterfaceValue beat = {TypeValue::RAW};

      Heartbeat(HeartbeatConfig config) : Device(config.device){
        this->config = config;

        init();
      }

      void init(){
        pinMode(config.pin, OUTPUT);
      }

      void turn_on(){
        digitalWrite(config.pin, HIGH);
      }

      void turn_off(){
        digitalWrite(config.pin, LOW);
      }

      void update(){
        beat.value = millis();

        is_alive = abs(last_message - beat.value) < config.max_latency;

        if(is_alive)
          turn_on();
        else
          turn_off();
      }

      void apply(ArduinoUtility::ArduinoMessage message){
        if(message.device != device)
          return;

        last_message = message.value;
      }

      ArduinoUtility::ArduinoMessage getStatus(hardware_component::InterfaceValue status){
          ArduinoUtility::ArduinoMessage packet;

          packet.device = device;
          packet.message_type = MessageType::STATUS;
          packet.type_value = status.interface_type;
          packet.value = status.value;

        return packet; 
      }

      bool is_connected(){
        update();

        return is_alive;
      }

  };
}

#endif