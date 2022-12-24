#include "driver/gpio.h"
#include "Mqtt.h"
#include "BinarySensor.h"
#include "Base.h"

class Switch:Base {
    public:
        BinarySensor *input;
        uint8_t onTime;
        bool toggleMode;
        uint8_t tOn;
        uint8_t tOff;
        gpio_num_t outputpin;
}

