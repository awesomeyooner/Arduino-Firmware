#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include "utils.hpp"

class Sensor{
  private:
    int pin;

  public:
    String device;
    String type_value;

    double value;

    Sensor(String device, int pin, String type_value){
      this->device = device;
      this->type_value = type_value;
      this->pin = pin;

      value = 0;
    }

    Utility::ArduinoMessage getStatus(){
      Utility::ArduinoMessage packet;

        packet.device = device;
        packet.message_type = MessageType::STATUS;
        packet.type_value = type_value;
        packet.value = value;

      return packet; 
    }

    void update(double value){
      this->value = value;
    }

};


#endif
