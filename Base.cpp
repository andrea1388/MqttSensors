#include "Base.h"
#include "string.h"
#include "Mqtt.h"

using namespace MqttSensors;

void Base::publish(char *msg) {
    printf("%s->%s\n",mqttStateTopic,msg);
    if(mqttClient) mqttClient->Publish(mqttStateTopic,msg); 
}