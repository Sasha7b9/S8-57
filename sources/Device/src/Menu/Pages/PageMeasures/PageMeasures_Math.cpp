#include "defines.h"
#include "Display/Primitives.h"
#include "FPGA/FPGA.h"
#include "FPGA/MathFPGA.h"
#include "Hardware/Beeper.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"


static void OnPress_Screen()
{
    if (set.fft.enabled)
    {
        Display::ShowWarning("��������� ���������� ���");
    }
    else
    {
        Math::CircleIncrease<int8>(reinterpret_cast<int8 *>(&set.math.modeDraw), 0, 2);
    }
}

static void Draw_Screen_Disable(int x, int y)
{
    String("��x").Draw(x + 2, y + 5);
}

static void Draw_Screen_Separate(int x, int y)
{
    Rectangle(13, 9).Draw(x + 3, y + 5);
    HLine line(13);
    line.Draw(x + 3, y + 9);
    line.Draw(x + 3, y + 10);
}

static void Draw_Screen_Together(int x, int y)
{
    Rectangle(13, 9).Draw(x + 3, y + 5);
}

static void Draw_Screen(int x, int y)
{
    typedef void (*pFuncDraw)(int, int);

    const pFuncDraw funcs[3] =
    {
        Draw_Screen_Disable,
        Draw_Screen_Separate,
        Draw_Screen_Together
    };
    funcs[set.math.modeDraw](x, y);
}

DEF_GRAPH_BUTTON_HINTS_3( bScreen,                                                                                                                         //--- ������ - ������� - ����� ---
    "�����",
    "�������� ����� ����������� ��������������� �������",
    &PageMath::self, Item::Active, OnPress_Screen, Draw_Screen,
    Draw_Screen_Disable, "����� �������������� ������� ��������",
    Draw_Screen_Separate, "������� � �������������� ������� ��������� � ������ �����",
    Draw_Screen_Together, "������� � �������������� ������� ��������� � ����� ����"
)


static void OnPress_Type()
{
    Math::CircleIncrease<int8>(reinterpret_cast<int8 *>(&set.math.function), 0, 1);
}

static void Draw_Type_Sum(int x, int y)
{
    HLine(10).Draw(x + 4, y + 9);
    VLine(10).Draw(x + 9, y + 4);
}

static void Draw_Type_Mul(int x, int y)
{
    Char(SymbolUGO2::MATH_FUNC_MUL).Draw4SymbolsInRect(x + 4, y + 3);
}

static void Draw_Type(int x, int y)
{
    typedef void (*pFuncDraw)(int, int);

    const pFuncDraw funcs[2] = { Draw_Type_Sum, Draw_Type_Mul };
    funcs[set.math.function](x, y);
}

static bool IsActive_Type()
{
    return (set.math.modeDraw != FuncModeDraw::Disable);
}

DEF_GRAPH_BUTTON_HINTS_2( bType,                                                                                                                             //--- ������ - ������� - ��� ---
    "���",
    "����� �������������� �������",
    &PageMath::self, IsActive_Type, OnPress_Type, Draw_Type,
    Draw_Type_Sum, "��������",
    Draw_Type_Mul, "���������"
)


static void OnPress_ModeArrows()
{
    Math::CircleIncrease<int8>(reinterpret_cast<int8*>(&set.math.modeRegSet), 0, 1);
}

static void Draw_ModeArrows_Range(int x, int y)
{
    Char('M').Draw(x + 7, y + 5);
}

static void Draw_ModeArrows_RShift(int x, int y)
{
    String("��").Draw(x + 5, y + 5);
}

static void Draw_ModeArrows(int x, int y)
{
    typedef void (*pFuncDraw)(int, int);

    static const pFuncDraw funcs[2] = { Draw_ModeArrows_Range, Draw_ModeArrows_RShift };
    funcs[set.math.modeRegSet](x, y);
}

static bool IsActive_ModeArrows()
{
    return (set.math.modeDraw != FuncModeDraw::Disable);
}

DEF_GRAPH_BUTTON_HINTS_2( bModeArrows,                                                                                                     //--- ������ - ������� - ����� ����� ��������� ---
    "����� ����� ���������",
    "����� ������ ����� ��������� - ���������� ��������� ��� ���������",
    &PageMath::self, IsActive_ModeArrows, OnPress_ModeArrows, Draw_ModeArrows,
    Draw_ModeArrows_Range, "���������� ���������",
    Draw_ModeArrows_RShift, "���������� ���������"
)


