#ifndef MOTOR_MOTOR_HPP
#define MOTOR_MOTOR_HPP

#include "utils.hpp"
#include "SignalManager.hpp"
#include <string>
#include "Device.hpp"
#include "Constants.hpp"

namespace hardware_component{

  // struct MotorConfig{

  //     std::string device;
  //     int channel;
  //     int max_forward;
  //     int neutral;
  //     int max_reverse;

  //     MotorConfig(std::string device, int channel, int max_forward, int neutral, int max_reverse) : 
  //       device(device), 
  //       channel(channel), 
  //       max_forward(max_forward),
  //       neutral(neutral),
  //       max_reverse(max_reverse){}

  //     MotorConfig(){}
  // };

  class Motor : public Device{

    private:
      
      managers::SignalManager pwmController = managers::SignalManager::getInstance();

    public:
      MotorConfig config;

      hardware_component::InterfaceValue command = {MotorConstants::COMMAND_INTERFACE};

      hardware_component::InterfaceValue position = {TypeValue::POSITION};
      hardware_component::InterfaceValue velocity = {TypeValue::VELOCITY};
      hardware_component::InterfaceValue effort = {TypeValue::EFFORT};

      bool inverted;

      Motor(MotorConfig config) : Device(config.device){
        this->config = config;
      }

      void set_speed(double percent){
        if(percent > 1)
          percent = 1;
        else if(percent < -1)
          percent = -1;

        uint16_t signal = 0;
        
        if(percent < 0)
          signal = map(percent * 10000, -10000, 0, config.max_reverse, config.neutral);
        else if(percent > 0)
          signal = map(percent * 10000, 0, 10000, config.neutral, config.max_forward);
        else
          signal = config.neutral;
          
        pwmController.sendSignal(
          config.channel, 
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
          config.max_reverse = message.value;
        
        else if(message.type_value == TypeValue::UPPER_BOUND)
          config.max_forward = message.value;

        else if(message.type_value == TypeValue::NEUTRAL)
          config.neutral = message.value;
      }

      ArduinoUtility::ArduinoMessage getStatus(hardware_component::InterfaceValue status){
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
        set_speed(command.value);
      }

      void off(){
        set_speed(0);
      }
  };
}


#endif
