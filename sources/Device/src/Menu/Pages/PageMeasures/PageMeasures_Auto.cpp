#include "defines.h"
#include "Menu/MenuItems.h"
#include "Osci/Measurements/Measures.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Include/PageMeasures.h"



DEF_CHOICE_2( cIsShow,                                                                                                                             //--- ��������� - ������� - ���������� ---
    "����������",
    "�������� ��� �� �������� ��������� �� �����",
    "���",
    "��",
    set.meas.show, &PageMeasuresAuto::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


static bool IsActive_NumberChannels()
{
    return set.meas.show;
}

DEF_CHOICE_7( cNumber,                                                                                                                             //--- ��������� - ������� - ���������� ---
    "����������"
    ,
    "������������� ������������ ���������� ��������� ���������:\n"
    "\"1\" - ���� ���������\n"
    "\"2\" - ��� ���������\n"
    "\"1�5\" - 1 ������ � ����� �����������\n"
    "\"2�5\" - 2 ������ � ����� ����������� � ������\n"
    "\"3�5\" - 3 ������ � ����� ����������� � ������\n"
    "\"6x1\" - 6 ����� �� ������ ��������� � ������\n"
    "\"6�2\" - 6 ����� �� ��� ��������� � ������"
    ,
    "1",
    "2",
    "1x5",
    "2x5",
    "3x5",
    "6x1",
    "6x2",
    set.meas.number, &PageMeasuresAuto::self, IsActive_NumberChannels, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_3( cChannels,                                                                                                                               //--- ��������� - ������� - ������ ---
    "������",
    "�� ����� ������� �������� ���������",
    "1",
    "2",
    "1 � 2",
    set.meas.source, &PageMeasuresAuto::self, IsActive_NumberChannels, Choice::Changed, Choice::AfterDraw
)


DEF_PAGE_4( pAuto, // -V641 // -V1027                                                                                                                              //--- ��������� - ���� ---
    "�������",
    "������ � ���������� �������������� ���������",
    &cIsShow,
    &cNumber,
    &cChannels,
    PageMeasuresAuto::PageTune::self,
    //&cMode,
    PageName::Measures_Auto, &PageMeasures::self, Item::Active, Page::Changed, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page * const PageMeasuresAuto::self = (const Page *)&pAuto;



/*
static bool IsActive_Mode()
{
    return SHOW_MEASURES;
}

_DEF_CHOICE_2( cMode,                                                                                                                                      //--- ��������� - ������� - ��� ---
    "���", "View",
    "��������� ��� ��� ���� ������ ������� ��� ���������� ���������� ��� ���������� ���������",
    "Decrease or no zone output signal to avoid overlapping of its measurement results",
    "��� ����",  "As is",
    "���������", "Reduce",
    MODE_VIEW_SIGNALS, pAuto, IsActive_Mode, 0, FuncDraw
)
*/
