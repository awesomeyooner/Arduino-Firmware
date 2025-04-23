#ifndef DRIVER_HPP
#define DRIVER_HPP

namespace drivers{

    class Driver{

        public:

            virtual ~Driver(){}

            virtual void initialize(){}

            virtual void set_percent(double command){}

            virtual void stop(){}
        
        private:


    }; // class Driver
     
} // namespace drivers

#endif