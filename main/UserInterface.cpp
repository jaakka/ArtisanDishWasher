#include "UserInterface.h"

UserInterface::UserInterface(ProgramController& programController, WlanCommunication& wlanCommunication, HardwareController& hardwareController) :
_programController(programController), 
_wlanCommunication(wlanCommunication),
_hardwareController(hardwareController),
_graphics(hardwareController)
{
}

void UserInterface::begin()
{
    _graphics.begin();
}

void UserInterface::loop()
{
    _graphics.loop();
}