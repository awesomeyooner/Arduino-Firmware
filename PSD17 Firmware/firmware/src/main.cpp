#include <Arduino.h>
#include "hardware_manager.hpp"

managers::HardwareManager *hardware_manager = managers::HardwareManager::get_instance();

void setup() {
  // put your setup code here, to run once:

  hardware_manager->initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  hardware_manager->update();
}