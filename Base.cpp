#include "Base.h"
#include "string.h"
#include "Mqtt.h"
#include "esp_log.h"
static const char *TAG = "Base";

using namespace MqttSensors;

Base::Base() {
    mqttClient=0;
    mqttStateTopic=0;
}

void Base::publish(char *msg) {
    ESP_LOGI(TAG, "%s->%s\n",mqttStateTopic,msg);
    if(!mqttStateTopic) {ESP_LOGE(TAG,"missing topic"); return;}
    if(!msg) {ESP_LOGE(TAG,"missing msg"); return;}
    if(!mqttClient) return;
    if(mqttClient) mqttClient->Publish(mqttStateTopic,msg); 
}