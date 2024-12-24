#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace GeneralConstants{
    const int PWM_HERTZ = 10000;
    const int PWM_RESOLUTION = 12; //bits
    const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 
}

namespace MotorConstants{
    const int ENCODER_PPR = 12;
    const int GEAR_RATIO = 45;
    const int OUTPUT_SHAFT_PPR = ENCODER_PPR * GEAR_RATIO;
    const int MAX_RPM = 130;
}

#endif
