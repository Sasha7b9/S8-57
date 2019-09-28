#pragma once
#include "SettingsMath.h"
#include "SettingsMemory.h"
#include "SettingsDebug.h"
#include "SettingsNRST.h"
#include "SettingsService.h"
#include "SettingsTime.h"
#include "Tester/Tester.h"
#include "Osci/FrequencyCounter.h"
#include "Osci/Measurements/Cursors.h"
#include "Menu/Menu.h"
#include "Display/Grid_Types.h"
#include "Display/Colors.h"
#include "Osci/Measurements/Measures.h"
#include "Osci/Measurements/Measures_Settings.h"
#include "Multimeter/Multimeter.h"
#include "Recorder/Recorder_Settings.h"
#include "Osci/Measurements/Cursors_Settings.h"
#include "Tester/Tester_Settings.h"
#include "Multimeter/Multimeter_Settings.h"


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
struct SettingsDisplay
{
    Display::ModeDrawSignal::E      modeDrawSignal;
    Display::Background::E          background;            ///< ���� ����.
    Display::ENumMinMax::E          ENumMinMax;            ///< ������������ ���������� ��������� ��� ����������� ��������� � ���������.
    uint8                           notUsing0;
    Display::ENumAverage::E         ENumAverage;           ///< ����� ���������� �������.
    Display::ENumAccum::E           ENumAccum;             ///< ����� ���������� ������� �� ������.
    Display::ModeAccumulation::E    modeAccumulation;      ///< ����� ���������� ��������.
    Display::ENumSmoothing          ENumSmoothing;         ///< ������������ ���������� ����� ��� ����������� �������.
    Display::ENumSignalsInSec       ENumSignalsInSec;      ///< ������������ ����� ���������� ������� � �������.
    Grid::Type::E                   typeGrid;              ///< ��� �����
    int                             brightnessGrid;        ///< ������� ����� �� 0 �� 100.
    Display::LinkingRShift::E       linkingRShift;         ///< ��� �������� � �������� �� ���������.
    int16                           brightness;            ///< ������� �������.
    Menu::AutoHide::E               menuAutoHide;          ///< ����� ������� ������� ����� ���������� ������� ������� ������� ����.
    int16                           shiftInMemory;         ///< \brief ���������� �������� ������ ���� ����� ������������ �������� ����� ������ � 
                                                           ///< ������. �.�. ��� �������� ��������� ����� � ��� ���� ������ ���������� ����� �� ������.
    Chan::E                         lastAffectedChannel;   ///< \brief ��������� ����������� �����. ������������ ��� ����������� ������ ��������
                                                           ///< �� ����� � ���������� ���� ������ �������
};

struct SettingsChannel
{
    uint16                         shift[Chan::Size];      ///< ����� ������ �� ���������
    Osci::Settings::Range::E       range[Chan::Size];      ///< ������� ������ �� ���������
    FPGA::Settings::ModeCouple::E  couple[Chan::Size];     ///< ����� �� �����
    bool                           enabled[Chan::Size];    ///< �������/�������� �����
    int8                           balanceShiftADC[2];     ///< ���������� �������� ��� ������������ ���.
    FPGA::Settings::Bandwidth      bandwidth[2];           ///< ����������� ������.
    bool                           inverse[2];
    Divider::E                     divider[2];             ///< ���������.
    CalibrationMode::E             calibrationMode[2];     ///< ����� ����������.
};

struct SettingsTrig
{
    Osci::Settings::Trig::Source::E    source;
    Osci::Settings::Trig::Input::E     input;
    Osci::Settings::Trig::Polarity::E  polarity;
    uint16                             lev[Chan::Size];
    Osci::Settings::Trig::StartMode::E startMode;           ///< ����� �������.
    Osci::Settings::Trig::ModeFind::E  modeFind;            ///< ����� ������������� - ������� ��� �������������.
                                            /// \todo ����������� trig_holdOff ������������
    int16                              holdOff;             ///< ��������� �������������
    bool                               holdOffEnabled;      ///< ��������� ��������� �������������
};

struct SettingsTime
{
    int                              shift;
    Osci::Settings::TBase::E         base;
    Osci::Settings::PeakDetMode::E   peakDet;
    Osci::Settings::TPos::E          TPos;
    Osci::Settings::SampleType::E    sampleType;
    Osci::Settings::FunctionTime::E  timeDivXPos;
    Osci::Settings::LinkingTShift::E linkingTShift;                 ///< ��� �������� �������� �� �����������
    Osci::Settings::SampleType::E    sampleTypeOld;
};

struct SettingsCursors
{
    bool                                     showCursors;             ///< ���������� �� �������.
    Osci::Measurements::Cursors::LookMode::E lookMode[2];             ///< ������ �������� �� ��������� ��� ���� ��� ��������.
    bool                                     showFreq;                ///< ������������� � true ��������, ��� ����� ���������� �� ������ 1/dT ����� ���������.
    Osci::Measurements::Cursors::Active::E   active;                  ///< ����� ������� ����� �������.
    Chan::E                                  source;                  ///< �������� - � ������ ������ ��������� �������.
    Osci::Measurements::Cursors::Control::E  cntrlU[Chan::Size];      ///< �������� ������� ����������.
    Osci::Measurements::Cursors::Control::E  cntrlT[Chan::Size];      ///< �������� ������� �������.
    Osci::Measurements::Cursors::Movement::E movement;                ///< ��� ������������ �������� - �� ������ ��� ���������.
    float                                    deltaU100percents[2];    ///< ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float                                    deltaT100percents[2];    ///< ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    float                                    posCurU[Chan::Size][2];  ///< ������� ������� �������� ���������� ����� �������.
    float                                    posCurT[Chan::Size][2];  ///< ������� ������� �������� ������� ����� �������.
};

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

    SettingsDisplay disp;
    SettingsChannel ch;
    SettingsTrig    trig;
    SettingsTime    time;
    SettingsCursors curs;

    // ���� ������

