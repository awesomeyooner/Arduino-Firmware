#ifndef SIGNALMANAGER_SIGNALMANAGER_HPP
#define SIGNALMANAGER_SIGNALMANAGER_HPP

#include "utils.hpp"
#include "PCA9685.h"
#include "Wire.h"
#include <string>

namespace managers{

  class SignalManager{

    private:

      PCA9685 pwmController;

    public:

      static SignalManager instance;

      SignalManager(){}
      
      static SignalManager* getInstance();

      void init(){
        Wire.begin();

        pwmController.resetDevices();
        pwmController.init();
        pwmController.setPWMFrequency(60);
      }

      void sendSignal(int channel, uint16_t value){
        pwmController.setChannelPWM(channel, value);
      }

  };
  
  managers::SignalManager managers::SignalManager::instance;

  managers::SignalManager* managers::SignalManager::getInstance(){
    return &instance;
  }
}

#endif