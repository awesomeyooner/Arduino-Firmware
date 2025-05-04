#include <Arduino.h>

#include "devices/led/builtin_led.hpp"

BuiltinLED led;

void setup() {
    led.initialize();
}

void loop() {
    led.turn_on();
    delay(500);
    led.turn_off();
    delay(500);
}
