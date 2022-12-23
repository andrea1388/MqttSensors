#include "Base.h"
#include "string.h"
#include "Mqtt.h"

void Base::publish() {
    char msg[4];
    if(!mqtt) return;
    sprintf(msg,"%.1f",Tp);
    if(state) strcpy(msg,"ON"); else strcpy(msg,"OFF");
    mqtt->Publish(mqttStateTopic,msg); 
}