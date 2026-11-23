#ifndef QUALITYSENSOR_H
#define QUALITYSENSOR_H

#include <Arduino.h>

class QualitySensor
{ 
    public:
        QualitySensor(const uint8_t pin);
        void begin();
        void loop();
        uint8_t getQuality();
        bool targetQualityReached(const uint8_t minTarget);
        void calibrateCleanWater();
        bool calibrationReady();
    private:
        uint8_t _cleanWaterQuality;
        
        const uint8_t _pin;
        bool _calibrating = false;
        uint8_t _calibrationCount = 0;
        uint32_t _calibrationSum = 0;
        unsigned long _lastCalibrationRead = 0;
        void calibrateLoop();
        uint16_t readRawValue();
};

#endif