#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageMeasures.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"


bool MeasuresModeViewSignals::IsCompress()
{
    return (set.meas.modeViewSignals == MeasuresModeViewSignals::Compress);
}


bool MeasuresOnDisplay::IsVertical()
{
    return (set.meas.number == MeasuresOnDisplay::_6_1) || (set.meas.number == MeasuresOnDisplay::_6_2);
}


bool CursorsControl::IsDisabledT()
{
    return S_CURS_CONTROL_T(S_CURS_SOURCE) == Disabled;
}


bool CursorsControl::IsEnabled1T()
{
    return (S_CURS_CONTROL_T(S_CURS_SOURCE) == _1 || S_CURS_CONTROL_T(S_CURS_SOURCE) == Both);
}


bool CursorsControl::IsEnabled2T()
{
    return (S_CURS_CONTROL_T(S_CURS_SOURCE) == _2 || S_CURS_CONTROL_T(S_CURS_SOURCE) == Both);
}


bool CursorsControl::IsDisabledU()
{
    return S_CURS_CONTROL_U(S_CURS_SOURCE) == Disabled;
}


bool CursorsControl::IsEnabled1U()
{
    return (S_CURS_CONTROL_U(S_CURS_SOURCE) == _1 || S_CURS_CONTROL_U(S_CURS_SOURCE) == Both);
}


bool CursorsControl::IsEnabled2U()
{
    return (S_CURS_CONTROL_U(S_CURS_SOURCE) == _2 || S_CURS_CONTROL_U(S_CURS_SOURCE) == Both);
}


DEF_PAGE_3( pMeasures,                                                                                                                                                    //--- ��������� ---
    "���������",
    "������ � ���������� ��������� - ��������� � ��������������",
    PageCursorsMeasures::self,
    PageAutoMeasures::self,
    PageMath::self,
    PageName::Measures, nullptr, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page *const PageMeasures::self = static_cast<const Page *>(&pMeasures);
