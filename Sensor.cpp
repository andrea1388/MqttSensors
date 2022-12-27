#include "Sensor.h"

Sensor::Sensor()
{
    value=0;
}

void Sensor::run(float v)
{
    if(value!=v) {
        value=v;
        if(mqtt && now>tLastPublish+publishInterval)           Base:publish(msg);
    }        
}
void Sensor::publish() {
    char msg[4];
    if(abs(value)>999) value=999;
    sprintf(msg,"%.1f",value);
    Base::publish(msg); 
}