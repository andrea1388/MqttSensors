#include "Sensor.h"

Sensor::Sensor()
{
    value=0;
    binary=false;
}

Sensor::run(float v)
{
    if(value!=v) publish();
    value=v;

}