#define MAX_SYMBOLS_IN_FILE_NAME 35
    Osci::Settings::Memory::ENumPointsFPGA::E   mem_enumPoints;                             ///< ����� �����
    ModeBtnMemory::E                            mem_modeBtnMemory;
    ModeWork::E                                 mem_modeWork;                               ///< ����� ������.
    bool                                        mem_flashAutoConnect;                       ///< ���� true, ��� ����������� ������ ������������� ��������� ����-��������.
    int8                                        mem_indexCurSymbolNameMask;                 ///< ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    ModeSaveSignal::E                           mem_modeSaveSignal;                         ///< � ����� ���� ��������� ������.
    char                                        mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     ///< ��� ����� ��� ������ ������� �������.
    ModeShowIntMem::E                           mem_modeShowIntMem;                         ///< ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
    FileNamingMode::E                           mem_fileNamingMode;                         ///< ����� ���������� ������.
    char                                        mem_fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< \brief ����� ����� ��� ��������������� ���������� ������.
                        ///< \details ������� ����������.\n
                        /// \code
                        /// %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������
                        /// %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007
                        /// �������
                        /// name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32
                        /// ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� 
                        /// ����� ������ ����� 0001, �.�. ��� ����������� ������ ���������������.
                        /// \endcode

    // ���� ���������

    bool                                                meas_show;              ///< ���������� �� ���������.
    Osci::Measurements::Settings::OnDisplay::E          meas_number;            ///< ������� ��������� ��������.
    Osci::Measurements::Settings::Source::E             meas_source;            ///< ��� ����� ������� �������� ���������.
    Osci::Measurements::Settings::ModeViewSignals::E    meas_modeViewSignals;   ///< ������� �� ������� ��� ������ ���������.
    Osci::Measurements::Measure::Type::E                meas_measures[15];      ///< ��������� ��� ��������� ���������.
    Osci::Measurements::Measure::Type::E                meas_marked;            ///< ���������, �� ������� ����� �������� �������.

    // ���� ������

    uint8               notUsing;
    Color::Scheme::E    serv_colorScheme;
    bool                serv_notUsing;
    CalibratorMode::E   serv_calibratorMode;            ///< ����� ������ �����������.
    uint8               serv_soundVolume;               ///< ��������� �����
    bool                serv_showInfoVoltage;           ///< ���������� ���������� ������� �� ������

    // ��������� ����������

    FuncModeDraw::E          math_modeDraw;             ///< ���������� ��� ����� ������� � ������ �������������� �������.
    bool                     math_enableFFT;
    ScaleFFT::E              math_scaleFFT;
    SourceFFT::E             math_sourceFFT;
    WindowFFT::E             math_windowFFT;
    uint8                    math_currentCursor;        ///< ����������, ����� �������� ������� ��������� ����� ���������.
    uint8                    math_posCur[2];            ///< ������� ������� �������. ���������� 0...256.
    FFTmaxDB::E              math_FFTmaxDB;
    MathFunction::E          math_function;
    ModeRegSet::E            math_modeRegSet;           ///< ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������.
    Osci::Settings::Range::E math_range;
    int8                     math_divider;
    uint16                   math_rShift;

    // ��������� �����������

    FrequencyCounter::Enabled::E        freq_enabled;
    FrequencyCounter::ModeView::E       freq_modeView;      
    FrequencyCounter::TimeCounting::E   freq_timeCounting;  ///< ����� ����� �������.
    FrequencyCounter::FreqClc::E        freq_freqClc;       ///< ������� ����������.
    FrequencyCounter::NumberPeriods::E  freq_numberPeriods; ///< ���������� ��������.

    // ���� �������

    int8                         dbg_showConsole;               ///< ���������� �� �������
    int16                        dbg_numStrings;                ///< ����� ����� � �������.
    int8                         dbg_sizeFont;                  ///< ������ ������ ������� - 0 - 5, 1 - 8.
    bool                         dbg_modePauseConsole;          ///< ���� true, �� ����� � ������� ��������������� �������� ������ ����/����.
    bool                         dbg_showAll;
    bool                         dbg_showFlag;
    bool                         dbg_showRShift[2];
    bool                         dbg_showTrigLev;
    bool                         dbg_showRange[2];
    bool                         dbg_showChanParam[2];
    bool                         dbg_showTrigParam;
    bool                         dbg_showTShift;
    bool                         dbg_showTBase;
    int16                        dbg_numMeasuresForGates;       ///< ����� ��������� ��� �����.
    bool                         dbg_showRandInfo;              ///< �������� ���������� �� ������������� - ������ � ��������� ��������.
    bool                         dbg_showRandStat;              ///< �������� ������ ����������.
    int16                        dbg_timeCompensation;          ///< �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    int16                        dbg_pretriggered;              ///< ������������ �������� ����������� ��� ������������ �������������.
    FPGA::Settings::Bandwidth::E dbg_bandwidth[2];              ///< \brief ����� ������� ������, ������� ����� ���������� ��� ������ � "�����-������" 
                                                                ///< �������� "������".
    bool                         dbg_ShowStats;                 ///< ���������� ���������� �� ������ (fps, ��������).
    Display::Orientation::E      dbg_Orientation;

    // ��������� ������-����������

    Tester::Settings::Control::E    test_control;
    Tester::Settings::Polarity::E   test_polarity;
    Tester::Settings::StepU::E      test_stepU;
    Tester::Settings::StepI::E      test_stepI;
    Display::ENumAverage::E         test_ave;                   ///< ���������� ����������
    Tester::Settings::ViewMode::E   test_viewMode;

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
