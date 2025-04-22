#ifndef DRIVER_HPP
#define DRIVER_HPP

namespace drivers{

    class Driver{

        public:

            virtual ~Driver(){}

            virtual void initialize(){}
            virtual void update(){}

            virtual void set_percent(double command){}
        
        private:


    }; // class Driver
     
} // namespace drivers

#endif