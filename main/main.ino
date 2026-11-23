#include <arduino.h>
#include "UserInterface.h"
#include "ProgramController.h"
#include "WlanCommunication.h"

HardwareController HardwareController;
ProgramController ProgramController(HardwareController);
WlanCommunication WlanCommunication(ProgramController);
UserInterface UserInterface(ProgramController, WlanCommunication, HardwareController);

void setup()
{
    HardwareController.begin();
    UserInterface.begin();
    ProgramController.begin();
    WlanCommunication.begin();
}

void loop()
{
    HardwareController.loop();
    UserInterface.loop();
    ProgramController.loop();
    WlanCommunication.loop();
}