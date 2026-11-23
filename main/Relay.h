#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

class Relay
{ 
    public:
        Relay(const uint8_t pin);
        void begin();
        void turnOn();
        void turnOff();
    private:
        const uint8_t _pin;
};

#endif