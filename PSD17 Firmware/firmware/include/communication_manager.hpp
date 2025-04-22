#ifndef COMMUNICATION_MANAGER_HPP
#define COMMUNICATION_MANAGER_HPP

#include "util/singleton.hpp"
#include "Wire.h"

namespace managers{

    class CommunicationManager : public util::Singleton<CommunicationManager>{

        public:

            CommunicationManager(){}

            void initialize(){
                Wire.begin();
            }

            

        private:


    }; // class CommunicationManager

} // namespace managers

#endif // COMMUNICATIN_MANAGER_HPP