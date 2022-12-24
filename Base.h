#include "driver/gpio.h"
#include "Mqtt.h"

class Base {
    public:
        Mqtt *mqtt;
        char *mqttStateTopic;

        virtual void run(float v)=0;
        bool state;
        float value;
    protected:
        void publish();
        bool binary;
        uint8_t mqttUpdateInterval; // in seconds
        float mqttMinUpdateOffset; 
        
}