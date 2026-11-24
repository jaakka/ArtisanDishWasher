#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{ 
    public:
        Encoder(const uint8_t rightPin, const uint8_t leftPin, const uint8_t pressPin, const uint8_t detectStepCount);
        void begin();
        void loop();
        bool userScrollLeft();
        bool userScrollRight();
        bool userPressButton();
        bool userLongPressButton();
        
    private:
        const uint8_t _rightPin;
        const uint8_t _leftPin;
        const uint8_t _pressPin;
        const uint8_t _detectStepCount;
        unsigned long _userPressStartTime;
};

#endif