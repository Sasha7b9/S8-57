#include "defines.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Settings.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageService.h"
#include "Settings/Settings.h"
#include "Settings/SettingsNRST.h"


using namespace Osci::Settings;

extern const PageDef pageRand;

const Page * const PageDebug::PageRand::self = (const Page *)&pageRand;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_GOVERNOR( gRand_NumAverage,                                                                                                                        //--- ������� - ����-��� - ������. ---
//    "������.",
//    "",
//    NRST_NUM_AVE_FOR_RAND, 1, 32, &PageDebug::PageRand::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_GOVERNOR( gRand_NumSmooth,                                                                                                                     //--- ������� - ����-��� - ����������� ---
//    "�����������",
//    "",
//    NRST_NUM_SMOOTH_FOR_RAND, 1, 10, &PageDebug::PageRand::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//static void OnChanged_Rand_NumMeasures()
//{
//}
//
//DEF_GOVERNOR( gRand_NumMeasures,                                                                                                                  //--- ������� - ����-��� - ���-�/������ ---
//    "���-�/������",
//    "",
//    NUM_MEASURES_FOR_GATES, 1, 2500, &PageDebug::PageRand::self, 0, OnChanged_Rand_NumMeasures, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_CHOICE_2( cRand_ShowInfo,                                                                                                                       //--- ������� - ����-��� - ���������� ---
//    "����������",
//    "���������� ���������� � ������� �������������"
//    ,
//    "�� ����������",
//    "����������",
//    SHOW_RAND_INFO, &PageDebug::PageRand::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_CHOICE_2( gRand_ShowStat,                                                                                                                       //--- ������� - ����-��� - ���������� ---
//    "����������",
//    "���������� ������ ����������"
//    ,
//    "�� ����������",
//    "����������",
//    SHOW_RAND_STAT, &PageDebug::PageRand::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//static void OnChanged_Rand_TimeCompensation()
//{
//}
//
//DEF_GOVERNOR( gRand_TimeCompensation,                                                                                                     //--- ������� - ����-��� - ����������� �������� ---
//    "����������� ��������",
//    "���������� ����������� �������� ��� 40 ��",
//    TIME_COMPENSATION, 0, 510, &PageDebug::PageRand::self, 0, OnChanged_Rand_TimeCompensation, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//static void OnChanged_Rand_AddTimeShift()
//{
//    TShift::Set(SET_TSHIFT);
//}
//
//static int16 addShift = 0;
//
//DEF_GOVERNOR( gRand_AddTimeShift,                                                                                                                     //--- ������� - ����-��� - �������� ---
//    "��� ��������",
//    "���������� ������� ��� �������� tShift",
//    addShift, -100, 100, &PageDebug::PageRand::self, 0, OnChanged_Rand_AddTimeShift, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//static void OnChanged_Rand_Pretriggered()
//{
//    TShift::Load();
//}
//
//DEF_GOVERNOR( gRand_Pretriggered,                                                                                                                   //--- ������� - ����-��� - ���������� ---
//    "����������",
//    "�������� �����������, ������� ������� � ������������",
//    PRETRIGGERED, 0, 30000, &PageDebug::PageRand::self, 0, OnChanged_Rand_Pretriggered, 0
//)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_16( gGateMax,                                                                                                                           //--- ������� - ����-��� - ������ ���� ---
    "������ ����",
    "������������� ����������� ���������� �� ��������� ����� ��� �������������",
    "0",
    "10",
    "20",
    "30",
    "40",
    "50",
    "60",
    "70",
    "80",
    "90",
    "100",
    "110",
    "120",
    "130",
    "140",
    "150",
    set.dbg_enum_gate_max, &PageDebug::PageRand::self, 0, 0, 0
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_16( gGateMin,                                                                                                                            //--- ������� - ����-��� - ������ ��� ---
    "������ ���",
    "������������� ����������� ���������� �� �������� ����� ��� �������������",
    "0",
    "10",
    "20",
    "30",
    "40",
    "50",
    "60",
    "70",
    "80",
    "90",
    "100",
    "110",
    "120",
    "130",
    "140",
    "150",
    set.dbg_enum_gate_min, &PageDebug::PageRand::self, 0, 0, 0
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_2( pageRand, // -V641 // -V1027                                                                                                                         //--- ������� - ����-��� ---
    "����-���",
    "",
    &gGateMin,                      ///< ������� - ����-��� - ������ ���
    &gGateMax,                      ///< ������� - ����-��� - ������ ����

    //&gRand_NumAverage,          ///< ������� - ����-��� - ������.
    //&gRand_NumSmooth,           ///< ������� - ����-��� - �����������
    //&gRand_NumMeasures,         ///< ������� - ����-��� - ���-�/������
    //&cRand_ShowInfo,            ///< ������� - ����-��� - ����������
    //&gRand_ShowStat,            ///< ������� - ����-��� - ����������
    //&gRand_TimeCompensation,    ///< ������� - ����-��� - ����������� ��������
    //&gRand_AddTimeShift,        ///< ������� - ����-��� - ��������
    //&gRand_Pretriggered,        ///< ������� - �A��-��� - ����������
    Page::Name::Debug_Rand, &PageDebug::self, 0, 0, 0, 0
)
