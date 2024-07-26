#ifndef MOTOR_MOTOR_HPP
#define MOTOR_MOTOR_HPP

#include "utils.hpp"
#include "SignalManager.hpp"

class Motor{
  private:
    int channel;
    int max_forward;
    int neutral;
    int max_reverse;

    SignalManager* pwmController;

  public:
    String device;
    String control_mode;
    double control_value;

    double position;
    double velocity;

    bool inverted;

    Motor(String device, int channel, SignalManager* pwmController, int max_forward, int neutral, int max_reverse){
      this->device = device;

      this->channel = channel;

      this->pwmController = pwmController;

      this->max_forward = max_forward;
      this->neutral = neutral;
      this->max_reverse = max_reverse;

      control_mode = ArduinoValue::PERCENT;
      control_value = 0;

      position = 0;
      velocity = 0;
      inverted = false;
    }

    void set_speed(double percent){
      if(percent > 1)
        percent = 1;
      else if(percent < -1)
        percent = -1;

      uint16_t signal = map(percent * 10000, -10000, 10000, max_reverse, max_forward);

      pwmController->sendSignal(
        channel, 
        signal
      );      

      velocity = signal;
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
      set_speed(control_value);

      //velocity = control_value;
    }

    void off(){
      set_speed(0);
    }
};


#endif
