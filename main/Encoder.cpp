#include "Encoder.h"

Encoder::Encoder(const uint8_t rightPin, const uint8_t leftPin, const uint8_t pressPin, const uint8_t detectStepCount) :
_rightPin(rightPin),
_leftPin(leftPin),
_pressPin(pressPin),
_detectStepCount(detectStepCount)
{

}

void Encoder::begin()
{
    pinMode(_pressPin, INPUT);
    pinMode(_rightPin, INPUT_PULLUP); 
    pinMode(_leftPin, INPUT_PULLUP);
}

void Encoder::loop()
{

}

bool Encoder::userScrollLeft()
{

}

bool Encoder::userScrollRight()
{

}

bool Encoder::userPressButton()
{

}

bool Encoder::userLongPressButton()
{

}