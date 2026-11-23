#include "QualitySensor.h"

QualitySensor::QualitySensor(const uint8_t pin)
{

}

void QualitySensor::begin()
{

}

void QualitySensor::loop()
{
  calibrateLoop();
}

uint8_t QualitySensor::getQuality()
{

}

bool QualitySensor::targetQualityReached(const uint8_t minTarget)
{

}

void QualitySensor::calibrateCleanWater()
{
  _calibrationSum = 0;
  _calibrationCount = 0;
  _lastCalibrationRead = millis();
  _calibrating = true;
}

void QualitySensor::calibrateLoop()
{
  if(_calibrating)
  {
    if((millis() - _lastCalibrationRead) >= 1000)
    {
      _lastCalibrationRead = millis();
    }
  }
}