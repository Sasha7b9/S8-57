#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Graphics_Recorder.h"
#include "Display/Painter.h"
#include "Menu/Menu.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Recorder::Graphics::Update()
{
    Painter::BeginScene(Color::BLUE_10);

    Menu::Draw();
}
