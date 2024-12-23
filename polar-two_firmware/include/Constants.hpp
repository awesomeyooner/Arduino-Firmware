#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "devices/Encoder.hpp"
#include "devices/Motor.hpp"

namespace GeneralConstants{
    const int PWM_HERTZ = 100000;
    const int PWM_RESOLUTION = 8; //bits


}

namespace MotorConstants{
    const int ENCODER_PPR = 12;
    const int GEAR_RATIO = 45;
    const int OUTPUT_SHAFT_PPR = ENCODER_PPR * GEAR_RATIO;
    const int MAX_RPM = 130;

    //robot specific stuff
    const hardware_component::MotorID LEFT_MOTOR_ID = {
        .inputPin1 = 1,
        .inputPin2 = 2,
        .channel1 = 0,
        .channel2 = 1
    };

    const hardware_component::MotorID RIGHT_MOTOR_ID = {
        .inputPin1 = 3,
        .inputPin2 = 4,
        .channel1 = 2,
        .channel2 = 3
    };

    const hardware_component::EncoderID LEFT_FRONT_ENCODER_ID = {
        .channelA = 23,
        .channelB = 22
    };

    const hardware_component::EncoderID LEFT_BACK_ENCODER_ID = {
        .channelA = 23,
        .channelB = 22
    };

    const hardware_component::EncoderID RIGHT_FRONT_ENCODER_ID = {
        .channelA = 23,
        .channelB = 22
    };

    const hardware_component::EncoderID RIGHT_BACK_ENCODER_ID = {
        .channelA = 23,
        .channelB = 22
    };
}

#endif
