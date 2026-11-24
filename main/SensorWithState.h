#ifndef SENSORWITHSTATE_H
#define SENSORWITHSTATE_H

#include "Sensor.h"

class SensorWithState : public Sensor
{
    public:
        explicit SensorWithState(uint8_t pin) : Sensor(pin) {}
        
        void begin();
        bool changeDetected();

    private:
        bool _wasDetecting;
};

#endif