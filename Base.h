# pragma once
#include "driver/gpio.h"
#include <Mqtt.h>

namespace MqttSensors {
    class Base {
        public:
            Mqtt *mqttClient;
            char *mqttStateTopic;
            float value;
            Base();
        protected:
            void publish(char*msg);
            uint8_t mqttUpdateInterval; // in seconds
            float mqttMinUpdateOffset; 
            
    };
}
