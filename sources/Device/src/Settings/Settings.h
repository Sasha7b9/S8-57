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
#define TRIG_MODE                   (set.trig_mode)
#define TRIG_HOLDOFF                (set.trig_holdOff)
#define TRIG_HOLDOFF_ENABLED        (set.trig_holdOffEnabled)

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

    // ���� �������
                                                                ///< ����������� �� ������� �����, ���������� �� ���� �����
    Display::ModeDrawSignal::E      disp_modeDrawSignal;
    Display::Background::E          disp_background;            ///< ���� ����.
    Display::ENumMinMax::E          disp_ENumMinMax;            ///< ������������ ���������� ��������� ��� ����������� ��������� � ���������.
    uint8                           not_using0;
    Display::ENumAverage::E         disp_ENumAverage;           ///< ����� ���������� �������.
    Display::ENumAccum::E           disp_ENumAccum;             ///< ����� ���������� ������� �� ������.
    Display::ModeAccumulation::E    disp_modeAccumulation;      ///< ����� ���������� ��������.
    Display::ENumSmoothing          disp_ENumSmoothing;         ///< ������������ ���������� ����� ��� ����������� �������.
    Display::ENumSignalsInSec       disp_ENumSignalsInSec;      ///< ������������ ����� ���������� ������� � �������.
    Grid::Type::E                   disp_typeGrid;              ///< ��� �����
    int                             disp_brightnessGrid;        ///< ������� ����� �� 0 �� 100.
    Display::LinkingRShift::E       disp_linkingRShift;         ///< ��� �������� � �������� �� ���������.
    int16                           disp_brightness;            ///< ������� �������.
    Menu::AutoHide::E               disp_menuAutoHide;          ///< ����� ������� ������� ����� ���������� ������� ������� ������� ����.
    int16                           disp_shiftInMemory;         ///< \brief ���������� �������� ������ ���� ����� ������������ �������� ����� ������ � 
                                                                ///< ������. �.�. ��� �������� ��������� ����� � ��� ���� ������ ���������� ����� �� ������.
    Chan::E                         disp_lastAffectedChannel;   ///< \brief ��������� ����������� �����. ������������ ��� ����������� ������ ��������
                                                                ///< �� ����� � ���������� ���� ������ �������

    // ���� ����� 1, ����� 2

    uint16                         chan_shift[Chan::Size];      ///< ����� ������ �� ���������
    Osci::Settings::Range::E       chan_range[Chan::Size];      ///< ������� ������ �� ���������
    FPGA::Settings::ModeCouple::E  chan_couple[Chan::Size];     ///< ����� �� �����
    bool                           chan_enabled[Chan::Size];    ///< �������/�������� �����
    int8                           chan_balanceShiftADC[2];     ///< ���������� �������� ��� ������������ ���.
    FPGA::Settings::Bandwidth      chan_bandwidth[2];           ///< ����������� ������.
    bool                           chan_inverse[2];
    Divider::E                     chan_divider[2];             ///< ���������.
    CalibrationMode::E             chan_calibrationMode[2];     ///< ����� ����������.

    // ���� �������������

    Osci::Settings::Trig::Source::E    trig_source;
    Osci::Settings::Trig::Input::E     trig_input;
    Osci::Settings::Trig::Polarity::E  trig_polarity;
    uint16                             trig_lev[Chan::Size];
    Osci::Settings::Trig::StartMode::E trig_startMode;           ///< ����� �������.
    Osci::Settings::Trig::ModeFind::E  trig_modeFind;            ///< ����� ������������� - ������� ��� �������������.
    /// \todo ����������� trig_holdOff ������������
    int16                              trig_holdOff;             ///< ��������� �������������
    bool                               trig_holdOffEnabled;      ///< ��������� ��������� �������������

    // ���� ���¨����

    int                              time_shift;
    Osci::Settings::TBase::E         time_base;
    Osci::Settings::PeakDetMode::E   time_peakDet;
    Osci::Settings::TPos::E          time_TPos;
    Osci::Settings::SampleType::E    time_sampleType;
    Osci::Settings::FunctionTime::E  time_timeDivXPos;
    Osci::Settings::LinkingTShift::E time_linkingTShift;                 ///< ��� �������� �������� �� �����������
    Osci::Settings::SampleType::E    time_sampleTypeOld;

    // ���� �������

    bool                                     curs_showCursors;             ///< ���������� �� �������.
    Osci::Measurements::Cursors::LookMode::E curs_lookMode[2];             ///< ������ �������� �� ��������� ��� ���� ��� ��������.
    bool                                     curs_showFreq;                ///< ������������� � true ��������, ��� ����� ���������� �� ������ 1/dT ����� ���������.
    Osci::Measurements::Cursors::Active::E   curs_active;                  ///< ����� ������� ����� �������.
    Chan::E                                  curs_source;                  ///< �������� - � ������ ������ ��������� �������.
    Osci::Measurements::Cursors::Control::E  curs_cntrlU[Chan::Size];      ///< �������� ������� ����������.
    Osci::Measurements::Cursors::Control::E  curs_cntrlT[Chan::Size];      ///< �������� ������� �������.
    Osci::Measurements::Cursors::Movement::E curs_movement;                ///< ��� ������������ �������� - �� ������ ��� ���������.
    float                                    curs_deltaU100percents[2];    ///< ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float                                    curs_deltaT100percents[2];    ///< ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    float                                    curs_posCurU[Chan::Size][2];  ///< ������� ������� �������� ���������� ����� �������.
    float                                    curs_posCurT[Chan::Size][2];  ///< ������� ������� �������� ������� ����� �������.

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
