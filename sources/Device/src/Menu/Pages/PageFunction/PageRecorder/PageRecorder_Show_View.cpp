#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Recorder/Recorder.h"
#include "Settings/Settings.h"


extern const PageBase pageView;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cMove,                                                                                                      //--- ������� - ����������� - �������� - �������� - ����������� ---
    "�����������",
    "",
    "X",
    "Y",
    RECORDER_AXIS_MOVE, pageView, 0, Choice::FuncChange, Choice::FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cZoom,                                                                                                          //--- ������� - ����������� - �������� - �������� - ������� ---
    "�������",
    "",
    "X",
    "Y",
    RECORDER_AXIS_ZOOM, pageView, 0, Choice::FuncChange, Choice::FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Less()
{

}

DEF_BUTTON( bLess,                                                                                                             //--- ������� - ����������� - �������� - �������� - ������ ---
    "������",
    "",
    pageView, Button::FuncActive, OnPress_Less, Button::EmptyDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_More()
{

}

DEF_BUTTON( bMore,                                                                                                             //--- ������� - ����������� - �������� - �������� - ������ ---
    "������",
    "",
    pageView, Button::FuncActive, OnPress_More, Button::EmptyDraw
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_5( pageView, // -V641 // -V1027                                                                                                //--- ������� - ����������� - �������� - �������� ---
    "��������",
    "",
    &cMove,                                                                 ///< ������� - ����������� - �������� - �������� - �����������
    &cZoom,                                                                 ///< ������� - ����������� - �������� - �������� - �������
    &bLess,                                                                 ///< ������� - ����������� - �������� - �������� - ������
    &bMore,                                                                 ///< ������� - ����������� - �������� - �������� - ������
    PageFunction::PageRecorder::PageShow::PageView::PageCursors::pointer,   ///< ������� - ����������� - �������� - �������� - �������
    Page::Name::Function_Recorder_Show_View, PageFunction::PageRecorder::PageShow::pointer, 0, Page::FuncPress, Page::FuncDraw, FuncRegSetPage
)


const PageBase *PageFunction::PageRecorder::PageShow::PageView::pointer = &pageView;
