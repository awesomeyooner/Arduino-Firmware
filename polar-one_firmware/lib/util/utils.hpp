#ifndef UTILS_UTILS_HPP
#define UTILS_UTILS_HPP

#include <string>

namespace ArduinoUtility{
  struct ArduinoMessage{
    std::string device = ""; //(id) left, right, voltage_sensor
    std::string message_type = ""; //status, control, config
    std::string type_value = ""; //velocity, position, percent, inverted
    double value = 0; //whatever value you want to send
  };
}

namespace hardware_component{
    struct InterfaceValue{
        std::string interface_type;
        double value;

        InterfaceValue(std::string if_type, double val) : interface_type(if_type), value(val){}
        InterfaceValue(std::string if_type) : interface_type(if_type), value(0.0){}
        InterfaceValue() : interface_type(""), value(0.0){}
    };
}

namespace MessageType{

  const std::string STATUS = "status";

  const std::string CONTROL = "control";

  const std::string CONFIG = "config";

  const std::string UNCONFIGURED = "unconfigured";
}

namespace TypeValue{
  const std::string VELOCITY = "velocity";

  const std::string POSITION = "position";

  const std::string EFFORT = "effort";

  const std::string VOLTAGE = "voltage";

  const std::string RAW = "raw";

  const std::string LOWER_BOUND = "lower_bound";

  const std::string NEUTRAL = "neutral";

  const std::string UPPER_BOUND = "upper_bound";
}

#endif  // ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
