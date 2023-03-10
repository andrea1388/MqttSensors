#include "driver/gpio.h"
#include "Switch.h"
#include "esp_timer.h"
#include "string.h"
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
static const char *TAG = "Switch";

using namespace MqttSensors;

Switch::Switch(gpio_num_t _pin) {
    pin=_pin;
    tOn=tOff=0;
    on=off=false;
    toggleMode=false;
    ESP_ERROR_CHECK(gpio_reset_pin(pin));
    ESP_ERROR_CHECK(gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT));
    gpio_set_level(pin,0);
    tLastChange=0;
    Base();
}

void Switch::changeState(bool s) {
    if(s) gpio_set_level(pin,1); else gpio_set_level(pin,0); 
    tLastChange=esp_timer_get_time();
    char msg[4];
    if(s) strcpy(msg,"ON"); else strcpy(msg,"OFF");
    Base::publish(msg); 
}

void Switch::run(bool inp) {
    bool out=(gpio_get_level(pin)==1);
    int64_t now=esp_timer_get_time();
    

    uint8_t modo;
    if(toggleMode) modo=1; else if(!tOn) modo=2; else modo=3;
    ESP_LOGD(TAG,"switch: %s, modo: %u input: %d previnp: %d out: %d time: %lld lastchange: %lld Ton:%ld Toff:%ld\n", mqttStateTopic, modo, inp,previnp,out,now/1000,tLastChange/1000,tOn,tOff);


    if(!out) {
        if(on) { on=false;changeState(true);return;}
        switch (modo)
        {
        case 1:
        case 2:
            if(inp && !previnp) {changeState(true);break;}
            break;
        case 3:
            if((inp && !previnp) || (inp && (now-tLastChange)>tOff*1000)) { changeState(true);break;}
            break;
        default:
            assert(0);
            break;
        }
    } 
    else {
        if(off) { off=false;changeState(false);return;}
        switch (modo)
        {
        case 1:
            if(inp && !previnp) { changeState(false);break;}
            if(tOn && (now-tLastChange)>tOn*1000) { changeState(false);break;}
            break;
        case 2:
        case 3:
            if(!inp && previnp) { changeState(false);break;}
            if(tOn && (now-tLastChange)>tOn*1000) { changeState(false);break;}
            break;
        
        default:
            assert(0);
            break;
        }
    }
    previnp=inp;
}

void Switch::newMqttMsg(char*topic, char*msg) {
    if(!strcmp(topic,commandTopic)) return; 
    if(strcmp(msg,"ON")) on=true;
    if(strcmp(msg,"OFF")) off=true;
    ESP_LOGD(TAG,"Switch::newMqttMsg: %s on: %d off: %d\n", msg, on, off);


}