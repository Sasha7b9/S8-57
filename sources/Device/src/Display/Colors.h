#pragma once
#include "Settings/SettingsChannel.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Color
{
public:
    static Color BLACK;
    static Color WHITE;
    static Color GRID;
    static Color DATA_A;
    static Color DATA_B;
    static Color MENU_FIELD;
    static Color MENU_TITLE;
    static Color MENU_TITLE_DARK;
    static Color MENU_TITLE_BRIGHT;
    static Color MENU_ITEM;
    static Color MENU_ITEM_DARK;
    static Color MENU_ITEM_BRIGHT;
    static Color DATA_WHITE_ACCUM_A;
    static Color DATA_WHITE_ACCUM_B;
    static Color RED;
    static Color GREEN;
    static Color BLUE;
    static Color BLUE_25;
    static Color BLUE_50;
    static Color GRAY_10;
    static Color GRAY_20;
    static Color BLUE_10;
    static Color GRAY_50;
    static Color GRAY_75;
    static Color DATA_HALF_A;
    static Color DATA_HALF_B;
    static Color SEPARATOR;
    static Color YELLOW;

    static Color NUMBER;

    static Color FILL;
    static Color BACK;
    static Color FLASH_10;
    static Color FLASH_01;

    explicit Color(uint8 val) : value(val) { }
    Color(const Color &color) : value(color.value) { }

    static Color Channel(Chan::E ch);
    static Color Cursors(Chan::E ch);
    static Color Trig();
    static Color ChanAccum(Chan ch);     ///< ���� ������ � ������ ����������
    static Color MenuItem(bool shade);      ///< ���� �������� ����.
    static Color MenuTitle(bool shade);     ///< ���� ��������� ��������. inShade == true, ���� �������� ��������
    static Color BorderMenu(bool shade);    ///< ���� ��������� ����
    static Color LightShadingText();        ///< ������� ���� � ����.
    static Color Contrast(Color color);     ///< ���������� ����, ����������� � color. ����� ���� ����� ��� ������.
    static Color ChanHalf(Chan::E ch);
    /// ������������� ������� ���� ���������
    static void SetCurrent(Color color = Color::NUMBER);
    /// ���������� ������� ���� ���������
    static Color GetCurent();

    static void ResetFlash();
    /// ��� ��������� �������. �������� ������ ������
    static void OnTimerFlashDisplay();

    void SetValue(uint value);
    
    uint8 value;

    static void InitGlobalColors();
    static void Log(Color color);

    Color& operator=(const Color &color);

private:

    static Color CHAN[4];
    
    enum
    {
        COLOR_BLACK = 0,
        COLOR_WHITE = 1,
        COLOR_GRID = 2,
        COLOR_DATA_A = 3,
        COLOR_DATA_B = 4,
        COLOR_MENU_FIELD = 5,
        COLOR_MENU_TITLE = 6,
        COLOR_MENU_TITLE_DARK = 7,
        COLOR_MENU_TITLE_BRIGHT = 8,
        COLOR_MENU_ITEM = 9,
        COLOR_MENU_ITEM_DARK = 10,
        COLOR_MENU_ITEM_BRIGHT = 11,
        COLOR_DATA_WHITE_ACCUM_A = 12,   ///< ������������ ��� ��� ��������� ������ �� ����� ����, ��� � ��� ��������� ����������� ��������
        COLOR_DATA_WHITE_ACCUM_B = 13,
        COLOR_RED = 14,
        COLOR_GREEN = 15,
        COLOR_BLUE = 16,
        COLOR_BLUE_25 = 17,
        COLOR_BLUE_50 = 18,
        COLOR_GRAY_10 = 19,
        COLOR_GRAY_20 = 20,
        COLOR_BLUE_10 = 21,
        COLOR_GRAY_50 = 22,
        COLOR_GRAY_75 = 23,
        COLOR_DATA_HALF_A = 24,
        COLOR_DATA_HALF_B = 25,
        COLOR_SEPARATOR = 26,
        COLOR_YELLOW = 27,

        COLOR_NUMBER = 32,

        COLOR_FLASH_10 = 33,
        COLOR_FLASH_01 = 34,
        COLOR_INVERSE = 35
    };

    /// ���������� ������� ���� � �������. ���������� false, ���� ������� ���� ����������
    static bool WriteFlashColor();
    /// ���������� ���� � �������
    static void WriteToDisplay(Color color);

    static Color currentColor;

public:

    struct Scheme
    {
        enum E
        {
            WhiteLetters,   ///< � ���� ������ ��������� ��������� ���� ������� ����� - �� ����� ������ ����� �����
            BlackLetters    ///< � ���� ������ ��������� ��������� ���� ������� ������ - �� ����� ������� ��������
        } value;
        explicit Scheme(E v) : value(v) {}
    };
};

bool operator!=(const Color &left, const Color &right);
bool operator==(const Color &left, const Color &right);
bool operator>(const Color &left, const Color &right);


/// ��������� ������������ ��� ���������� ��������� �����
class ColorType
{
public:
    /// ������� ������������ ����� [0.0...1.0]
    float   red;
    /// ������ ������������ ����� [0.0...1.0]
    float   green;
    /// ����� ������������ ����� [0.0...1.0]
    float   blue;
    /// ��� ��������� ������� ������������ �����
    float   stepRed;
    /// ��� ��������� ������ ������������ �����
    float   stepGreen;
    /// ��� ��������� ����� ������������ �����
    float   stepBlue;
    /// ������� [0...1]
    float   brightness;
    Color   color;
    int8    currentField;
    /// true, ���� ��������� ��� ����������������
    bool    inititalized;

    /// �������������. ��� ��������� ������ �� ��������. ��� ��������� ������� �������� ReInit()
    void Init();
    void ReInit();
    void SetBrightness(float brightness = -1.0F);
    void BrightnessChange(int delta);
    void ComponentChange(int delta);
private:
    void CalcSteps();
    void SetColor();
};

#define DEF_COLOR_TYPE(name, r, g, b, sR, sG, sB, bright, col) ColorType name = {r, g, b, sR, sG, sB, bright, col, 0, false, false};
#define COLOR_TYPE(r, g, b, sR, sG, sB, bright, col) {r, g, b, sR, sG, sB, bright, col, 0, false};


#define MAKE_COLOR(r, g, b) ((uint)((b) + ((g) << 8) + ((r) << 16)))
#define R_FROM_COLOR(color) (((uint)(color) >> 16) & 0xff)
#define G_FROM_COLOR(color) (((uint)(color) >> 8)  & 0xff)
#define B_FROM_COLOR(color) (((uint)(color))       & 0xff)

#define COLOR(x) GlobalColors[x]

extern uint GlobalColors[256];
