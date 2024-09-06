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
  constexpr char STATUS[] = "status";

  constexpr char CONTROL[] = "control";

  constexpr char CONFIG[] = "config";

  constexpr char UNCONFIGURED[] = "unconfigured";
}

namespace TypeValue{
  constexpr char VELOCITY[] = "velocity";

  constexpr char POSITION[] = "position";

  constexpr char EFFORT[] = "effort";

  constexpr char VOLTAGE[] = "voltage";

  constexpr char RAW[] = "raw";

  constexpr char LOWER_BOUND[] = "lower_bound";

  constexpr char NEUTRAL[] = "neutral";

  constexpr char UPPER_BOUND[] = "upper_bound";
}

#endif  // ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
