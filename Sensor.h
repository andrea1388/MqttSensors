# pragma once
#include "Base.h"
namespace MqttSensors {
    class Sensor:public Base {
        public:
            void run(float);
            Sensor();
            uint8_t minIntervalBetweenMqttUpdate; /*!< interval expressed in minutes */
            uint8_t minVariationBetweenMqttUpdate; 

        private:
            void publish();
    };
}