#include <Arduino.h>
#include "devices/motor.hpp"
#include "devices/l298n.hpp"
#include "devices/led/builtin_led.hpp"

#define PIN_ENA 1
#define PIN_IN1 2
#define PIN_IN2 3

#define PIN_CHA 10
#define PIN_CHB 9

BuiltinLED led;

hardware_component::L298N driver(PIN_ENA, PIN_IN1, PIN_IN2);
hardware_component::QuadratureEncoder encoder(PIN_CHA, PIN_CHB);

hardware_component::Motor motor;

void setup() {
    led.initialize();

    driver.initialize();
    encoder.initialize([](){encoder.handleA();}, [](){encoder.handleB();});

    motor.link_driver(&driver);
    motor.link_encoder(&encoder);
}

void loop() {

}
