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

extern const Page pageDisplay;
extern const Page pageViewSignal;

const Page * const PageDisplay::PageView::self = (const Page *)&pageViewSignal;
const Page * const PageDisplay::self = (const Page *)&pageDisplay;

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
    ENUM_SMOOTHING.value, &PageDisplay::self, 0, 0, 0
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
    ENUM_SIGNALS_IN_SEC.value, &PageDisplay::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cScaleYtype,                                                                                                                                       //--- ������� - �������� ---
    "��������",
    "����� ����� ��������� �������� �� ���������\n1. \"����������\" - ����������� ��������� ��������.\n2. \"�������\" - ����������� ��������� "
    "�������� �� ������.",
    "����������",
    "�������",
    LINKING_RSHIFT, &PageDisplay::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_4( cType, // -V206                                                                                                                                       //--- ������� - ����� ---
    "�����",
    "����� ���� �����",
    "��� 1",
    "��� 2",
    "��� 3",
    "��� 4",
    TYPE_GRID, &PageDisplay::self, 0, 0, 0
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
    ENUM_AVE, &PageDisplay::self, 0, OnChange_AverageNum, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cViewMode,                                                                                                                                      //--- ������� - ����������� ---
    "�������",
    "����� ����� ����������� �������",
    "������",
    "�����",
    MODE_DRAW_SIGNAL, &PageDisplay::self, 0, 0, 0
)


DEF_PAGE_1( pageViewSignal, //-V641
    "�������",
    "��������� ����������� ��������",
    &cViewMode,
    Page::Name::Display_View, &PageDisplay::self, 0, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_8( pageDisplay, // -V641 // -V1027                                                                                                                                 //--- ������� ---
    "�������",
    "�������� ��������� ����������� �������.",
    &cViewMode,                             ///< ������� - �����������
    PageDisplay::PageAccumulation::self, ///< ������� - ����������
    &cAverage_Num,                          ///< ������� - ����������
    //PageDisplay::PageAverage::self,      ///< ������� - ����������
    &cSmoothing,                            ///< ������� - �����������
    &cType,                                 ///< ������� - �����
    &cRefreshFPS,                           ///< ������� - ������� ������
    //PageDisplay::PageGrid::self,         ///< ������� - �����
    &cScaleYtype,                           ///< ������� - ��������
    PageDisplay::PageSettings::self,     ///< ������� - ���������
//    &cThickness,                            ///< ������� - �������
    Page::Name::Display, 0, 0, 0, 0, 0
)
