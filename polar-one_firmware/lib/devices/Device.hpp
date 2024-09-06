#ifndef DEVICE_DEVICE_HPP
#define DEVICE_DEVICE_HPP

#include "utils.hpp"
#include <string>
#include <vector>
#include "utils.hpp"

namespace hardware_component{

  class Device{

    public:
      std::string device;

      Device(std::string device){
        this->device = device;
      }

      virtual void apply(ArduinoUtility::ArduinoMessage message){}

      virtual void update(){}

      virtual ArduinoUtility::ArduinoMessage getStatus(hardware_component::InterfaceValue status){return {};}

  };
}

#endif
