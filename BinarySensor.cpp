#include "driver/gpio.h"
#include "BinarySensor.h"
#include "string.h"
#include "esp_timer.h"

using namespace MqttSensors;

BinarySensor::BinarySensor(gpio_num_t _pin)
{
    pin=_pin;
    debounceTime = 50;
    gpio_set_direction(pin, GPIO_MODE_INPUT);
}

void BinarySensor::run()
{
    if (debouceTimeElapsed())
        processInput();
}

void BinarySensor::processInput()
{
    bool input=gpio_get_level(pin);

    if (state != input)
    {
        state = input;
        char msg[4];
        if (state)
            strcpy(msg,"ON");
        else
            strcpy(msg,"OFF");
        publish(msg);
    }
}

bool BinarySensor::debouceTimeElapsed()
{
    int64_t now = esp_timer_get_time();
    if ((now - tLastReading) > debounceTime*1000) {
        tLastReading=now;
        return true;
    }
    return false;
}
