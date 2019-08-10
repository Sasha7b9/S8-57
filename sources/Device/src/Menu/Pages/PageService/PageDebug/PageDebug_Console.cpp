#include "defines.h"
#include "Display/Colors.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageService.h"
#include "Settings/Settings.h"


extern const PageDef pageConsole;
extern const PageDef pageRegisters;

const Page * const PageDebug::PageConsole::self = (const Page *)&pageConsole;
const Page * const PageDebug::PageRegisters::self = (const Page *)&pageRegisters;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cShow,                                                                                                                                 //--- ������� - ������� - ���������� ---
    "����������",
    "",
    "���",
    "��",
    set.dbg_showConsole, &PageDebug::PageConsole::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR( gNumStrings,                                                                                                                          //--- ������� - ������� - ����� ����� ---
    "����� �����",
    "",
    CONSOLE_NUM_STRINGS, 0, 33, &PageDebug::PageConsole::self, 0, Console::OnChangedMaxStringsInConsole, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_CHOICE_2( cSizeFont,                                                                                                                          //--- ������� - ������� - ������ ������ ---
//    "������ ������",
//    "",
//    "5",
//    "8",
//    set.dbg_sizeFont, &PageDebug::PageConsole::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DEF_CHOICE_2( cModeStop,                                                                                                                          //--- ������� - ������� - ���. �������� ---
//    "���. ��������",
//    "������������� ����������� ������������ ������ � ������� ���� ������� �� ������ ����/����",
//    DISABLE_RU,
//    ENABLE_RU,
//    MODE_PAUSE_CONSOLE, &PageDebug::PageConsole::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_ShowAll,                                                                                                     //--- ������� - ������� - �������� - ���������� ��� ---
    "���������� ���",
    "���������� ��� ��������, ���������� � ��������",
    "���",
    "��",
    DBG_SHOW_ALL, &PageDebug::PageRegisters::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Console_Registers()
{
    return DBG_SHOW_ALL;
}

DEF_CHOICE_2( cRegisters_RD_FL,                                                                                                                //--- ������� - ������� - �������� - RD_FL ---
    "RD_FL",
    "",
    DISABLE_RU,
    ENABLE_RU,
    DBG_SHOW_FLAG, &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_RShiftA,                                                                                                           //--- ������� - ������� - �������� - U ��. 1� ---
    "U ��. 1�",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showRShift[Chan::A], &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_RShiftB,                                                                                                           //--- ������� - ������� - �������� - U ��. 2� ---
    "U ��. 2�",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showRShift[Chan::B], &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_TrigLev,                                                                                                           //--- ������� - ������� - �������� - U �����. ---
    "U �����.",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showTrigLev, &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_RangeA,                                                                                                         //--- ������� - ������� - �������� - �����/��� 1 ---
    "�����/��� 1",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showRange[Chan::A], &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_RangeB,                                                                                                         //--- ������� - ������� - �������� - �����/��� 2 ---
    "�����/��� 2",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showRange[Chan::B], &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_TrigParam,                                                                                                    //--- ������� - ������� - �������� - �����. �����. ---
    "�����. �����.",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showTrigParam, &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_ChanParamA,                                                                                                   //--- ������� - ������� - �������� - �����. ���. 2 ---
    "�����. ���. 1",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showChanParam[Chan::A], &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_ChanParamB,                                                                                                   //--- ������� - ������� - �������� - �����. ���. 2 ---
    "�����. ���. 2",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showChanParam[Chan::B], &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_TBase,                                                                                                            //--- ������� - ������� - �������� - �����/��� ---
    "�����/���",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showTBase, &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cRegisters_TShift,                                                                                                               //--- ������� - ������� - �������� - � ��. ---
    "� ��.",
    "",
    DISABLE_RU,
    ENABLE_RU,
    set.dbg_showTShift, &PageDebug::PageRegisters::self, IsActive_Console_Registers, 0, 0
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_12( pageRegisters, // -V641                                                                                                                   //--- ������� - ������� - �������� ---
    "��������",
    "",
    &cRegisters_ShowAll,        ///< ������� - ������� - �������� - ���������� ���
    &cRegisters_RD_FL,          ///< ������� - ������� - �������� - RD_FL
    &cRegisters_RShiftA,        ///< ������� - ������� - �������� - U ��. 1�
    &cRegisters_RShiftB,        ///< ������� - ������� - �������� - U ��. 2�
    &cRegisters_TrigLev,        ///< ������� - ������� - �������� - U �����
    &cRegisters_RangeA,         ///< ������� - ������� - �������� - �����/��� 1
    &cRegisters_RangeB,         ///< ������� - ������� - �������� - �����/��� 2
    &cRegisters_TrigParam,      ///< ������� - ������� - �������� - �����. �����.
    &cRegisters_ChanParamA,     ///< ������� - ������� - �������� - �����. ���. 1
    &cRegisters_ChanParamB,     ///< ������� - ������� - �������� - �����. ���. 2
    &cRegisters_TBase,          ///< ������� - ������� - �������� - �����/���
    &cRegisters_TShift,         ///< ������� - ������� - �������� - � ��.
    Page::Name::Debug_Console_Registers, &PageDebug::PageConsole::self, 0, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//static void Draw_Console_SizeSettings(int x, int y)
//{
//    String("����.�����. %d", sizeof(Settings)).Draw(x + 6, y + 13, Color::BACK);
//}
//
//DEF_BUTTON( bSizeSettings,                                                                                                                      //--- ������� - ������� - ������ �������� ---
//    "",
//    "���������� ������� ������ ��������� ��� ���������� ��������",
//    &PageDebug::PageConsole::self, 0, 0, Draw_Console_SizeSettings
//)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_2( pageConsole, // -V641 // -V1027                                                                                                                       //--- ������� - ������� ---
    "�������",
    "��������� ������������ � ����������� ���������� �������",
    &cShow,             ///< ������� - ������� - ����������
    &gNumStrings,       ///< ������� - ������� - ����� �����
//    &cSizeFont,         ///< ������� - ������� - ������ ������
//    &cModeStop,         ///< ������� - ������� - ���. ��������
//    &pageRegisters,     ///< ������� - ������� - ��������
//    &bSizeSettings,     ///< ������� - ������� - ������ ��������
    Page::Name::Debug_Console, &PageDebug::self, 0, 0, 0, 0
)

