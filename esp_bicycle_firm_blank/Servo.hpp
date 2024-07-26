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

    bool inverted;

    Servo(String device, int channel, SignalManager* pwmController, int max_left, int neutral, int max_right){
      this->device = device;

      this->channel = channel;

      this->pwmController = pwmController;

      this->max_left = max_left;
      this->neutral = neutral;
      this->max_right = max_right;

      control_mode = ArduinoValue::PERCENT;
      control_value = 0;

      position = 0;
      velocity = 0;
      inverted = false;
    }

    void set_angle(double percent){
      if(percent > 1)
        percent = 1;
      else if(percent < -1)
        percent = -1;

      uint16_t signal = map(percent * 10000, -10000, 10000, max_right, max_left);

      pwmController->sendSignal(
        channel, 
        signal
      );   
    }

    void apply(Utility::ArduinoMessage message){
      if(message.device != device)
        return;

      if(message.message_type == ArduinoValue::CONTROL){
        control_mode = message.type_value;
        control_value = message.value;
      }
    }

    Utility::ArduinoMessage getPosition(){
      Utility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = ArduinoValue::STATUS;
        packet.type_value = ArduinoValue::POSITION;
        packet.value = position;

      return packet; 
    }

    Utility::ArduinoMessage getVelocity(){
      Utility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = ArduinoValue::STATUS;
        packet.type_value = ArduinoValue::VELOCITY;
        packet.value = velocity;

      return packet; 
    }

    void update(double position, double velocity){
      this->position = position;
      this->velocity = velocity;
    }

    void update(){
      set_angle(control_value);

      position = control_value;
    }

    void off(){
      set_angle(0);
    }
};


#endif
