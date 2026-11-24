#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor
{ 
    public:
        TemperatureSensor(const uint8_t pin);
        void begin();
        void loop();
        float getTemperature();
        bool targetTemperatureReached(const uint8_t minTarget);
        bool SensorOk();
    private:
        const uint8_t _sensorIndex;
        OneWire _oneWire;
        DallasTemperature _dallasTemperature; 
        unsigned long _requestTime = 0;
        bool _measuring = false;
        float _temperature = DEVICE_DISCONNECTED_C; // Dallas def value -127
};

#endif