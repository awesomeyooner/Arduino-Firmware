#ifndef SUBSYSTEM_SUBSYSTEM_HPP
#define SUBSYSTEM_SUBSYSTEM_HPP

#include <vector>
#include "utils.hpp"
#include "Motor.hpp"
#include "Servo.hpp"
#include "Sensor.hpp"
#include "Constants.hpp"

namespace subsystem{

    class Subsystem{

        private:    

        public:

            Subsystem(){}

            virtual std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend(){return {};}

            virtual void applyToAll(ArduinoUtility::ArduinoMessage message){}

            virtual void updateAll(){}

    };
}

#endif