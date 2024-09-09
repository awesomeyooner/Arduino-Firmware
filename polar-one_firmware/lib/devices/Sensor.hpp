#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include "utils.hpp"
#include <string>

namespace hardware_component{

  struct SensorConfig{
    std::string device;
    int pin;
    std::string type_value;

    SensorConfig(std::string device, int pin, std::string type_value) : device(device), pin(pin), type_value(type_value){}
    SensorConfig(std::string device, std::string type_value) : device(device), pin(0), type_value(type_value){}
    SensorConfig(){}
  };

  class Sensor : public Device{
    private:
      SensorConfig config;

    public:
      hardware_component::InterfaceValue status = {MessageType::UNCONFIGURED};

      Sensor(SensorConfig config) : Device(config.device){
        this->config = config;

        status.interface_type = config.type_value;
      }

      ArduinoUtility::ArduinoMessage getStatus(hardware_component::InterfaceValue status) override{
        ArduinoUtility::ArduinoMessage packet;

          packet.device = device;
          packet.message_type = MessageType::STATUS;
          packet.type_value = status.interface_type;
          packet.value = status.value;

        return packet; 
      }

      void update(double value){
        status.value = value;
      }

  };
}

#endif
