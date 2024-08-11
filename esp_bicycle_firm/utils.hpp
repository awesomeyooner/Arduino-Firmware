#ifndef UTILITY_UTILS_HPP
#define UTILITY_UTILS_HPP

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

  constexpr char LOWER_BOUND[] = "lower_bound";

  constexpr char NEUTRAL[] = "neutral";

  constexpr char UPPER_BOUND[] = "upper_bound";
}

class Utility{

  public:
    struct ArduinoMessage{
      String device = "";
      String message_type = "";
      String type_value = "";
      double value = 0;
    };
    

};


#endif
