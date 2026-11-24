#include <arduino.h>
#include "UserInterface.h"
#include "ProgramController.h"
#include "WlanCommunication.h"
#include "HardwareController.h"

HardwareController HardwareController;
ProgramController ProgramController(HardwareController);
WlanCommunication WlanCommunication(ProgramController);
UserInterface UserInterface(ProgramController, WlanCommunication, HardwareController);

void setup()
{
    Serial.begin(115200);
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
    testloop();
}

void testloop()
{
    UserEvent event = HardwareController.getUserLastAction();

      switch(event)
    {
        case UserEvent::UserScrollLeft:
            Serial.println("User scroll left encoder.");
        break;

        case UserEvent::UserScrollRight:
            Serial.println("User scroll right encoder.");
        break;

        case UserEvent::UserPressButton:
            Serial.println("User press button (short).");
        break;

        case UserEvent::UserLongPressButton:
            Serial.println("User press button (long).");
        break;
    }
}