#include "driver/gpio.h"
#include "Mqtt.h"

class Base {
    public:
        Mqtt *mqtt;
        char *mqttStateTopic;
        bool state;
        float value;
    protected:
        void publish(char*);
        bool binary;
        uint8_t mqttUpdateInterval; // in seconds
        float mqttMinUpdateOffset; 
        
}