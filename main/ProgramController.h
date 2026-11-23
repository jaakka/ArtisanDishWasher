#ifndef PROGRAMCONTROLLER_H
#define PROGRAMCONTROLLER_H

#include "HardwareController.h"

class ProgramController
{ 
    public:
        ProgramController(HardwareController& hardwareController);
        void begin();
        void loop();
    private:
        HardwareController& _hardwareController;
};

#endif