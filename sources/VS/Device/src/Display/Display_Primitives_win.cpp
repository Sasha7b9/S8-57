#include "defines.h"
#include "Display/Display_Primitives.h"
#include "Display/Painter.h"
#include <SDL.h>
#include <cstring>


extern SDL_Renderer *renderer;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int DrawChar(int x, int y, char symbol);

static bool ByteFontNotEmpty(uint eChar, int byte);

static bool BitInFontIsExist(int eChar, int numByte, int bit);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Display::Primitives::Region::Fill(int x, int y, Color color)
{
    Color::SetCurrent(color);
    SDL_Rect rect = { x, y, width + 1, height + 1 };
    SDL_RenderFillRect(renderer, &rect);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Primitives::Rectangle::Draw(int x, int y, Color color)
{
    Color::SetCurrent(color);
    SDL_Rect rect = { x, y, width + 1, height + 1 };
    SDL_RenderDrawRect(renderer, &rect);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Primitives::HLine::Draw(int x, int y, Color color)
{
    Color::SetCurrent(color);
    SDL_Rect rect = {x, y, width, 1};
    SDL_RenderFillRect(renderer, &rect);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Primitives::VLine::Draw(int x, int y, Color color)
{
    Color::SetCurrent(color);
    SDL_Rect rect = {x, y, 1, height};
    SDL_RenderFillRect(renderer, &rect);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Primitives::Point::Draw(int x, int y, Color color)
{
    Color::SetCurrent(color);
    SDL_RenderDrawPoint(renderer, x, y);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Primitives::Line::Draw(Color color)
{
    Color::SetCurrent(color);
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Display::Primitives::Text::DrawSmall(int x, int y, Color color)
{
    Color::SetCurrent(color);

    uint numSymbols = std::strlen(text);

    for (uint i = 0; i < numSymbols; i++)
    {
        x = DrawChar(x, y, text[i]);
        ++x;
    }

    return x;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static int DrawChar(int eX, int eY, char _symbol)
{
    uint8 symbol = (uint8)_symbol;

    int8 width = (int8)font->symbol[(uint8)symbol].width;
    int8 height = (int8)font->height;

    int size = 1;

    for (int b = 0; b < height; b++)
    {
        if (ByteFontNotEmpty((uint)symbol, b))
        {
            int x = eX;
            int y = eY + b * size + 9 - height;
            int endBit = 8 - width;
            for (int bit = 7; bit >= endBit; bit--)
            {
                if (BitInFontIsExist(symbol, b, bit))
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            SDL_RenderDrawPoint(renderer, x + i, y + j);
                        }
                    }
                }
                x += size;
            }
        }
    }

    return eX + width * size;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool ByteFontNotEmpty(uint eChar, int byte)
{
    static const uint8 *bytes = 0;
    static uint prevChar = (uint)-1;
    if (eChar != prevChar)
    {
        prevChar = eChar;
        bytes = font->symbol[prevChar].bytes;
    }
    return bytes[byte];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool BitInFontIsExist(int eChar, int numByte, int bit)
{
    static uint8 prevByte = 0;      /// \todo ����� ����� ������� �����?
    static int prevChar = -1;
    static int prevNumByte = -1;
    if (prevNumByte != numByte || prevChar != eChar)
    {
        prevByte = font->symbol[eChar].bytes[numByte];
        prevChar = eChar;
        prevNumByte = numByte;
    }
    return prevByte & (1 << bit);
}
