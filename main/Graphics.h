#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "HardwareController.h"

enum class TextLine : uint8_t
{
    TopText,
    BottomText
};

class Graphics
{ 
    public:
        Graphics(HardwareController& hardwareController);
        void begin();
        void loop();
        void drawText(const char* text, TextLine line);
    private:
        HardwareController& _hardwareController;
};

#endif