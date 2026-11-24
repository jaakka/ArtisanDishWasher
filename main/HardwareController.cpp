#include "HardwareController.h"
#include "Pinout.h"
#include "Configurations.h"

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
_waterTemperatureSensor(TEMP_SENSOR_PIN, 0),
_waterQualitySensor(QUALITY_SENSOR_PIN),
_overHeatSensor(OVERHEAT_SENSOR_PIN),
_userInput(ENCODER_RIGHT_PIN, ENCODER_LEFT_PIN, ENCODER_BUTTON_PIN, ENCODER_DETECT_PULSE_COUNT),
_lcdSerial(LCD_RX, LCD_TX),
_wlanSerial(WLAN_RX, WLAN_TX)
{
    activeErrorCode = HardwareError::None;
    _emergencyWaterDrainStartTime = 0;
    _lastAction = UserEvent::None;
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
    _userInput.begin();

    _mainPowerRelay.turnOn();
    beginSerialCommunications();
}

void HardwareController::beginSerialCommunications()
{
    _lcdSerial.begin(9600);
    // HardwareController::sendLcdCommand("baud=115200");
    // _lcdSerial.begin(115200);
    HardwareController::sendLcdCommand("t1.txt=\"TOIMII\"");

    _wlanSerial.begin(19200);
    
}

void HardwareController::sendLcdCommand(const char* cmd)
{
  _lcdSerial.print(cmd);
  _lcdSerial.write(0xFF);
  _lcdSerial.write(0xFF);
  _lcdSerial.write(0xFF);
}

void HardwareController::loop()
{ 
    _userInput.loop();
    _waterQualitySensor.loop();
    _waterTemperatureSensor.loop();

    HardwareController::loopHandleOverHeat();
    HardwareController::loopHandleWaterLeak();
    HardwareController::loopHandleEmergencyPowerOff();
    HardwareController::loopHandleUserActions();
}

void HardwareController::loopHandleEmergencyPowerOff()
{
    if(_userInput.userVeryLongButton())
    {
        _mainPowerRelay.turnOff();
    }
}

void HardwareController::loopHandleWaterLeak()
{
    if(_emergencyWaterDrainStartTime == 0 && _floodSensor.isDetecting())
    {
        _drainPumpRelay.turnOn();
        HardwareController::saveMostImportantCode(HardwareError::WaterLeak);
        _emergencyWaterDrainStartTime = millis();
        return;
    }

    if(_emergencyWaterDrainStartTime != 0 && millis() - _emergencyWaterDrainStartTime >= (static_cast<unsigned long>(DRAIN_PUMP_DELAY_IN_S) * 1000))
    {
        _drainPumpRelay.turnOff();
    }
}

void HardwareController::loopHandleOverHeat()
{
    if(_overHeatSensor.isDetecting() || (_waterTemperatureSensor.getTemperature() >= TEMPERATURE_LIMIT || !_waterTemperatureSensor.SensorOk()))
    {
        _waterHeatRelay.turnOff();

        if(_waterTemperatureSensor.SensorOk())
        {
            HardwareController::saveMostImportantCode(HardwareError::Overheating);
            return;
        }
        HardwareController::saveMostImportantCode(HardwareError::TempSensorError);
    }
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

    if(activeErrorCode == HardwareError::None)
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
    if(!_waterTemperatureSensor.SensorOk())
    {
        HardwareController::saveMostImportantCode(HardwareError::TempSensorError);
        return;
    }

    if(_overHeatSensor.isDetecting() || _waterTemperatureSensor.getTemperature() > TEMPERATURE_LIMIT)
    {
        HardwareController::saveMostImportantCode(HardwareError::Overheating);
        return;
    }

    if(_waterLevelSensor.notDetecting())
    {
        HardwareController::saveMostImportantCode(HardwareError::NoWater);
        return;
    }

    if(activeErrorCode == HardwareError::None)
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

    if(activeErrorCode == HardwareError::None)
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

bool HardwareController::targetQualityReached(const uint8_t minTarget)
{
    return _waterQualitySensor.targetQualityReached(minTarget);
}

uint8_t HardwareController::getQualityInPercentage()
{
    return _waterQualitySensor.getQuality();
}

float HardwareController::getTemperatureInCelsius()
{
    return _waterTemperatureSensor.getTemperature();
}

bool HardwareController::targetTemperatureReached(const uint8_t minTarget)
{
    return _waterTemperatureSensor.targetTemperatureReached(minTarget);
}

void HardwareController::saveMostImportantCode(const HardwareError code)
{
    if(activeErrorCode < code)
    {
        activeErrorCode = code;
    }
}

void HardwareController::calibrateQualitySensorForCleanWater()
{
    _waterQualitySensor.calibrateCleanWater();
}

bool HardwareController::qualitySensorCalibratedOk()
{
    _waterQualitySensor.calibrationReady();
}

UserEvent HardwareController::getUserLastAction()
{
    UserEvent currentAction = _lastAction;
    _lastAction = UserEvent::None;
    return currentAction;
}

void HardwareController::loopHandleUserActions()
{
    if(_userInput.userScrollLeft())
    {
        _lastAction = UserEvent::UserScrollLeft;
    }
    if(_userInput.userScrollRight())
    {
        _lastAction = UserEvent::UserScrollRight;
    }
    if(_userInput.userPressButton())
    {
        _lastAction = UserEvent::UserPressButton;
    }
    if(_userInput.userLongPressButton())
    {
        _lastAction = UserEvent::UserLongPressButton;
    }

    // Door overide
    if(_doorSensor.changeDetected())
    {
        if(_doorSensor.isDetecting())
        {
            _lastAction = UserEvent::UserOpenDoor;
        }
        if(_doorSensor.notDetecting())
        {
            _lastAction = UserEvent::UserCloseDoor;
        }
    }
}