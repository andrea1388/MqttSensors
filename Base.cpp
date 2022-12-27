#include "Base.h"
#include "string.h"
#include "Mqtt.h"

void Base::publish(char *msg) {
    printf("%s->%s\n",mqttStateTopic,msg);
    if(mqtt) mqtt->Publish(mqttStateTopic,msg); 
}