#include "driver/gpio.h"
#include "BinarySensor.h"
#include "string.h"
#include "esp_timer.h"
#include "esp_log.h"
static const char *TAG = "BinarySensor";

using namespace MqttSensors;

BinarySensor::BinarySensor(gpio_num_t _pin)
{
    pin=_pin;
    debounceTime = 50;
    ESP_ERROR_CHECK(gpio_set_direction(pin, GPIO_MODE_INPUT));
    Base();
    tLastReading=0;
}

void BinarySensor::run()
{
    if (debouceTimeElapsed())
        processInput();
}

void BinarySensor::processInput()
{
    bool input=(gpio_get_level(pin)==1);
    
    ESP_LOGD(TAG,"inp= %d, state=%d",input, state);

    if (state != input)
    {
        printf("input: %d state: %d\n", input, state);
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
