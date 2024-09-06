#ifndef SUPERSTRUCTURE_SUPERSTRUCTURE_HPP
#define SUPERSTRUCTURE_SUPERSTRUCTURE_HPP

#include "utils.hpp"
#include <string>
#include "Drive.hpp"
#include "Subsystem.hpp"

namespace subsystem{

    class Superstructure : public Subsystem{

        private:
            static Superstructure instance;

            std::vector<subsystem::Subsystem*> subsystems;

            
        public:
            Drive drive;// = Drive::getInstance();
            
            Superstructure() : Subsystem(){
                subsystems.emplace_back(&drive);
            }

            static Superstructure getInstance(){
                return instance;
            }
            
            std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend(){
                std::vector<ArduinoUtility::ArduinoMessage> messages;

                for(Subsystem* subsystem : subsystems){
                    std::vector<ArduinoUtility::ArduinoMessage> currentCommandPacket = subsystem->getMessagesToSend();

                    messages.insert(messages.end(), currentCommandPacket.begin(), currentCommandPacket.end());
                }
                
                return messages;
            }

            void updateAll() override{
                for(Subsystem* subsystem : subsystems){
                    subsystem->updateAll();
                }
            }
    };
}

#endif