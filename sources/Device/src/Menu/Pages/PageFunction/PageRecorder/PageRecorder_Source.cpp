#include "defines.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Settings/Settings.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageSource;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cChanA,                                                                                                                    //--- ������� - ����������� - �������� - ����� 1 ---
    "����� 1", "Channl 1",
    "����� ������ 1 ��� ������ � ���������",
    "Select channel 1 for recording and viewing",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU,  ENABLE_EN,
    RECORDER_SOURCE_A, pageSource, FuncActive, Choice::FuncChange, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cChanB,                                                                                                                    //--- ������� - ����������� - �������� - ����� 2 ---
    "����� 2", "Channl 2",
    "����� ������ 2 ��� ������ � ���������",
    "Select channel 2 for recording and viewing",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU,  ENABLE_EN,
    RECORDER_SOURCE_B, pageSource, FuncActive, Choice::FuncChange, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cSensor,                                                                                                                    //--- ������� - ����������� - �������� - ������ ---
    "������", "Sensor",
    "����� ������� ��� ������ � ���������",
    "Sensor selection for recording and viewing",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU,  ENABLE_EN,
    RECORDER_SOURCE_SENSOR, pageSource, FuncActive, Choice::FuncChange, FuncDraw
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_3( pageSource, // -V641 // -V1027                                                                                                         //--- ������� - ����������� - �������� ---
    "��������", "SOURCE",
    "����� ������������ ��������",
    "Selection of recorded signals",
    &cChanA,        ///< ������� - ����������� - �������� - ����� 1
    &cChanB,        ///< ������� - ����������� - �������� - ����� 2
    &cSensor,       ///< ������� - ����������� - �������� - ������
    Page::Name::Function_Recorder_Source, PageFunction::PageRecorder::pointer, FuncActive, FuncPressPage, FuncDrawPage, FuncRegSetPage
)

const PageBase *PageFunction::PageRecorder::PageSource::pointer = &pageSource;
