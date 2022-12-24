#include "driver/gpio.h"
#include "BinarySensor.h"

BinarySensor::BinarySensor() {
    debounceTime=50;
}

void BinarySensor:run(float input) {
    now=(esp_timer_get_time()/1000);
    
    if(debouceTimeElapsed())
        processInput();
}

void BinarySensor::processInput() {
    ns=gpio_get_level(pin);
    if(state!=ns) {
        state=ns;
        tLastReading=now;
        publish();
    }
}

inline bool BinarySensor::debouceTimeElapsed() {

    return((now-tLastReading)>debounceTime);
}

