#include "SensorWithState.h"

void SensorWithState::begin()
{
    Sensor::begin();
    _wasDetecting = isDetecting();
}

bool SensorWithState::changeDetected()
{
    const bool detecting = isDetecting();
    const bool changed = detecting != _wasDetecting;

    _wasDetecting = detecting;
    return changed;
}