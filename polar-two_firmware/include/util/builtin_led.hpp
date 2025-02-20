#ifndef BUILTIN_LED_HPP
#define BUILTIN_LED_HPP

#include <Arduino.h>

#define LED_PIN 2

class BuiltinLED{

    private:

    public:

        void initialize(){
            pinMode(LED_PIN, OUTPUT);
        }

        void toggle(bool turnOn){
            turnOn ? turn_on() : turn_off();
        }

        void turn_on(){
            digitalWrite(LED_PIN, HIGH);
        }

        void turn_off(){
            digitalWrite(LED_PIN, LOW);
        }
};


#endif