#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Graphics_Recorder.h"
#include "Display/Grid.h"
#include "Display/Painter.h"
#include "Menu/Menu.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Recorder::Graphics::Update()
{
    Painter::BeginScene(Color::BLUE_10);

    Grid::Draw();

    Menu::Draw();
}
