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
_waterQualitySensor(QUALITY_SENSOR_PIN)
{

}

void HardwareController::begin()
{

}

void HardwareController::loop()
{

}