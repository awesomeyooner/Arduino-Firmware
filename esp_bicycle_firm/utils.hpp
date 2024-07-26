#ifndef UTILITY_UTILS_HPP
#define UTILITY_UTILS_HPP

namespace ArduinoValue{
  constexpr char STATUS[] = "status";

  constexpr char CONTROL[] = "control";

  constexpr char CONFIG[] = "config";

  constexpr char UNCONFIGURED[] = "unconfigured";

  //type_value macros
  constexpr char VELOCITY[] = "velocity";

  constexpr char POSITION[] = "position";

  constexpr char PERCENT[] = "percent";

  constexpr char VOLTAGE[] = "voltage";
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
