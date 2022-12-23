#include "driver/gpio.h"
#include "Mqtt.h"

class Base {
    public:
        Mqtt *mqtt;
        char *mqttStateTopic;

        void run();
        bool state;
        float value;
    private:
        void publish();
}