#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{ 
    public:
        Sensor(const uint8_t pin);
        void begin();
        bool isDetecting();
        bool notDetecting();
    private:
        const uint8_t _pin;
};

#endif