#ifndef SERVO_SERVO_HPP
#define SERVO_SERVO_HPP

#include "utils.hpp"
#include "SignalManager.hpp"

class Servo{
  private:
    int channel;
    int max_left;
    int neutral;
    int max_right;

    SignalManager* pwmController;

  public:
    String device;
    String control_mode;
    double control_value;

    double position;
    double velocity;
    double effort;

    bool inverted;

    Servo(String device, int channel, SignalManager* pwmController, int max_left, int neutral, int max_right){
      this->device = device;

      this->channel = channel;

      this->pwmController = pwmController;

      this->max_left = max_left;
      this->neutral = neutral;
      this->max_right = max_right;

      control_mode = TypeValue::EFFORT;
      control_value = 0;

      position = 0;
      velocity = 0;
      effort = 0;
      inverted = false;
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

      pwmController->sendSignal(
        channel, 
        signal
      );   

      effort = signal;
    }

    void apply(Utility::ArduinoMessage message){
      if(message.device != device)
        return;

      if(message.message_type == MessageType::CONTROL)
        handle_control(message);
      else if(message.message_type == MessageType::CONFIG)
        handle_config(message);
    }

    void handle_control(Utility::ArduinoMessage message){
      control_mode = message.type_value;
      control_value = message.value;
    }

    void handle_config(Utility::ArduinoMessage message){
      if(message.type_value == TypeValue::LOWER_BOUND)
        max_right = message.value;
      
      else if(message.type_value == TypeValue::UPPER_BOUND)
        max_left = message.value;

      else if(message.type_value == TypeValue::NEUTRAL)
        neutral = message.value;
    }

    Utility::ArduinoMessage getPosition(){
      Utility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = MessageType::STATUS;
        packet.type_value = TypeValue::POSITION;
        packet.value = position;

      return packet; 
    }

    Utility::ArduinoMessage getVelocity(){
      Utility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = MessageType::STATUS;
        packet.type_value = TypeValue::VELOCITY;
        packet.value = velocity;

      return packet; 
    }

    Utility::ArduinoMessage getEffort(){
      Utility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = MessageType::STATUS;
        packet.type_value = TypeValue::EFFORT;
        packet.value = effort;

      return packet; 
    }

    void update(double position, double velocity){
      this->position = position;
      this->velocity = velocity;
    }

    void update(){
      set_angle(control_value);
    }

    void off(){
      set_angle(0);
    }
};


#endif
