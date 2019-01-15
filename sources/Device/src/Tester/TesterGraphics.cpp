#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Tester.h"
#include "Data/Reader.h"
#include "Display/Display_Primitives.h"
#include "Display/Grid.h"
#include "Display/Painter.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"
#endif


using namespace Display::Primitives;
using namespace Osci::Settings;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef uint8 array[Chan::Number][Tester::NUM_STEPS][TESTER_NUM_POINTS];

static bool ready[Tester::NUM_STEPS] = {false, false, false, false, false};

static array *dat = (array *)OUT_A;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// �������� ������� �����������
static void DrawLegend(int x, int y);
/// ���������� ��������� ������ ������
static void DrawParametersChannel(Chan::E ch, int x, int y);
/// ���������� ����, ������� ����� �������� ��������������� "���������"
static Color ColorForStep(int step);
/// �������� ������ ��������� numStep
static void DrawData(int step, int x0, int y0);
/// ���������� �������� �������� �������� ��������������� "���������"
static String ValueForStep(int step);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tester::Display::Update()
{
    Painter::BeginScene(Color::BACK);

    Grid::Draw();

    for (int i = 0; i < NUM_STEPS; i++)
    {
        DrawData(i, 0, 0);
    }

    DrawLegend(274, 2);

    DrawParametersChannel(Chan::A, 250, 206);
    DrawParametersChannel(Chan::B, 3, 3);
    
    Menu::Draw();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static Color ColorForStep(int _step)
{
    static const Color colors[Tester::NUM_STEPS] = {Color::FILL, Color::GRID, Color::RED, Color::GREEN, Color::BLUE};

    if (_step < Tester::NUM_STEPS)
    {
        return colors[_step];
    }
    else
    {
        LOG_ERROR("������������ ���");
    }

    return Color::FILL;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData(int numStep, int /*x0*/, int /*y0*/)
{
    if(!ready[numStep])
    {
        return;
    }

    uint8 *x = &(*dat)[Chan::A][numStep][0];
    uint8 *y = &(*dat)[Chan::B][numStep][0];
    
    if(TESTER_VIEW_MODE_IS_LINES)
    {
        Painter::DrawTesterData((uint8)TESTER_VIEW_MODE, ColorForStep(numStep), x, y);
    }
    else
    {
        Color::SetCurrent(ColorForStep(numStep));
        for(int i = 1; i < 240; i++)
        {
            //Painter::SetPoint(x[i], y[i]);
            Point().Draw(x[i], y[i]);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Tester::Display::SetPoints(int numStep, const uint8 dx[TESTER_NUM_POINTS], const uint8 dy[TESTER_NUM_POINTS])
{
    ready[numStep] = true;

    uint8 *x = &(*dat)[Chan::A][numStep][0];
    uint8 *y = &(*dat)[Chan::B][numStep][0];

    for(int i = 0; i < TESTER_NUM_POINTS; i++)
    {
        int X = TESTER_NUM_POINTS - (dx[i] - MIN_VALUE);
        int Y = dy[i] - MIN_VALUE;

        LIMITATION(X, 0, TESTER_NUM_POINTS - 1); //-V2516
        LIMITATION(Y, 0, TESTER_NUM_POINTS - 1); //-V2516

        x[i] = (uint8)X;
        y[i] = (uint8)Y;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawLegend(int x, int y)
{
    Region(43, 40).Draw(x, y, Color::BACK);

    HLine line(9);

    for (int i = 0; i < Tester::NUM_STEPS; i++)
    {
        //Painter::DrawHLine(y + 4 + i * 8, x + 1, x + 10, ColorForStep(i));
        line.Draw(x + 1, y + 4 + i * 8, ColorForStep(i));

        ValueForStep(i).Draw(x + 12, y + i * 8);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static String ValueForStep(int step)
{
    static pString valuesU[2][5] =
    {
        {"0��", "100��", "200��", "300��", "400��"},
        {"0��", "500��", "1�",    "1.5�",  "2.0�"}
    };

    if (TESTER_CONTROL_IS_U)
    {
        return String(valuesU[TESTER_STEP_U][step]);
    }

    static pString valuesI[2][5] =
    {
        {"0��", "4��",  "8��",  "12��", "16��"},
        {"0��", "20��", "40��", "60��", "80��"}
    };

    return String(valuesI[TESTER_STEP_I][step]);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawParametersChannel(Chan::E ch, int x, int y)
{
    Range range = Range(SET_RANGE(ch));
    uint16 rShift = SET_RSHIFT(ch);
    Tester::Scale scale(range.value, ch);
    Tester::Shift shift(rShift, ch);

    Color::SetCurrent(Color::FILL);

    //Painter::DrawTextOnBackground(x, y, scale.ToString(), Color::BACK);
    Text(scale.ToString()).DrawOnBackground(x, y, Color::BACK);

    Color::SetCurrent(Color::FILL);

    //Painter::DrawTextOnBackground(x + ((ch == Chan::A) ? 25 : 35), y, shift.ToString(scale.value).CString(), Color::BACK);
    Text(shift.ToString(scale.value).CString()).DrawOnBackground(x + ((ch == Chan::A) ? 25 : 35), y, Color::BACK);
}
