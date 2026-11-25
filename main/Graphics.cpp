#include "Graphics.h"

Graphics::Graphics(HardwareController& hardwareController) :
_hardwareController(hardwareController)
{
    
}

void Graphics::begin()
{
    Graphics::drawText("TalvLabs", TextLine::TopText);
    Graphics::drawText("", TextLine::BottomText);
}

void Graphics::loop()
{
    
}

void Graphics::drawText(const char* text, TextLine line)
{
    char cmd[30] = "t0.txt=\""; 
    cmd[1] = '0' + static_cast<uint8_t>(line); // Change line id

    uint8_t position = 8; // Custom data start pos

    for (uint8_t i = 0; i < 9; i++)
    {
        if (text[i] == '\0') // Detect custom data end
        {
            break;
        }

        cmd[position] = text[i]; // add letter by letter
        position++;
    }

    // Command end 
    cmd[position] = '"';
    cmd[position + 1] = '\0';

    _hardwareController.sendLcdCommand(cmd);

    // Working example cmd "t0.txt=\"123456789\""
}

// Pitää tehdä tuki monille kuville
void Graphics::drawImage(uint8_t elementId, uint8_t imageId)
{
    char cmd[15] = "p0.pic=";

    cmd[1] = '0' + elementId;

    uint8_t position = 7;

    if (imageId >= 100)
    {
        cmd[position++] = '0' + imageId / 100;
    }

    if (imageId >= 10)
    {
        cmd[position++] = '0' + (imageId / 10) % 10;
    }

    cmd[position++] = '0' + imageId % 10;
    cmd[position] = '\0';

    _hardwareController.sendLcdCommand(cmd);
}