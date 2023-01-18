#include "Sensor.h"
#include "esp_timer.h"

using namespace MqttSensors;

Sensor::Sensor()
{
    value=0;
    minIntervalBetweenMqttUpdate=1;
    minVariationBetweenMqttUpdate=1;
    Base();
}

void Sensor::run(float v)
{
    int64_t now=esp_timer_get_time();
    if(value!=v) {
        value=v;
        if(abs(value-lastValuePublished)>minVariationBetweenMqttUpdate || (now-tLastPublish)>minIntervalBetweenMqttUpdate*1000000) {
            publish();
        }
    }        
    
}
void Sensor::publish() {
    char msg[6];
    if(abs(value)>999) value=999;
    sprintf(msg,"%.1f",value);
    Base::publish(msg);
    lastValuePublished=value;
    tLastPublish=esp_timer_get_time();
}