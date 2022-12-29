#include "driver/gpio.h"
#include "Mqtt.h"
#include "BinarySensor.h"
#include "Base.h"

class Switch:Base {
    public:
        bool toggleMode;
        uint8_t tOn;
        uint8_t tOff;
        gpio_num_t outputpin;
        void run(bool);
        void newMqttMsg(char*topic,char*msg);
        char *commandTopic;
    private:
        void changeState(bool);
        bool lastReading;
        void publish();
        int64_t tLastChange;
        bool cycle;
};

