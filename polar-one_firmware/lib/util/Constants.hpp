#ifndef CONSTANTS_CONSTANTS_HPP
#define CONSTANTS_CONSTANTS_HPP

#include <string>
#include "Sensor.hpp"
#include "Servo.hpp"
#include "Motor.hpp"
#include "Heartbeat.hpp"

namespace MotorConstants{
  const std::string DEVICE = "virtual_rear_wheel_joint";
  const std::string COMMAND_INTERFACE = TypeValue::VELOCITY;

  const int MAX_FORWARD = 500;
  const int NEUTRAL = 360;
  const int MAX_REVERSE = 280;

  const int CHANNEL = 0;

  //const hardware_component::MotorConfig CONFIG = {DEVICE, CHANNEL, MAX_FORWARD, NEUTRAL, MAX_REVERSE};
}

namespace ServoConstants{
  const std::string DEVICE = "virtual_front_wheel_joint";
  const std::string COMMAND_INTERFACE = TypeValue::POSITION;

  const int MAX_LEFT = 520;
  const int NEUTRAL = 380;
  const int MAX_RIGHT = 260;

  const int CHANNEL = 1;

  const hardware_component::ServoConfig CONFIG = {DEVICE, CHANNEL, MAX_LEFT, NEUTRAL, MAX_RIGHT};
}

namespace VoltageSensorConstants{
  const std::string DEVICE = "voltage_sensor";
  const int CHANNEL = 1;
  const std::string TYPE_VALUE = TypeValue::VOLTAGE;  

  const hardware_component::SensorConfig CONFIG = {DEVICE, CHANNEL, TYPE_VALUE};
}


namespace HeartbeatConstants{
  const std::string DEVICE = "heartbeat";

  const int PIN = 2; //led pin

  const hardware_component::HeartbeatConfig CONFIG = {DEVICE, PIN};  
}

#endif