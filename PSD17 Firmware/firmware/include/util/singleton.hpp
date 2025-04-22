#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>

namespace util{

    template <typename T>

    class Singleton{

        public:

            static inline T instance;

            Singleton(){
               
            }

            static T* get_instance(){
                return &instance;
            }

        private: 


    }; //class Singleton

} //namespace my_namespace

#endif