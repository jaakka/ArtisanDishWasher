#include "TemperatureSensor.h"
#include "Configurations.h"

TemperatureSensor::TemperatureSensor(const uint8_t pin) : 
_oneWire(pin),
_dallasTemperature(&_oneWire) 
{

}

void TemperatureSensor::begin()
{
  _dallasTemperature.begin();
  _dallasTemperature.setResolution(10); // 0.25 & 187.5ms
  _dallasTemperature.setWaitForConversion(false);
}

void TemperatureSensor::loop()
{
  if (!_measuring && millis() - _requestTime >= TEMPERATURE_MEASURE_LOOP_DELAY)
  {
    _dallasTemperature.requestTemperatures();
    _requestTime = millis();
    _measuring = true;
  }

  if (_measuring && millis() - _requestTime >= TEMPERATURE_MEASURE_TIME)
  {
    _temperature = _dallasTemperature.getTempCByIndex(0);
    _measuring = false;
  }
}

float TemperatureSensor::getTemperature()
{
  return _temperature;
}

bool TemperatureSensor::targetTemperatureReached(const uint8_t minTarget)
{
  return _temperature >= minTarget;
}

bool TemperatureSensor::SensorOk()
{
  return _temperature > MIN_VALUE_TEMP_SENSOR_ERROR && _temperature < MAX_VALUE_TEMP_SENSOR_ERROR;
}