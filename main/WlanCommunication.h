#ifndef WLANCOMMUNICATION_H
#define WLANCOMMUNICATION_H

#include "ProgramController.h"
#include "WlanCommunication.h"

class WlanCommunication
{ 
    public:
        WlanCommunication(ProgramController& programController);
        void begin();
        void loop();
    private:
        ProgramController& _programController;
};

#endif