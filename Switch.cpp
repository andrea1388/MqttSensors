#include "driver/gpio.h"
#include "Switch.h"
#include "esp_timer.h"
#include "string.h"

using namespace MqttSensors;

Switch::Switch(gpio_num_t _pin) {
    pin=_pin;
    tOn=tOff=0;
    toggleMode=true;
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin,0);
    tLastChange=0;
}

void Switch::changeState(bool s) {
    gpio_set_level(pin,s);
    tLastChange=esp_timer_get_time();
    char msg[4];
    if(s) strcpy(msg,"ON"); else strcpy(msg,"OFF");
    Base::publish(msg); 
}

void Switch::run(bool input) {
    bool state=gpio_get_level(pin);
    if(toggleMode) {
        if(input != lastReading) {
            changeState(!state);
            lastReading=input;
        }
        return;
    }

    if(tOn==0) {
        if(input != gpio_get_level(pin)) changeState(input);            
        return;
    }

    //cycle case
    if(cycle) {
        int64_t now=esp_timer_get_time();
        if(gpio_get_level(pin)) {
            if((now-tLastChange)>tOn*1000) changeState(false);
        } else {
            if((now-tLastChange)>tOff*1000) {
                changeState(true);
                cycle=false;
            }
        }   
    } else {
        if(input && !cycle) {cycle=true; changeState(true);} 
    }

}

void Switch::newMqttMsg(char*topic, char*msg) {
    if(!strcmp(topic,commandTopic)) return;
 
    if(strcmp(msg,"ON")) {
        if(toggleMode==true || tOn==0) {
            if(gpio_get_level(pin)==0) changeState(true);
            return;
        }
        if(!cycle) {cycle=true; changeState(true);}
    }
    if(strcmp(msg,"OFF")) {
        if(toggleMode==true || tOn==0) {
            if(gpio_get_level(pin)==1) changeState(false);
            return;
        }
        if(cycle) {cycle=false; changeState(false);}
    
    }

}