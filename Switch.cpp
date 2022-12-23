#include "driver/gpio.h"
#include "switch.h"

Switch::Switch() {
    onTime=0;
    toggleMode=true;
    changeState(false);
    binary=true;

}

Switch::changeState(bool s) {
    value=s;
    gpio_set_level(pin,state);
    tLastChange=now;
    publish();
}

Switch::run(float v) {
    if(toggle) {
        if(v && !lastReading) {
            changeState(!value);
            lastReading=v;
        }
    }
    else {

    }
    if(v && !previnput) {
        changeState(ns);
    }
    if(state) {
        if(tLastChange>onTime) {
            changeState(false);
        }
    }

}

void BinarySensor::publish() {
    char msg[4];
    if(!mqtt) return;
    if(state) strcpy(msg,"ON"); else strcpy(msg,"OFF");
    mqtt.Publish(mqttStateTopic,msg); 
}