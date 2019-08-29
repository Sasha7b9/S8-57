#include "defines.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Settings.h"
#include "Menu/Pages/Include/PageTrig.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"


extern const Page pHoldOff;

const Page * const PageTrig::PageHoldOff::self = (const Page *)&pHoldOff;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChanged_HoldOff(bool)
{
    Osci::Settings::LoadHoldfOff();
}

DEF_CHOICE_2( cHoldOff,                                                                                                                               //--- ����� - ��������� - ��������� ---
    "���������",
    "��������/��������� ����� �������� �������������"
    ,
    DISABLE_RU,
    ENABLE_RU,
    TRIG_HOLDOFF_ENABLED,
    &PageTrig::PageHoldOff::self, E_BtV, OnChanged_HoldOff, E_VII
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Duration()
{
    Osci::Settings::LoadHoldfOff();
}

DEF_GOVERNOR( gDuration,                                                                                                                           //--- ����� - ��������� - ������������ ---
    "������������",
    "����� ������������ ���������� ����� ���������� �������������",
    TRIG_HOLDOFF, 10, 32000,
    &PageTrig::PageHoldOff::self, E_BtV, OnChanged_Duration
)

/// \todo gDuration ������ ������������ ����������� �������� �������� ��������, ��� 32000


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_2( pHoldOff, // -V641 // -V1027                                                                                                                          //--- ����� - ��������� ---
    "���������",
    "",
    &cHoldOff,          ///< ����� - ��������� - ���������
    &gDuration,         ///< ����� - ��������� - ������������
    PageName::Trig_HoldOff,
    &PageTrig::self, E_BtV, E_VB, E_VV, E_BfKE
)
