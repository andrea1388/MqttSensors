# pragma once
#include "driver/gpio.h"
#include "Base.h"
namespace MqttSensors {
    class BinarySensor:public Base {
        public:
            BinarySensor(gpio_num_t pin);
            uint8_t debounceTime;
            void run();
            bool state;
            gpio_num_t pin;

        private:
            int64_t tLastReading;
            void processInput();
            bool debouceTimeElapsed();
    };
}