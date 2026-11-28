#include "Graphics.h"

Graphics::Graphics(HardwareController& hardwareController) :
_hardwareController(hardwareController)
{
    
}

void Graphics::begin()
{

    Graphics::updateActionInfo(LargeIcon::HOME, "Tervetuloa!");
}

void Graphics::loop()
{
    
}

void Graphics::drawText(const char* text, TextPosition line)
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


void Graphics::drawImage(uint8_t elementId, uint8_t imageId)
{
    char cmd[15];
    uint8_t position = 0;

    cmd[position++] = 'p';

    if (elementId >= 100)
    {
        cmd[position++] = '0' + elementId / 100;
    }

    if (elementId >= 10)
    {
        cmd[position++] = '0' + (elementId / 10) % 10;
    }

    cmd[position++] = '0' + elementId % 10;

    cmd[position++] = '.';
    cmd[position++] = 'p';
    cmd[position++] = 'i';
    cmd[position++] = 'c';
    cmd[position++] = '=';

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


void Graphics::drawBackground(BgImageRightTop rightTopBg, BgImageRightBottom rightBottomBg, BgImageLeftBottom leftBottomBg, BgImageLeftTop leftTopBg)
{
    Graphics::drawImage(static_cast<uint8_t>(BgImagePosition::RIGHT_TOP), static_cast<uint8_t>(rightTopBg));
    Graphics::drawImage(static_cast<uint8_t>(BgImagePosition::RIGHT_BOTTOM), static_cast<uint8_t>(rightBottomBg));
    Graphics::drawImage(static_cast<uint8_t>(BgImagePosition::LEFT_BOTTOM), static_cast<uint8_t>(leftBottomBg));
    Graphics::drawImage(static_cast<uint8_t>(BgImagePosition::LEFT_TOP), static_cast<uint8_t>(leftTopBg));
}

void Graphics::updateActionInfo(LargeIcon icon, const char* info)
{
    Graphics::drawBackground(BgImageRightTop::EMPTY, BgImageRightBottom::EMPTY, BgImageLeftBottom::EMPTY, BgImageLeftTop::EMPTY);
    Graphics::drawImage(static_cast<uint8_t>(LargeIconPosition::CENTER),static_cast<uint8_t>(icon));
    Graphics::drawText(info, TextPosition::CENTER_TOP);
}