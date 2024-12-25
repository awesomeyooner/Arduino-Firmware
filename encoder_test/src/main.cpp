#include <Arduino.h>
#include "../include/devices/Encoder.hpp"
#include <string>
#include <esp32-hal-ledc.h>
#include <Arduino.h>
#include <map>
#include "esp_timer.h"
#include "../include/util/Utility.hpp"
#include "../include/devices/Motor.hpp"

// hardware_component::Encoder left_encoder(23, 22);
// hardware_component::Encoder right_encoder(19, 18);

hardware_component::Motor motor(14, 12, 13, 0, 1, 2);

void setup() {
  // Configure serial transport
  Serial.begin(115200);

  delay(3000);

  motor.initialize();

  // left_encoder.initialize();
  // right_encoder.initialize();

  delay(2000);
}

void loop() {
  // left_encoder.update();
  // right_encoder.update();

  // std::string output = "Left: " + std::to_string(left_encoder.position.value) + "    " + "Right: " + std::to_string(right_encoder.position.value);
  // Serial.println(output.c_str());
  // delay(20);

  motor.setSpeed(-0.1);
}