#include "defines.h"
#include "Display/Painter.h"
#include "Menu/Pages/Include/PageDisplay.h"
#include "FPGA/FPGA.h"
#include "Menu/Menu.h"
#include "Utils/CommonFunctions.h"
#include "Settings/Settings.h"

#include "Osci/Osci.h"
#include "Osci/Osci_Averager.h"


using namespace Osci::Settings;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageDisplay;

const PageBase *PageDisplay::pointer = &pageDisplay;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
DEF_CHOICE_2( cThickness,                                                                                                                                         //--- ������� - ������� ---
    "�������", "Thickness",
    "��������� �������� ������� ��������� �� ����� �����������",
    "Allows you to change the thickness of the signals displayed on the screen",
    "x1", "x1",
    "x3", "x3",
    THICKNESS_SIGNAL, pageDisplay, FuncActive, Choice::EmptyChange, Choice::EmptyDraw
)
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageDisplay::Init()
{
    PageSettings::PageColors::Init();   // ������� �������� � ��������� ������
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cViewMode,                                                                                                                                      //--- ������� - ����������� ---
    "�������.",
    "����� ����� ����������� �������.",
    "������",
    "�����",
    MODE_DRAW_SIGNAL, pageDisplay, FuncActive, Choice::EmptyChange, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_MinMax()
{
    return !Osci::InModeRandomizer() && !Osci::InModeP2P();
}

static void OnChanged_MinMax(bool)
{
}

DEF_CHOICE_8( cMinMax,                                                                                                                                           //--- ������� - ��� ���� ---
    "��� ����",
    "����� ���������� ��������� ���������, �� ������� �������� ��������������� �����, ��������� �������� � ��������� ���������.",
    DISABLE_RU,
    "2",
    "4",
    "8",
    "16",
    "32",
    "64",
    "128",
    ENUM_MIN_MAX, pageDisplay, IsActive_MinMax, OnChanged_MinMax, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_10( cSmoothing,                                                                                                                                    //--- ������� - ����������� ---
    "�����.",
    "������������� ���������� ����� ��� ������� ����������� �� �������� ������ �������.",
    DISABLE_RU,
    "2 �����",
    "3 �����",
    "4 �����",
    "5 �����",
    "6 �����",
    "7 �����",
    "8 �����",
    "9 �����",
    "10 �����",
    ENUM_SMOOTHING.value, pageDisplay, FuncActive, Choice::EmptyChange, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_5( cRefreshFPS,                                                                                                                                 //--- ������� - ������� ������ ---
    "������� ������",
    "����� ������������ ����� ��������� � ������� ������.",
    "25",
    "10",
    "5",
    "2",
    "1",
    ENUM_SIGNALS_IN_SEC.value, pageDisplay, FuncActive, Choice::EmptyChange, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cScaleYtype,                                                                                                                                       //--- ������� - �������� ---
    "��������",
    "����� ����� ��������� �������� �� ���������\n1. \"����������\" - ����������� ��������� ��������.\n2. \"�������\" - ����������� ��������� "
    "�������� �� ������.",
    "����������",
    "�������",
    LINKING_RSHIFT, pageDisplay, FuncActive, Choice::EmptyChange, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_4( cType, // -V206                                                                                                                                       //--- ������� - ����� ---
    "�����",
    "����� ���� �����",
    "��� 1",
    "��� 2",
    "��� 3",
    "��� 4",
    TYPE_GRID, pageDisplay, FuncActive, Choice::EmptyChange, Choice::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_AverageNum(bool)
{
    Osci::Averager::SettingChanged();
}

DEF_CHOICE_9(cAverage_Num,                                                                                                                        //--- ������� - ���������� - ���������� ---
    "����������",
    "����� ���������� ��������� ���������, �� ������� ������������ ����������.",
    DISABLE_RU,
    "2",
    "4",
    "8",
    "16",
    "32",
    "64",
    "128",
    "256",
    ENUM_AVE, pageDisplay, FuncActive, OnChange_AverageNum, Choice::EmptyDraw
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_9( pageDisplay, // -V641 // -V1027                                                                                                                                 //--- ������� ---
    "�������",
    "�������� ��������� ����������� �������.",
    &cViewMode,                             ///< ������� - �����������
    PageDisplay::PageAccumulation::pointer, ///< ������� - ����������
    &cAverage_Num,                          ///< ������� - ����������
    //PageDisplay::PageAverage::pointer,      ///< ������� - ����������
    &cMinMax,                               ///< ������� - ��� ����
    &cSmoothing,                            ///< ������� - �����������
    &cRefreshFPS,                           ///< ������� - ������� ������
    &cType,                                 ///< ������� - �����
    //PageDisplay::PageGrid::pointer,         ///< ������� - �����
    &cScaleYtype,                           ///< ������� - ��������
    PageDisplay::PageSettings::pointer,     ///< ������� - ���������
//    &cThickness,                            ///< ������� - �������
    Page::Name::Display, nullptr, FuncActive, FuncPressPage, FuncDrawPage, FuncRegSetPage
)
