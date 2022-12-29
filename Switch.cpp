#include "driver/gpio.h"
#include "switch.h"
#include "esp_timer.h"
#include "string.h"

Switch::Switch() {
    tOn=tOff=0;
    toggleMode=true;
    binary=true;
    changeState(false);
}

void Switch::changeState(bool s) {
    gpio_set_level(outputpin,s);
    tLastChange=esp_timer_get_time();
    char msg[4];
    if(s) strcpy(msg,"ON"); else strcpy(msg,"OFF");
    Base::publish(msg); 
}

void Switch::run(bool input) {
    bool state=gpio_get_level(outputpin);
    if(toggleMode) {
        if(input != lastReading) {
            changeState(!gpio_get_level(outputpin));
            lastReading=input;
        }
        return;
    }

    if(tOn==0) {
        if(input != gpio_get_level(outputpin)) changeState(input);            
        return;
    }

    //cycle case
    if(cycle) {
        int64_t now=esp_timer_get_time();
        if(gpio_get_level(outputpin)) {
            if((now-tLastChange)>tOn) changeState(false);
        } else {
            if((now-tLastChange)>tOff) {
                changeState(true);
                cycle=false;
            }
        }   
    } else {
        if(input && !cycle) {cycle=true; changeState(true);} 
    }

}

void Switch::newMqttMsg(char*topic,char*msg) {
    if(strcmp(topic,commandTopic))
        if(strcmp(msg,"ON")) {
            if(toggleMode==true || tOn=0) {
                if(gpio_get_level(outputpin)==0) changeState(true);
                return;
            }
            if(!cycle) {cycle=true; changeState(true);}
        }
        if(strcmp(msg,"OFF")) {
            if(toggleMode==true || tOn=0) {
                if(gpio_get_level(outputpin)==1) changeState(false);
                return;
            }
            if(cycle) {cycle=false; changeState(false);}
        
        }

}