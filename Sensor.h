# pragma once
#include "Base.h"
namespace MqttSensors {
    class Sensor:public Base {
        public:
            void run(float);
            Sensor();
            uint16_t minIntervalBetweenMqttUpdate; /*!< interval expressed in seconds */
            uint8_t minVariationBetweenMqttUpdate; 

        private:
            void publish();
            float lastValuePublished;
            int64_t tLastPublish;
    };
}