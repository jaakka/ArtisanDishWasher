#include "Encoder.h"
#include "Configurations.h"

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
    _oldState = readEncoder();
    _rotationCount = 0;
    _userPressStartTime = 0;
    _shortPressWaiting = 0;
    _longPressWaiting = 0;
}

void Encoder::loop()
{
    Encoder::encoderLoop();
    Encoder::buttonLoop();
}

bool Encoder::userScrollLeft()
{
    if(_rotationCount < _detectStepCount)
    {
        return false;
    }

    _rotationCount -= _detectStepCount;
    return true;
}

bool Encoder::userScrollRight()
{
    const int16_t stepCount = _detectStepCount;

    if(_rotationCount > -stepCount)
    {
        return false;
    }

    _rotationCount += stepCount;
    return true;
}

bool Encoder::userPressButton()
{
    if(_shortPressWaiting)
    {
        _shortPressWaiting = false;
        return true;
    }
    return false;
}

bool Encoder::userLongPressButton()
{
    if(_longPressWaiting)
    {
        _longPressWaiting = false;
        return true;
    }
    return false;
}

bool Encoder::userVeryLongButton()
{
    return _userPressStartTime != 0 && ((millis() - _userPressStartTime) >= VERY_LONG_BUTTON_PRESS_TIME_IN_MS);
}

void Encoder::buttonLoop()
{
    if(Encoder::buttonPressed())
    {
        if(_userPressStartTime == 0)
        {   
            // Press start
            _userPressStartTime = millis();
        }
        
    }

    // Button released
    if(!Encoder::buttonPressed() && _userPressStartTime != 0)
    {
        if((millis() - _userPressStartTime) >= SHORT_BUTTON_PRESS_TIME_IN_MS)
        {
            // Button press detected

            if((millis() - _userPressStartTime) >= LONG_BUTTON_PRESS_TIME_IN_MS)
            {
                _longPressWaiting = true;
            }
            else
            {
                _shortPressWaiting = true;
            }
        }

        _userPressStartTime = 0;
    }
}

bool Encoder::buttonPressed()
{
    return analogRead(_pressPin) >= SENSOR_MIN_DETECT_VALUE;
}

uint8_t Encoder::readEncoder()
{
    return (digitalRead(_rightPin) << 1) | digitalRead(_leftPin);

    // Output is RL -> 11 both high, 10 right high, 01 left high..
    // -> 000000XX
}

void Encoder::encoderLoop()
{
    const uint8_t state = readEncoder(); 
    // -> 000000XX

    const uint8_t movedBitsOldState = _oldState << 2; 
    // move state bits to -> 0000XX00

    const uint8_t oldAndNewState = movedBitsOldState | state; 
    // connect new 000000XX and old 0000XX00 = 0000XXYY

    _oldState = state;

    Encoder::handleRotationDirection(oldAndNewState);
}

void Encoder::handleRotationDirection(const uint8_t oldAndNewState)
{
    switch(oldAndNewState)
    {
        // Left 11 > 01 > 00 > 10 > 11
        case 0b00001101: 
            _rotationCount++;
        break;

        case 0b00000100:
            _rotationCount++;
        break;

        case 0b00000010:
            _rotationCount++;
        break;
        
        case 0b00001011:
            _rotationCount++;
        break;

        // Right 11 > 10 > 00 > 01 > 11
        case 0b00001110:
          _rotationCount--;
        break;

        case 0b00001000:
          _rotationCount--;
        break;

        case 0b00000001:
          _rotationCount--;
        break;

        case 0b00000111:
          _rotationCount--;
        break;
    }
}