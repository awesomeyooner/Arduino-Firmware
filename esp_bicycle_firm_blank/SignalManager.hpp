#ifndef SIGNALMANAGER_SIGNALMANAGER_HPP
#define SIGNALMANAGER_SIGNALMANAGER_HPP

#include "utils.hpp"
#include "PCA9685.h"
#include "Wire.h"


class SignalManager{

  private:
    PCA9685 pwmController;

  public:

    SignalManager(){
    }

    void init(){
      // Wire.begin();

      // pwmController.resetDevices();
      // pwmController.init();
      // pwmController.setPWMFrequency(60);
    }

    void sendSignal(int channel, uint16_t value){
      //pwmController.setChannelPWM(channel, value);
    }

};

#endif