static void OnPress_RangeA()
{
    set.math.range = set.ch[Chan::A].range;
    set.math.divider = static_cast<int8>(set.ch[Chan::A].divider);
}

static void Draw_RangeA(int x, int y)
{
    Char('1').Draw(x + 8, y + 5);
}

static bool IsActive_RangeA()
{
    return (set.math.modeDraw != FuncModeDraw::Disable);
}

DEF_GRAPH_BUTTON( bRangeA,                                                                                                                   //--- ������ - ������� - ������� 1-�� ������ ---
    "������� 1-�� ������",
    "���������� ������� ������� ������ ��� ����������� ����������",
    &PageMath::self, IsActive_RangeA, OnPress_RangeA, Draw_RangeA
)


static void OnPress_RangeB()
{
    set.math.range = set.ch[Chan::B].range;
    set.math.divider = static_cast<int8>(set.ch[Chan::B].divider);
}

static void Draw_RangeB(int x, int y)
{
    Char('2').Draw(x + 8, y + 5);
}

static bool IsActive_RangeB()
{
    return (set.math.modeDraw != FuncModeDraw::Disable);
}

DEF_GRAPH_BUTTON( bRangeB,                                                                                                                   //--- ������ - ������� - ������� 2-�� ������ ---
    "������� 2-�� ������",
    "���������� ������� ������� ������ ��� ����������� ����������",
    &PageMath::self, IsActive_RangeB, OnPress_RangeB, Draw_RangeB
)


static bool IsActive_Math()
{
    return !set.fft.enabled;
}

static void OnOpenClose_Math(bool)
{
    if (set.fft.enabled)
    {
        Display::ShowWarning("��������� ���������� ���");
    }
}

static bool HandlerKey_Function(const KeyEvent &event) // -V2506
{
    if (set.math.modeDraw == FuncModeDraw::Disable)
    {
        return false;
    }

    Key::E key = event.key;

    int delta = (key == Key::Up || key == Key::Right) ? 1 : -1;

    if (set.math.modeRegSet == ModeRegSet::RShift)
    {
        int16 prevRShift = set.math.rShift;
        int16 rShift = prevRShift;
        if (delta > 0)
        {
            if (rShift < RShift::MAX)
            {
                rShift += 4 * RShift::STEP;  // -V112
                LIMIT_ABOVE(rShift, RShift::MAX);
                if (prevRShift < 0 && rShift > 0)
                {
                    rShift = 0;
                }
                Beeper::RegulatorShiftRotate();
                set.math.rShift = rShift;
            }
        }
        else
        {
            if (rShift > RShift::MIN)
            {
                rShift -= 4 * RShift::STEP; // -V112
                LIMIT_BELOW(rShift, RShift::MIN);
                if (prevRShift > 0 && rShift < 0)
                {
                    rShift = 0;
                }
                Beeper::RegulatorShiftRotate();
                set.math.rShift = rShift;
            }
        }
    }
    if (set.math.modeRegSet == ModeRegSet::Range)
    {
        static int sum = 0;
        sum -= delta;

        float rShiftAbs = RShift::ToAbs(set.math.rShift, set.math.range);

        if (sum > 2)
        {
            if (set.math.range < Range::Count - 1)
            {
                set.math.range = static_cast<Range::E>(static_cast<uint8>(set.math.range + 1));  // SET_RANGE_MATH++;
                set.math.rShift = MathFPGA::RShift2Rel(rShiftAbs, set.math.range);
                Beeper::RegulatorSwitchRotate();
            }
            sum = 0;
        }
        else if (sum < -2)
        {
            if (set.math.range > 0)
            {
                set.math.range = static_cast<Range::E>(static_cast<uint8>(set.math.range - 1));  // SET_RANGE_MATH--;
                set.math.rShift = MathFPGA::RShift2Rel(rShiftAbs, set.math.range);
                Beeper::RegulatorSwitchRotate();
            }
            sum = 0;
        }
        else
        {
            // ������ ������ �� �����
        }
    }

    return true;
}

DEF_PAGE_5( pMath,                                                                                                                                         //--- ������ - ������� ---
    "����������",
    "��������� � ����� �������������� ������� - �������� ��� ���������",
    &bScreen,
    &bType,
    &bModeArrows,
    &bRangeA,
    &bRangeB,
    PageName::Math, &PageMeasures::self, IsActive_Math, Page::NormalTitle, OnOpenClose_Math, Page::BeforeDraw, HandlerKey_Function
)

const Page * const PageMath::self = static_cast<const Page *>(&pMath);
