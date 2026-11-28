#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "HardwareController.h"

enum class TextPosition {
    CENTER_TOP = 0,
    CENTER_BOTTOM = 1
};

enum class LargeIconPosition : uint8_t{
    CENTER = 1
};

enum class SmallIconPositionRightTop : uint8_t{
    // Right top circle icons
    ONE = 14,
    TWO_1 = 15,
    TWO_2 = 16,
    TREE_1 = 15,
    TREE_2 = 14,
    TREE_3 = 16,
    FOUR_1 = 19,
    FOUR_2 = 20,
    FOUR_3 = 21,
    FOUR_4 = 22
};

enum class SmallIconPositionRightBottom : uint8_t{
    // Right bottom circle icons
    ONE = 23,
    TWO_1 = 25,
    TWO_2 = 24,
    TREE_1 = 27,
    TREE_2 = 23,
    TREE_3 = 26,
    FOUR_1 = 28,
    FOUR_2 = 29,
    FOUR_3 = 30,
    FOUR_4 = 31
};

enum class SmallIconPositionLeftBottom : uint8_t{
    // Left bottom circle icons
    ONE = 32,
    TWO_1 = 33,
    TWO_2 = 34,
    TREE_1 = 36,
    TREE_2 = 32,
    TREE_3 = 35,
    FOUR_1 = 37,
    FOUR_2 = 38,
    FOUR_3 = 39,
    FOUR_4 = 40
};

enum class SmallIconPositionLeftTop : uint8_t{
    // Left top circle icons
    ONE = 0,
    TWO_1 = 7,
    TWO_2 = 6,
    TREE_1 = 8,
    TREE_2 = 0,
    TREE_3 = 9,
    FOUR_1 = 10,
    FOUR_2 = 11,
    FOUR_3 = 12,
    FOUR_4 = 13
};

// Background image positions
enum class BgImagePosition : uint8_t{
    RIGHT_TOP = 5,
    RIGHT_BOTTOM = 4,
    LEFT_BOTTOM = 3,
    LEFT_TOP = 2
};

// Background images
enum class BgImageRightTop : uint8_t{
    // Circle right top
    EMPTY = 62,
    ONE = 60,
    ONE_SELECTED = 61,
    TWO = 48,
    TWO_1_SELECTED = 49,
    TWO_2_SELECTED = 50,
    THREE = 51,
    THREE_1_SELECTED = 52,
    THREE_2_SELECTED = 53,
    THREE_3_SELECTED = 54,
    FOUR = 55,
    FOUR_1_SELECTED = 56,
    FOUR_2_SELECTED = 57,
    FOUR_3_SELECTED = 58,
    FOUR_4_SELECTED = 59
};

enum class BgImageRightBottom : uint8_t{
    // Circle right bottom
    EMPTY = 63,
    ONE = 46,
    ONE_SELECTED = 47,
    TWO = 34,
    TWO_1_SELECTED = 35,
    TWO_2_SELECTED = 36,
    THREE = 37,
    THREE_1_SELECTED = 38,
    THREE_2_SELECTED = 39,
    THREE_3_SELECTED = 40,
    FOUR = 41,
    FOUR_1_SELECTED = 42,
    FOUR_2_SELECTED = 43,
    FOUR_3_SELECTED = 44,
    FOUR_4_SELECTED = 45
};

enum class BgImageLeftBottom : uint8_t{
    // Circle left bottom
    EMPTY = 64,
    ONE = 32,
    ONE_SELECTED = 33,
    TWO = 20,
    TWO_1_SELECTED = 21,
    TWO_2_SELECTED = 22,
    THREE = 23,
    THREE_1_SELECTED = 24,
    THREE_2_SELECTED = 25,
    THREE_3_SELECTED = 26,
    FOUR = 27,
    FOUR_1_SELECTED = 28,
    FOUR_2_SELECTED = 29,
    FOUR_3_SELECTED = 30,
    FOUR_4_SELECTED = 31
};

enum class BgImageLeftTop : uint8_t{
    // Circle left top
    EMPTY = 65,
    ONE = 18,
    ONE_SELECTED = 19,
    TWO = 6,
    TWO_1_SELECTED = 7,
    TWO_2_SELECTED = 8,
    THREE = 9,
    THREE_1_SELECTED = 10,
    THREE_2_SELECTED = 11,
    THREE_3_SELECTED = 12,
    FOUR = 13,
    FOUR_1_SELECTED = 14,
    FOUR_2_SELECTED = 15,
    FOUR_3_SELECTED = 16,
    FOUR_4_SELECTED = 17
};

enum class LargeIcon : uint8_t{
    WATER = 0,
    FIRE = 1,
    SOAP = 2,
    STORM = 3,
    RESTART = 4,
    PAUSE = 5,
    HOME = 72,
    CABLE = 75,
    TOOLS = 79,
    SNOWFLAKE = 82,
    TIME = 86,
    CONTROLLER = 93,
    LEAF = 96
};

enum class SmallIcon : uint8_t {
    NONE = 0,
    FIRE = 66,
    PAUSE = 67,
    RESTART = 68,
    SOAP = 69,
    STORM = 70,
    WATER = 71,
    CABLE = 76,
    TOOLS = 80,
    SNOWFLAKE = 83,
    TIME = 87,
    HOME = 89,
    CONTROLLER = 94,
    LEAF = 97
};

enum class SmallIconSelected : uint8_t {
    NONE = 0,
    FIRE = 91,
    PAUSE = 73,
    RESTART = 78,
    SOAP = 85,
    STORM = 92,
    WATER = 74,
    CABLE = 77,
    TOOLS = 81,
    SNOWFLAKE = 84,
    TIME = 88,
    HOME = 90,
    CONTROLLER = 95,
    LEAF = 98
};

class Graphics
{ 
    public:
        Graphics(HardwareController& hardwareController);
        void begin();
        void loop();
        void drawText(const char* text, TextPosition line);
        void drawImage(uint8_t elementId, uint8_t imageId);
        void drawBackground(BgImageRightTop rightTopBg, BgImageRightBottom rightBottomBg, BgImageLeftBottom leftBottomBg, BgImageLeftTop leftTopBg);
        void updateActionInfo(LargeIcon icon, const char* info);

    private:
        HardwareController& _hardwareController;
};

#endif