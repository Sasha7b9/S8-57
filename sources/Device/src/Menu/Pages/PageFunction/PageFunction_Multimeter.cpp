#include "defines.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Include/Definition.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Device.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageMultimeter;

const PageBase *PageFunction::PageMultimeter::pointer = &pageMultimeter;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FuncActive_RangesVoltageDC()
{
    return MULTI_MEASURE == Multimeter::Measure::VoltageDC;
}

static void OnChange_VoltageDC(bool active)
{
    if(active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_3( cRangesVoltageDC,                                                                                                                                 //--- ���������� - ������ ---
    "������", "Range",
    "�������� ���������", "�easurement range",
    "2 �",   "2 V",
    "20 �",  "20 V",
    "500 �", "500 V",
    MULTI_RANGE_VOLTAGE_DC, pageMultimeter, FuncActive_RangesVoltageDC, OnChange_VoltageDC, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncActive_RnagesVoltageAC()
{
    return MULTI_MEASURE == Multimeter::Measure::VoltageAC;
}

static void OnChange_VoltageAC(bool active)
{
    if(active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_3( cRangesVoltageAC,                                                                                                                                 //--- ���������� - ������ ---
    "������", "Range",
    "�������� ���������", "Measurement range",
    "2 �", "2 V",
    "20 �", "20 V",
    "400 �", "400 V",
    MULTI_RANGE_VOLTAGE_AC, pageMultimeter, FuncActive_RnagesVoltageAC, OnChange_VoltageAC, Choice::EmptyDraw
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_CurrentDC(bool active)
{
    if (active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_2( cRangesCurrentDC,
    "������", "Range",
    "�������� ���������", "Measurement range",
    "20��", "20m�",
    "2�", "2�",
    MULTI_RANGE_CURRENT_DC, pageMultimeter, Choice::EmptyActive, OnChange_CurrentDC, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_CurrentAC(bool active)
{
    if (active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_2( cRangesCurrentAC,
    "������", "Range",
    "�������� ���������", "Measurement range",
    "20��", "20mA",
    "2�", "2A",
    MULTI_RANGE_CURRENT_AC, pageMultimeter, Choice::EmptyActive, OnChange_CurrentAC, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncActive_RangesReistance()
{
    return MULTI_MEASURE == Multimeter::Measure::Resistance;
}

static void OnChange_Resistance(bool active)
{
    if(active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_4(   cRangesResistance,                                                                                                                              //--- ���������� - ������ ---
    "������", "Range",
    "�������� ���������", "Measurement range",
    "2 ���", "2 kOhm",
    "20 ���", "20 kOhm",
    "200 ���", "200 kOhm",
    "10 ���", "10 MOhm",
    MULTI_RANGE_RESISTANCE, pageMultimeter, FuncActive_RangesReistance, OnChange_Resistance, Choice::EmptyDraw
)

DEF_CHOICE_7(   cMode,
    "�����", "Mode"
    ,
    "����� ���� ����������\n"
    "U= - ���������� ����������\n"
    "U~ - ���������� ����������\n"
    "I= - ���������� ���\n"
    "I~ - ���������� ���\n"
    "R - ������������� ����������� ����\n"
    "VD - ���� ������\n"
    "BELL - ���������"
    ,
    "Selecting the type of measurement\n"
    "U= - DC voltage\n"
    "U~ - AC voltage\n"
    "I= - DC current\n"
    "I~ - AC current\n"
    "R - DC resistance\n"
    "VD - diodes test\n"
    "BELL - bell"
    ,
    "U=",   "U=",
    "U~",   "U~",
    "I=",   "I=",
    "I~",   "I~",
    "R",    "R",
    "VD",   "VD",
    "���������", "Bell",
    MULTI_MEASURE, pageMultimeter, FuncActive, PageFunction::PageMultimeter::OnChanged_Mode, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_AVP(bool)
{
    Multimeter::ChangeAVP();
}

DEF_CHOICE_2 (cAVP,
    "���", "ASL",
    "��������� �������",
    "Auto-select limit",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    MULTI_AVP, pageMultimeter, FuncActive, OnChanged_AVP, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Zero(bool)
{
    //Multimeter::LoadZero();
}

static int8 zero = 0;

DEF_CHOICE_2(cZero,
    "����", "Zero",
    "",
    "",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    zero, pageMultimeter, FuncActive, OnChanged_Zero, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Calibrate0()
{
    Multimeter::Calibrate(0);
}

DEF_BUTTON( bCalibrate0,
    "������ 0", "Calibrate 0",
    "",
    "",
    pageMultimeter, FuncActive, OnPress_Calibrate0, Button::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Calibrate1()
{
    Multimeter::Calibrate(1);
}

DEF_BUTTON( bCalibrate1,
    "������ 1", "Calibrate 1",
    "",
    "",
    pageMultimeter, FuncActive, OnPress_Calibrate1, Button::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static int8 calibration = 0;

static void OnChanged_Calibration(bool)
{
    PageBase *page = (PageBase *)&pageMultimeter;

    Control **items = (Control **)page->items;

    if (calibration == 0)
    {
        items[2] = (Control *)&cAVP; //-V641
        items[3] = (Control *)&cZero; //-V641
    }
    else
    {
        items[2] = (Control *)&bCalibrate0; //-V641 //-V1027
        items[3] = (Control *)&bCalibrate1; //-V641 //-V1027
    }
}

DEF_CHOICE_2( cCalibration,
    "����������", "Calibration",
    "",
    "",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    calibration, pageMultimeter, FuncActive, OnChanged_Calibration, Choice::EmptyDraw
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PageFunction::PageMultimeter::Init()
{
    OnChanged_Mode(true);
}

static void OnPress_Page(bool enter)
{
    Device::State::SetMode(enter ? Device::Mode::Multimeter : Device::Mode::Osci);
}

DEF_PAGE_4( pageMultimeter, // -V641
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    &cMode,
    &cRangesVoltageDC,
    &cAVP,
    &cZero,
    //&cCalibration,
    Page::Name::Function_Multimeter, PageFunction::pointer, FuncActive, OnPress_Page, FuncDrawPage, FuncRegSetPage
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageFunction::PageMultimeter::OnChanged_Mode(bool)
{
    PageBase *page = (PageBase *)&pageMultimeter;

    Control **items = (Control **)page->items;

    if (MULTI_MEASURE == Multimeter::Measure::VoltageDC)
    {
        items[1] = (Control *)&cRangesVoltageDC; //-V641
    }
    else if (MULTI_MEASURE == Multimeter::Measure::VoltageAC)
    {
        items[1] = (Control *)&cRangesVoltageAC; //-V641
    }
    else if (MULTI_MEASURE == Multimeter::Measure::CurrentDC)
    {
        items[1] = (Control *)&cRangesCurrentDC;  // -V641
    }
    else if (MULTI_MEASURE == Multimeter::Measure::CurrentAC)
    {
        items[1] = (Control *)&cRangesCurrentAC;    // -V641
    }
    else if (MULTI_MEASURE == Multimeter::Measure::Resistance)
    {
        items[1] = (Control *)&cRangesResistance; //-V641
    }
    else if (MULTI_MEASURE == Multimeter::Measure::TestDiode)
    {
        items[1] = nullptr;
    }
    else
    {
        // ����� ������
    }

    Multimeter::ChangeMode();
}
