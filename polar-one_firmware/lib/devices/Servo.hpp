#ifndef SERVO_SERVO_HPP
#define SERVO_SERVO_HPP

#include "utils.hpp"
#include "SignalManager.hpp"
#include <string>

namespace hardware_component{

  struct ServoConfig{

    std::string device;
    int channel;
    int max_left;
    int neutral;
    int max_right;

    ServoConfig(std::string device, int channel, int max_left, int neutral, int max_right) : 
      device(device), 
      channel(channel), 
      max_left(max_left),
      neutral(neutral),
      max_right(max_right){}

    ServoConfig(){}
  };

  class Servo : public Device{
    private:
      int channel;
      int max_left;
      int neutral;
      int max_right;

      managers::SignalManager pwmController = managers::SignalManager::getInstance();

    public:
      ServoConfig config;

      hardware_component::InterfaceValue command = {TypeValue::POSITION};

      hardware_component::InterfaceValue position = {TypeValue::POSITION};
      hardware_component::InterfaceValue velocity = {TypeValue::VELOCITY};
      hardware_component::InterfaceValue effort = {TypeValue::EFFORT};

      Servo(ServoConfig config) : Device(config.device){
        this->config = config;
      }

      void set_angle(double percent){
        if(percent > 1)
          percent = 1;
        else if(percent < -1)
          percent = -1;

        uint16_t signal = 0;

        if(percent < 0)
          signal = map(percent * 10000, -10000, 0, max_right, neutral);
        else if(percent > 0)
          signal = map(percent * 10000, 0, 10000, neutral, max_left);
        else
          signal = neutral;

        pwmController.sendSignal(
          channel, 
          signal
        );   

        effort.value = signal;
      }

      void apply(ArduinoUtility::ArduinoMessage message){
        if(message.device != device)
          return;

        if(message.message_type == MessageType::CONTROL)
          handle_control(message);
        else if(message.message_type == MessageType::CONFIG)
          handle_config(message);
      }

      void handle_control(ArduinoUtility::ArduinoMessage message){
        command.value = message.value;
      }

      void handle_config(ArduinoUtility::ArduinoMessage message){
        if(message.type_value == TypeValue::LOWER_BOUND)
          max_right = message.value;
        
        else if(message.type_value == TypeValue::UPPER_BOUND)
          max_left = message.value;

        else if(message.type_value == TypeValue::NEUTRAL)
          neutral = message.value;
      }

      ArduinoUtility::ArduinoMessage getStatus(hardware_component::InterfaceValue status) override{
        ArduinoUtility::ArduinoMessage packet;

          packet.device = device;
          packet.message_type = MessageType::STATUS;
          packet.type_value = status.interface_type;
          packet.value = status.value;

        return packet; 
      }

      void update(double position, double velocity){
        this->position.value = position;
        this->velocity.value = velocity;
      }

      void update(){
        set_angle(command.value);
      }

      void off(){
        set_angle(0);
      }
  };
}

#endif
