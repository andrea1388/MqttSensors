#include "Base.h"
#include "string.h"
#include "Mqtt.h"

void Base::publish() {
    char msg[6];
    if(binary) {
        if(value==1) strcpy(msg,"ON"); else strcpy(msg,"OFF");
        if(mqtt) mqtt->Publish(mqttStateTopic,msg); 
    }
    else {
        if(abs(value)>999) value=999;
        sprintf(msg,"%.1f",value);
        if(mqtt && now>tLastPublish+publishInterval) mqtt->Publish(mqttStateTopic,msg); 

    }
    printf("%s %s\n",mqttStateTopic,msg);
}