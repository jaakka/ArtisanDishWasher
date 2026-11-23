#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "Relay.h"
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "QualitySensor.h"

class HardwareController
{ 
    public:
        HardwareController();
        void begin();
        void loop();
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
        TemperatureSensor _waterTemperatureSensor;
        QualitySensor _waterQualitySensor;
};

#endif