#include <Arduino.h>
#include "../include/devices/Encoder.hpp"
#include <string>
#include <esp32-hal-ledc.h>
#include <Arduino.h>
#include <map>
#include "esp_timer.h"
#include "../include/util/Utility.hpp"

hardware_component::Encoder encoder(23, 22);

void setup() {
  // Configure serial transport
  Serial.begin(115200);
  encoder.initialize();

  delay(2000);
}

void loop() {
  encoder.update();
  // Serial.println(encoder.velocity.value);

}