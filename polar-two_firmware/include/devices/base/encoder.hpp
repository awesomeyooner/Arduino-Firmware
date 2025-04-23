#ifndef ENCODER_HPP
#define ENCODER_HPP

namespace encoders{

    class Encoder{

        public:
            virtual ~Encoder(){}

            virtual void initialize(){}

            virtual double get_position(){}

            virtual double get_velocity(){}


    }; // class Encoder
} // namespace encoders

#endif // ENCODER_HPP