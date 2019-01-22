#include <stm32f4xx.h>
#include "defines.h"
#include "Menu/Pages/Include/PageChannels.h"
#include "Display/Display.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Settings.h"
#include "Menu/MenuItems.h"
#include "Keyboard/Keyboard.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Include/Definition.h"
#include "Utils/CommonFunctions.h"
#include "Utils/Dictionary.h"


extern const PageBase pChanA;
extern const PageBase pChanB;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char chanInputRu[] =   "1. \"���\" - �������� ������ �� �����.\n"
                                    "2. \"����\" - �� �������� ������ �� �����.";
static const char chanInputEn[] =   "1. \"Enable\" - signal output to the screen.\n"
                                    "2. \"Disable\" - no output to the screen.";

static const char chanCoupleRu[] =  "����� ��� ����� � ���������� �������.\n"
                                    "1. \"����\" - �������� ����.\n"
                                    "2. \"�����\" - �������� ����.\n"
                                    "3. \"�����\" - ���� �������� � �����.";
static const char chanCoupleEn[] =  "Sets a type of communication with a signal source.\n"
                                    "1. \"AC\" - open input.\n"
                                    "2. \"DC\" - closed input.\n"
                                    "3. \"Ground\" - input is connected to the ground.";

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageChannelA::OnChanged_Input(bool)
{

}

DEF_CHOICE_2(       cChanA_Input,                                                                                             //--- ����� 1 - ���� ---
    "����", "Input",
    chanInputRu,
    chanInputEn,
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    SET_ENABLED_A, pChanA, FuncActive, PageChannelA::OnChanged_Input, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageChannelA::OnChanged_Couple(bool)
{
    FPGA::Settings::ModeCouple::Set(Chan::A, SET_COUPLE_A);
}

DEF_CHOICE_3(       cChanA_Couple,                                                                                           //--- ����� 1 - ����� ---
    "�����", "Couple",
    chanCoupleRu,
    chanCoupleEn,
    "����",  "AC",
    "�����", "DC",
    "�����", "Ground",
    SET_COUPLE_A, pChanA, FuncActive, PageChannelA::OnChanged_Couple, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_ChanA_Bandwidth(bool)
{
    FPGA::Settings::Bandwidth::Load(Chan::A);
}

DEF_CHOICE_2( cChanA_Bandwidth,                                                                                                                                    //--- ����� 1 - ������ ---
    "������", "Bandwidth",
    "����� ������ ����������� ������",
    "Sets the channel bandwidth",
    "������", "Full",
    "20���",  "20MHz",
    SET_BANDWIDTH_A, pChanA, FuncActive, OnChanged_ChanA_Bandwidth, FuncDraw
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageChannelA::pointer = &pChanA;

DEF_PAGE_3( pChanA, // -V641                                                                                                                                                //--- ����� 1 ---
    "����� 1", "CHANNEL 1",
    "�������� ��������� ������ 1.",
    "Contains settings of the channel 1.",
    &cChanA_Input,              ///< ����� 1 - ����
    &cChanA_Couple,             ///< ����� 1 - �����
    &cChanA_Bandwidth,          ///< ����� 1 - ������
    Page::Name::ChannelA, Menu::pageMain, FuncActive, FuncPressPage, FuncDrawPage, FuncRegSetPage
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageChannelB::OnChanged_Input(bool active)
{
    if (!active)
    {
        Display::ShowWarning(Warning::TooLongMemory);
        return;
    }
}

DEF_CHOICE_2( cChanB_Input,                                                                                                                                          //--- ����� 2 - ���� ---
    "����", "Input",
    chanInputRu,
    chanInputEn,
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU,  ENABLE_EN,
    SET_ENABLED_B, pChanB, FuncActive, PageChannelB::OnChanged_Input, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageChannelB::OnChanged_Couple(bool)
{
    FPGA::Settings::ModeCouple::Set(Chan::B, SET_COUPLE_B);
}

DEF_CHOICE_3( cChanB_Couple,                                                                                                                                        //--- ����� 2 - ����� ---
    "�����", "Couple",
    chanCoupleRu,
    chanCoupleEn,
    "����",  "DC",
    "�����", "AC",
    "�����", "Ground",
    SET_COUPLE_B, pChanB, FuncActive, PageChannelB::OnChanged_Couple, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_BandwidthB(bool)
{
    FPGA::Settings::Bandwidth::Load(Chan::B);
}

DEF_CHOICE_2( cChanB_Bandwidth,                                                                                                                                    //--- ����� 2 - ������ ---
    "������", "Bandwidth",
    "",
    "",
    "������", "Full",
    "20���", "20MHz",
    SET_BANDWIDTH_B, pChanB, FuncActive, OnChanged_BandwidthB, FuncDraw
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageChannelB::pointer = &pChanB;

DEF_PAGE_3( pChanB, // -V641                                                                                                                                                //--- ����� 2 ---
    "����� 2", "CHANNEL 2",
    "�������� ��������� ������ 2.",
    "Contains settings of the channel 2.",
    &cChanB_Input,       // ����� 2 - ����
    &cChanB_Couple,      // ����� 2 - �����
    &cChanB_Bandwidth,   // ����� 2 - ������
    Page::Name::ChannelB, Menu::pageMain, FuncActive, FuncPressPage, FuncDrawPage, FuncRegSetPage
)
