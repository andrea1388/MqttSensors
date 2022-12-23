#include "driver/gpio.h"
#include "Mqtt.h"
#include "BinarySensor.h"
#include "Base.h"

class Switch:Base {
    BinarySensor *input;
    uint8_t onTime;
    bool toggleMode;
    gpio_num_t outputpin;
}

