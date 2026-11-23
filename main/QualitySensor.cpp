#include "QualitySensor.h"
#include "Configurations.h"

QualitySensor::QualitySensor(const uint8_t pin) : _pin(pin)
{

}

void QualitySensor::begin()
{
  pinMode(_pin, INPUT);
  _cleanWaterQuality = 0;
  _calibrating = false;
  _calibrationCount = 0;
  _calibrationSum = 0;
  _lastCalibrationRead = 0;
}

void QualitySensor::loop()
{
  calibrateLoop();
}

uint8_t QualitySensor::getQuality()
{
    if(!calibrationReady() || _cleanWaterQuality == 0)
    return 0;

    uint16_t raw = readRawValue();

    if(raw >= _cleanWaterQuality)
    return 0;

    return static_cast<uint8_t>((static_cast<uint32_t>(_cleanWaterQuality - raw) * 100) / _cleanWaterQuality);
}

bool QualitySensor::targetQualityReached(const uint8_t minTarget)
{
  return calibrationReady() && QualitySensor::getQuality() <= minTarget;
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
    if((millis() - _lastCalibrationRead) >= WATER_QUALITY_CALIB_DELAY_BETWEEN_SAMPLES_MS)
    {
      _lastCalibrationRead = millis();
      _calibrationCount++;
      _calibrationSum+=QualitySensor::readRawValue();

      if(_calibrationCount >= WATER_QUALITY_CALIB_SAMPLE_COUNT)
      {
        _cleanWaterQuality = (_calibrationSum / WATER_QUALITY_CALIB_SAMPLE_COUNT);
        _calibrating = false;
      }
    }
  }
}

bool QualitySensor::calibrationReady()
{
  return !_calibrating && _calibrationCount >= WATER_QUALITY_CALIB_SAMPLE_COUNT;
}

uint16_t QualitySensor::readRawValue()
{
  return analogRead(_pin);
}