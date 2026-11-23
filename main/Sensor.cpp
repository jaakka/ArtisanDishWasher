#include "Sensor.h"
#include "Configurations.h"

Sensor::Sensor(const uint8_t pin) : _pin(pin)
{

}

void Sensor::begin()
{
  pinMode(_pin, INPUT);
}

bool Sensor::isDetecting()
{
  return (analogRead(_pin) >= SENSOR_MIN_DETECT_VALUE);
}

bool Sensor::notDetecting()
{
  return !Sensor::isDetecting();
}