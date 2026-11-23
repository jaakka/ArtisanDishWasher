#include "Relay.h"

Relay::Relay(const uint8_t pin) : _pin(pin)
{

}

void Relay::begin()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void Relay::turnOn()
{
  digitalWrite(_pin, HIGH);
}

void Relay::turnOff()
{
  digitalWrite(_pin, LOW);
}