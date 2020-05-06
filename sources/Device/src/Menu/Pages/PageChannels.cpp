#include "defines.h"
#include "FPGA/Calibrator.h"
#include "Osci/Osci.h"
#include "Settings/Settings.h"
#include <cstring>


static const char chanInput[] =   "1. \"���\" - �������� ������ �� �����.\n"
                                  "2. \"����\" - �� �������� ������ �� �����.";

static const char chanCouple[] =  "����� ��� ����� � ���������� �������.\n"
                                  "1. \"����\" - �������� ����.\n"
                                  "2. \"�����\" - �������� ����.\n"
                                  "3. \"�����\" - ���� �������� � �����.";


DEF_CHOICE_2( cInputA,                                                                                                                                               //--- ����� 1 - ���� ---
    "����",
    chanInput,
    DISABLE_RU,
    ENABLE_RU,
    S_CHANNEL_ENABLED_A, &PageChannelA::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


void PageChannelA::OnChanged_Couple(bool)
{
    Range::LoadBoth();
}

DEF_CHOICE_3( cCoupleA,                                                                                                                                             //--- ����� 1 - ����� ---
    "�����",
    chanCouple,
    "����",
    "�����",
    "�����",
    ModeCouple::Ref(ChanA), &PageChannelA::self, Item::Active, PageChannelA::OnChanged_Couple, Choice::AfterDraw
)


static void OnChanged_BandwidthA(bool)
{
    Bandwidth::Load(ChanA);
}

DEF_CHOICE_2( cBandwidthA,                                                                                                                                         //--- ����� 1 - ������ ---
    "������",
    "����� ������ ����������� ������",
    "������",
    "20���",
    S_BANDWIDTH(ChanA), &PageChannelA::self, Item::Active, OnChanged_BandwidthA, Choice::AfterDraw
)


static void Balance(Chan::E ch)
{
    Calibrator::BalanceChannel(ch);
}


static void OnPress_BalanceA()
{
    Balance(ChanA);
}

DEF_BUTTON( bBalanceA,                                                                                                                                      //--- ����� 1 - ������������� ---
    "������",
    "",
    &PageChannelA::self, Item::Active, OnPress_BalanceA
)


DEF_CHOICE_2( cDividerA,                                                                                                                                         //--- ����� 1 - �������� ---
    "��������",
    "",
    "1X",
    "10X",
    S_DIVIDER_A, &PageChannelA::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_2( cInverseA,                                                                                                                                         //--- ����� 1 - �������� ---
    "��������",
    "����������� ������ ������������ ������ 0�",
    "����",
    "���",
    S_INVERSE_A, &PageChannelA::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_PAGE_6( pChanA,                                                                                                                                                         //--- ����� 1 ---
    "����� 1",
    "�������� ��������� ������ 1.",
    &cInputA,
    &cCoupleA,
    &cBandwidthA,
    &cDividerA,
    &bBalanceA,
    &cInverseA,
    PageName::ChannelA, nullptr, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page * const PageChannelA::self = static_cast<const Page *>(&pChanA);


DEF_CHOICE_2( cInputB,                                                                                                                                               //--- ����� 2 - ���� ---
    "����",
    chanInput,
    DISABLE_RU,
    ENABLE_RU,
    S_CHANNEL_ENABLED_B, &PageChannelB::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


void PageChannelB::OnChanged_Couple(bool)
{
    Range::LoadBoth();
}

DEF_CHOICE_3( cCoupleB,                                                                                                                                             //--- ����� 2 - ����� ---
    "�����",
    chanCouple,
    "����",
    "�����",
    "�����",
    ModeCouple::Ref(ChanB), &PageChannelB::self, Item::Active, PageChannelB::OnChanged_Couple, Choice::AfterDraw
)


static void OnChanged_BandwidthB(bool)
{
    Bandwidth::Load(ChanB);
}

DEF_CHOICE_2( cBandwidthB,                                                                                                                                         //--- ����� 2 - ������ ---
    "������",
    "",
    "������",
    "20���",
    S_BANDWIDTH(ChanB), &PageChannelB::self, Item::Active, OnChanged_BandwidthB, Choice::AfterDraw
)


static void OnPress_BalanceB()
{
    Balance(ChanB);
}

DEF_BUTTON( bBalanceB,                                                                                                                                       //--- ����� 2 - ������������ ---
    "������",
    "",
    &PageChannelB::self, Item::Active, OnPress_BalanceB
)


DEF_CHOICE_2( cDividerB,                                                                                                                                         //--- ����� 2 - �������� ---
    "��������",
    "",
    "1X",
    "10X",
    S_DIVIDER_B, &PageChannelB::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_CHOICE_2( cInverseB,                                                                                                                                         //--- ����� 2 - �������� ---
    "��������",
    "����������� ������ ������������ ������ 0�",
    "����",
    "���",
    S_INVERSE_B, &PageChannelB::self, Item::Active, Choice::Changed, Choice::AfterDraw
)


DEF_PAGE_6( pChanB,                                                                                                                                                         //--- ����� 2 ---
    "����� 2",
    "�������� ��������� ������ 2.",
    &cInputB,
    &cCoupleB,
    &cBandwidthB,
    &cDividerB,
    &bBalanceB,
    &cInverseB,
    PageName::ChannelB, nullptr, Item::Active, Page::NormalTitle, Page::OpenClose, Page::BeforeDraw, Page::HandlerKeyEvent
)

const Page * const PageChannelB::self = static_cast<const Page *>(&pChanB);
