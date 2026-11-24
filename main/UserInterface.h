#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "ProgramController.h"
#include "WlanCommunication.h"
#include "HardwareController.h"

class UserInterface
{ 
    public:
        UserInterface(ProgramController& programController, WlanCommunication& wlanCommunication, HardwareController& hardwareController);
        void begin();
        void loop();
    private:
        ProgramController& _programController;
        WlanCommunication& _wlanCommunication;
        HardwareController& _hardwareController;
        // MainMenu _mainMenu;
        // DebugMenu _debugMenu;

};

#endif