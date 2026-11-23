#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "Relay.h"
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "QualitySensor.h"

enum class HardwareError : uint8_t
{
    None,
    DoorOpen,
    AlreadyFilled,
    Timeout,
    NoWater,
    Overheating,
    WaterLeak
};

class HardwareController
{ 
    public:
        HardwareController();
        void begin();
        void loop();
        HardwareError activeErrorCode;
        void turnPowerOff();
        void turnOnHeater();
        void turnOffHeater();
        void openValve();
        void closeValve();
        void openSoapDoor();
        void closeSoapDoor();
        void turnOnDrainPump();
        void turnOffDrainPump();
        void startWashing();
        void endWashing();
        bool waterLevelNotOk();
        bool doorIsOpen();
        bool targetQualityReached(const uint8_t minTarget);
        uint8_t getQualityInPercentage();
        float getTemperatureInCelsius();
        bool targetTemperatureReached(const uint8_t minTarget);

    private:
        Relay _mainPowerRelay;
        Relay _waterHeatRelay;
        Relay _washPumpRelay;
        Relay _drainPumpRelay;
        Relay _waterValveRelay;
        Relay _soapDoorRelay;
        Sensor _waterLevelSensor;
        Sensor _floodSensor;
        Sensor _waterOverheatSensor;
        Sensor _doorSensor;
        Sensor _overHeatSensor;
        TemperatureSensor _waterTemperatureSensor;
        QualitySensor _waterQualitySensor;
        void loopHandleOverHeat();
        void loopHandleWaterLeak();
        unsigned long _emergencyWaterDrainStartTime;
        HardwareError saveMostImportantCode(const HardwareError code);
};

#endif