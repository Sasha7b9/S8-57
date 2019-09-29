#pragma once
#include "SettingsNRST.h"
#include "Tester/Tester.h"
#include "Osci/FrequencyCounter.h"
#include "Osci/Measurements/Cursors.h"
#include "Menu/Menu.h"
#include "Display/Colors.h"
#include "Osci/Measurements/Measures.h"
#include "Multimeter/Multimeter.h"
#include "Recorder/Recorder_Settings.h"
#include "Osci/Measurements/Cursors_Settings.h"
#include "Multimeter/Multimeter_Settings.h"
#include "Menu/Pages/Include/PageChannels.h"
#include "Menu/Pages/Include/PageDisplay.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Menu/Pages/Include/PageMemory.h"
#include "Menu/Pages/Include/PageService.h"
#include "Menu/Pages/Include/PageTime.h"
#include "Menu/Pages/Include/PageTrig.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SET_SIZE                    (set.size)
#define SET_CRC32                   (set.crc32)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TRIG_MODE                   (set.trig.mode)
#define TRIG_HOLDOFF                (set.trig.holdOff)
#define TRIG_HOLDOFF_ENABLED        (set.trig.holdOffEnabled)

/// ���������� ������� ��������� ������ �� �������� Page::Name.
#define MENU_POS_ACT_ITEM(name)     (set.menu_posActItem[name])

#define SET_DIVIDER(ch)             (divider[ch])
#define SET_DIVIDER_IS_1(ch)        (SET_DIVIDER(ch) == 0)
#define SET_DIVIDER_IS_10(ch)       (SET_DIVIDER(ch) == 1)

#define SET_DIVIDER_ABS(ch)         ((divider[ch] == 0) ? 1 : 10)


#pragma pack(push, 1)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Settings
{
public:
    static void Load(bool _default = false);
    static void Save();
    static void Reset();

    void SetData(uint8 data[1024]);
    /// ��������� �������� ������������� ����. ���������� ����� ������ ��������� ������ (���� ���� ���������� ��������� ��������)
    void SaveEnum16(uint8 name, uint8 value);

    uint                size;                               ///< ������ ������ ��������� � ������
    uint                crc32;                              ///< \brief ����������� ����� ������ ��������� � ����������� � ��� �����������

    SettingsDisplay     disp;
    SettingsChannel     ch;
    SettingsTrig        trig;
    SettingsTime        time;
    SettingsCursors     curs;
    SettingsMemory      mem;
    SettingsMath        math;
    SettingsMeasures    meas;
    SettingsService     serv;
    SettingsFreqMeter   freq;
    SettingsDebug       dbg;
    SettingsTester      test;

    // ��������� ����

    bool                menu_show;                                                  ///< ���� true, �� ����� ���������� ������� ��������
    int8                menu_posActItem[PageName::Number];                          ///< \brief ������� ��������� ������. bit7 == 1 - item is opened, 0x7f - ��� ��������� ������.
    int8                menu_currentSubPage[PageName::Number];                      ///< ����� ������� �����������.

    // �������������� ��������� ����������

    int16               nrst_balanceADC[Chan::Size];                                ///< �������� ��������������� �������� ��� ��� ������ ������������.
    BalanceADC::E       nrst_balanceADCtype;                                        ///< ��� ������������.
    StretchADC::E       nrst_stretchADCtype;                                        ///< ��� �������� ������.
    int16               nrst_StretchADC[Chan::Size][3];                             ///< \brief ����������� ����������� ��� �������, �������������� �
                        ///< ������������ �������. ����� �������� � ����� ����, ����� �������� �������� �����������, ����� ��������� �� 1000 �
                        ///< ��������� �������.
    int16               nrst_rShiftAddStable[Chan::Size][3];                        ///< ���������� �������� ��� ��� ����� �������������� ����������. ������� �������� ��� ���������
    int16               nrst_numAveForRand;                                         ///< �� �������� ���������� ��������� ������ � ������ �������������.
    int16               nrst_numSmoothForRand;                                      ///< ����� ����� ��� ����������� ������ � �������������.
    int16               nrst_rShiftAdd[Chan::Size][Osci::Settings::Range::Size][2]; ///< ���������� ��������, ������� ������� ���� ��� ���������� � ������������
    int16               nrst_correctionTime;                                        ///< ����������� ��������� �������.

    // ��������� �����������
    Multimeter::Settings::AVP::E              multi_avp;
    Multimeter::Measure::E                    multi_meas;
    Multimeter::Settings::RangeDC::E          multi_rangeDC;
    Multimeter::Settings::RangeAC::E          multi_rangeAC;
    Multimeter::Settings::RangeCurrent::E     multi_rangeCurrentAC;     ///< ������ ��������� ����������� ����
    Multimeter::Settings::RangeCurrent::E     multi_rangeCurrentDC;     ///< ������ ��������� ����������� ����
    Multimeter::Settings::RangeResistance::E  multi_rangeResist;

    // ��������� ������������
    bool                               rec_sourceChanA;      ///< ��������� ������ ������ 1
    bool                               rec_sourceChanB;      ///< ��������� ������ ������ 2
    bool                               rec_sourceSensor;     ///< ��������� ������ ��������� �������
    Recorder::Settings::TypeStorage::E rec_storageRecord;    ///< ���� ��������� ������
    Recorder::Settings::TypeStorage::E rec_storagePlay;      ///< ������ ����� ����������� ������
    Recorder::Settings::Axis::E        rec_axisMove;         ///< ������� ��� �����������
    Recorder::Settings::Axis::E        rec_axisZoom;         ///< ������� ��� ���������������
    Recorder::Settings::ScaleX         rec_scaleX;           ///< ������������� ������� �� �������
    Osci::Settings::Range::E           unused[2];            ///< ������� �� ��������� � ������ ������������


    /*  !!!!!!!!!!!!!!!!!!!!!!                                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        !!!!!!!!!!!!!!!!!!!!!! ��� ��������� �������� ��� ������� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        !!!!!!!!!!!!!!!!!!!!!!                                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    */

    int16   dbg_enum_gate_max;                              ///< ����������� ����� � ������������� ������
    int16   dbg_enum_gate_min;                              ///< ����������� ����� � ������������� �����

    int8    addRShift[2][Osci::Settings::Range::Size];      ///< ���������� �������� ��� 

    /// ��������� �� ���������
    static const Settings defaultSettings;
};

#pragma pack(pop)

extern Settings set;

extern int8 divider[2]; // �������� ������
