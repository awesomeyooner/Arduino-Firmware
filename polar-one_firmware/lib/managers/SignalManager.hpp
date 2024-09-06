#ifndef SIGNALMANAGER_SIGNALMANAGER_HPP
#define SIGNALMANAGER_SIGNALMANAGER_HPP

#include "utils.hpp"
#include "PCA9685.h"
#include "Wire.h"
#include <string>

class SignalManager{

  private:
    static SignalManager instance;

    PCA9685 pwmController;

  public:

    SignalManager(){}

    static SignalManager getInstance(){
      return instance;
    }

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

#endif