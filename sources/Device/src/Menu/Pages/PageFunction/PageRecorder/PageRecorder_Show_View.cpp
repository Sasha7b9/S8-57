#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Recorder/Recorder.h"
#include "Settings/Settings.h"


extern const PageBase pageView;

const Page * const PageRecorder::PageShow::PageView::self = (const Page *)&pageView;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cMove,                                                                                                      //--- ������� - ����������� - �������� - �������� - ����������� ---
    "�����������",
    "",
    "X",
    "Y",
    RECORDER_AXIS_MOVE, &PageRecorder::PageShow::PageView::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cZoom,                                                                                                          //--- ������� - ����������� - �������� - �������� - ������� ---
    "�������",
    "",
    "X",
    "Y",
    RECORDER_AXIS_ZOOM, &PageRecorder::PageShow::PageView::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Less()
{

}

DEF_BUTTON( bLess,                                                                                                             //--- ������� - ����������� - �������� - �������� - ������ ---
    "������",
    "",
    &PageRecorder::PageShow::PageView::self, 0, OnPress_Less, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_More()
{

}

DEF_BUTTON( bMore,                                                                                                             //--- ������� - ����������� - �������� - �������� - ������ ---
    "������",
    "",
    &PageRecorder::PageShow::PageView::self, 0, OnPress_More, 0
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_5( pageView, // -V641 // -V1027                                                                                                //--- ������� - ����������� - �������� - �������� ---
    "��������",
    "",
    &cMove,                                                                 ///< ������� - ����������� - �������� - �������� - �����������
    &cZoom,                                                                 ///< ������� - ����������� - �������� - �������� - �������
    &bLess,                                                                 ///< ������� - ����������� - �������� - �������� - ������
    &bMore,                                                                 ///< ������� - ����������� - �������� - �������� - ������
    PageRecorder::PageShow::PageView::PageCursors::self,      ///< ������� - ����������� - �������� - �������� - �������
    Page::Name::Function_Recorder_Show_View, &PageRecorder::PageShow::self, 0, 0, 0, 0
)
