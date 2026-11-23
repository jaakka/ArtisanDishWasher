#include "UserInterface.h"

UserInterface::UserInterface(ProgramController& programController, WlanCommunication& wlanCommunication, HardwareController& hardwareController) :
_programController(programController), 
_wlanCommunication(wlanCommunication),
_hardwareController(hardwareController)
{
}

void UserInterface::begin()
{

}

void UserInterface::loop()
{

}