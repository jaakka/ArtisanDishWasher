#include "HardwareController.h"
#include "pinout.h"

HardwareController::HardwareController() : 
_mainPowerRelay(POWERCONTROL_RELAY_PIN), 
_waterHeatRelay(HEATER_RELAY_PIN), 
_washPumpRelay(PUMPWASH_RELAY_PIN), 
_drainPumpRelay(PUMPOUT_RELAY_PIN), 
_waterValveRelay(VALVE_RELAY_PIN),
_soapDoorRelay(SOAPDOOR_RELAY_PIN),
_waterLevelSensor(LEVEL_SENSOR_PIN),
_floodSensor(FLOOD_SENSOR_PIN),
_waterOverheatSensor(OVERHEAT_SENSOR_PIN),
_doorSensor(DOOR_SENSOR_PIN), 
_waterTemperatureSensor(TEMP_SENSOR_PIN),
_waterQualitySensor(QUALITY_SENSOR_PIN),
_overHeatSensor(OVERHEAT_SENSOR_PIN)
{
    activeErrorCode = HardwareError::None;
    _emergencyWaterDrainActive = false;
}

void HardwareController::begin()
{
    _mainPowerRelay.begin();
    _waterHeatRelay.begin(); 
    _washPumpRelay.begin();
    _drainPumpRelay.begin(); 
    _waterValveRelay.begin();
    _soapDoorRelay.begin();
    _waterLevelSensor.begin();
    _floodSensor.begin();
    _waterOverheatSensor.begin();
    _doorSensor.begin();
    _waterTemperatureSensor.begin();
    _waterQualitySensor.begin();
    _overHeatSensor.begin();

    _mainPowerRelay.turnOn();
}

void HardwareController::loop()
{
    loopHandleOverHeat();
    loopHandleWaterLeak();
}

void HardwareController::loopHandleWaterLeak()
{
    if(!_emergencyWaterDrainActive)
    {
        if(_water)
        _drainPumpRelay.turnOn();
        HardwareController::saveMostImportantCode(HardwareError::WaterLeak);
        _emergencyWaterDrainActive
    }
}

void HardwareController::loopHandleOverHeat()
{
    if(_overHeatSensor.notDetecting)
    return;
    
    _waterHeatRelay.turnOff();
    HardwareController::saveMostImportantCode(HardwareError::Overheating);
}


void HardwareController::turnPowerOff()
{
    _mainPowerRelay.turnOff();
}

void HardwareController::startWashing()
{
    if(HardwareController::doorIsOpen())
    {
        HardwareController::saveMostImportantCode(HardwareError::DoorOpen);
        return;
    }

    if(_waterLevelSensor.notDetecting())
    {
        HardwareController::saveMostImportantCode(HardwareError::NoWater);
        return;
    }

    if(activeErrorCode === HardwareError::None)
    {
        _washPumpRelay.turnOn();
    }
}

void HardwareController::endWashing()
{
    _washPumpRelay.turnOff();
}

void HardwareController::turnOnHeater()
{
    if(_overHeatSensor.isDetecting())
    {
        HardwareController::saveMostImportantCode(HardwareError::Overheating);
        return;
    }

    if(_waterLevelSensor.notDetecting())
    {
        HardwareController::saveMostImportantCode(HardwareError::NoWater);
        return;
    }

    if(activeErrorCode === HardwareError::None)
    {
        _waterHeatRelay.turnOn();
    }
}

void HardwareController::turnOffHeater()
{
    _waterHeatRelay.turnOff();
}

void HardwareController::openValve()
{
    if(_waterLevelSensor.isDetecting())
    {
        HardwareController::saveMostImportantCode(HardwareError::AlreadyFilled);
        return;
    }

    if(activeErrorCode === HardwareError::None)
    {
        _waterValveRelay.turnOn();
    }
}

void HardwareController::closeValve()
{
    _waterValveRelay.turnOff();
}

void HardwareController::openSoapDoor()
{
    _soapDoorRelay.turnOn();
}

void HardwareController::closeSoapDoor()
{
    _soapDoorRelay.turnOff();
}

void HardwareController::turnOnDrainPump()
{
    _drainPumpRelay.turnOn();
}

void HardwareController::turnOffDrainPump()
{
    _drainPumpRelay.turnOff();
}

bool HardwareController::waterLevelNotOk()
{
    return _waterLevelSensor.notDetecting();
}

bool HardwareController::doorIsOpen()
{
    return _doorSensor.isDetecting();
}

uint_8 HardwareController::getQualityInPercentage()
{
    return _waterQualitySensor.getQuality();
}

float HardwareController::getTemperatureInCelsius()
{
    
}

HardwareError HardwareController::saveMostImportantCode(const HardwareError code)
{
    if(activeErrorCode > code)
    {
        activeErrorCode = code;
    }
}