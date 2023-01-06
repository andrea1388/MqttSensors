# pragma once
#include "driver/gpio.h"
#include "Mqtt.h"
#include "BinarySensor.h"
#include "Base.h"

namespace MqttSensors {
    class Switch:Base {
        public:
            bool toggleMode;
            bool state;
            uint32_t tOn; /*!< On time interval expressed in milliseconds */
            uint32_t tOff; /*!< Off time interval expressed in milliseconds */
            gpio_num_t pin;
            void run(bool);
            void newMqttMsg(char*topic,char*msg);
            char *commandTopic;
            Switch(gpio_num_t pin);
        private:
            void changeState(bool);
            bool lastReading;
            void publish();
            int64_t tLastChange;
            bool cycle;
    };
}
