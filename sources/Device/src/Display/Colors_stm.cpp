#include "defines.h"
#include "Display/Colors.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetCurrent(Color color)
{
    currentColor = color;
    if (!WriteFlashColor())
    {
        WriteToDisplay(currentColor);
    }
}
