#ifndef DEVICE_DEVICE_HPP
#define DEVICE_DEVICE_HPP

#include "utils.hpp"

class Device{

  public:
    String device;

    Device(String device){
      this->device = device;
      this->type_value = type_value;
      this->pin = pin;

      value = 0;
    }

    void update();

    

};


#endif
