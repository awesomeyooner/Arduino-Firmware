#ifndef HEARTBEATMANAGER_HEARTBEATMANAGER_HPP
#define HEARTBEATMANAGER_HEARTBEATMANAGER_HPP

#include "utils.hpp"
#include <string>
#include <Constants.hpp>

class HeartbeatManager{

  private:
    static HeartbeatManager instance;

    std::string device = HeartbeatConstants::DEVICE;
    int pin = HeartbeatConstants::PIN;
    
    int internal_signal = 0;
    int last_message = 0;

    bool is_alive = false;

  public:

    HeartbeatManager(){}

    static HeartbeatManager getInstance(){
      return instance;
    }

    void init(){
      pinMode(pin, OUTPUT);
    }

    void turn_on(){
      digitalWrite(pin, HIGH);
    }

    void turn_off(){
      digitalWrite(pin, LOW);
    }

    void update(){
      internal_signal = millis();

      if(abs(last_message - internal_signal) < 500){
        is_alive = true;
      }
      else{
        is_alive = false;
      }

      if(is_alive)
        turn_on();
      else
        turn_off();
    }

    void apply(ArduinoUtility::ArduinoMessage message){
      if(message.device != device)
        return;

      last_message = (int)message.value;
    }

    ArduinoUtility::ArduinoMessage getHeartbeat(){
      ArduinoUtility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = MessageType::STATUS;
        packet.type_value = TypeValue::RAW;
        packet.value = internal_signal;

      return packet; 
    }

    bool is_connected(){
      return is_alive;
    }

};

#endif