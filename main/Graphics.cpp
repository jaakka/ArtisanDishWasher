#include "Graphics.h"

Graphics::Graphics(HardwareController& hardwareController) :
_hardwareController(hardwareController)
{
    
}

void Graphics::begin()
{
    _hardwareController.sendLcdCommand("t0.txt=\"123456789\"");
}

void Graphics::loop()
{
    
}

void Graphics::drawText(const char* text, TextLine line)
{
    
}