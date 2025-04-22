#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace hardware_component{
    struct MotorID{
        int enablePin, inputPin1, inputPin2;
        int channelEnable, channel1, channel2;
    };

    struct EncoderID{
        int channelA;
        int channelB;
    };
}

namespace GeneralConstants{
    const int TIMEOUT_MS = 500;
    const int PWM_HERTZ = 100000;
    const int PWM_RESOLUTION = 8; //bits
    const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 
}

namespace MotorConstants{
    const int ENCODER_CPR = 12 * 4; //12ppr, 4 per
    const int GEAR_RATIO = 45;
    const int OUTPUT_SHAFT_CPR = ENCODER_CPR * GEAR_RATIO;
    const int MAX_RPM = 130;

    //robot specific stuff
    const hardware_component::MotorID LEFT_MOTOR_ID = {
        .enablePin = 5,
        .inputPin1 = 17,
        .inputPin2 = 16,
        .channelEnable = 3,
        .channel1 = 4,
        .channel2 = 5
    };
    
    const hardware_component::MotorID RIGHT_MOTOR_ID = {
        .enablePin = 14,
        .inputPin1 = 12,
        .inputPin2 = 13,
        .channelEnable = 0,
        .channel1 = 1,
        .channel2 = 2
    };

    const hardware_component::EncoderID LEFT_ENCODER_ID = {
        .channelA = 19,
        .channelB = 18
    };

    const hardware_component::EncoderID RIGHT_ENCODER_ID = {
        .channelA = 26,
        .channelB = 27
    };
}

#endif
