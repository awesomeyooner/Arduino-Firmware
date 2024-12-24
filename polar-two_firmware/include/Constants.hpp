#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace hardware_component{
    struct MotorID{
        int inputPin1, inputPin2;
        int channel1, channel2;
    };

    struct EncoderID{
        int channelA;
        int channelB;
    };
}

namespace GeneralConstants{
    const int PWM_HERTZ = 100000;
    const int PWM_RESOLUTION = 12; //bits
    const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 
}

namespace MotorConstants{
    const int ENCODER_PPR = 12;
    const int GEAR_RATIO = 45;
    const int OUTPUT_SHAFT_PPR = ENCODER_PPR * GEAR_RATIO;
    const int MAX_RPM = 130;

    //robot specific stuff
    const hardware_component::MotorID LEFT_MOTOR_ID = {
        .inputPin1 = 12,
        .inputPin2 = 13,
        .channel1 = 0,
        .channel2 = 1
    };

    const hardware_component::MotorID RIGHT_MOTOR_ID = {
        .inputPin1 = 17,
        .inputPin2 = 16,
        .channel1 = 2,
        .channel2 = 3
    };

    const hardware_component::EncoderID LEFT_FRONT_ENCODER_ID = {
        .channelA = 19,
        .channelB = 18
    };

    const hardware_component::EncoderID LEFT_BACK_ENCODER_ID = {
        .channelA = 23,
        .channelB = 22
    };

    const hardware_component::EncoderID RIGHT_FRONT_ENCODER_ID = {
        .channelA = 26,
        .channelB = 27
    };

    const hardware_component::EncoderID RIGHT_BACK_ENCODER_ID = {
        .channelA = 34,
        .channelB = 35
    };
}

#endif
