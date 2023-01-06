#include "Sensor.h"

using namespace MqttSensors;

Sensor::Sensor()
{
    value=0;
    minIntervalBetweenMqttUpdate=1;
    minVariationBetweenMqttUpdate=1;
}

void Sensor::run(float v)
{
    if(value!=v) {
        value=v;
        if(true) {
            publish();
        }
    }        
}
void Sensor::publish() {
    char msg[4];
    if(abs(value)>999) value=999;
    sprintf(msg,"%.1f",value);
    Base::publish(msg); 
}