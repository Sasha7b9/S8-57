#include "defines.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Recorder/Recorder.h"
#include "Settings/Settings.h"
#include "Recorder/Recorder_Storage.h"
#include "Recorder/Recorder_Display.h"


extern const PageBase pageShow;

const Page * const PageFunction::PageRecorder::PageShow::self = (const Page *)&pageShow;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DEF_CHOICE_3( cSource,                                                                                                                  //--- ������� - ����������� - �������� - �������� ---
//    "��������",
//    "����� ������������ ������",
//    "���",
//    "USB-Flash",
//    "USB-PC",
//    RECORDER_STORAGE_PLAY, &PageFunction::PageRecorder::PageShow::self, 0, 0, 0
//)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cCursor,
    "������",
    "",
    "1",
    "2",
    Recorder::Settings::currentCursor, &PageFunction::PageRecorder::PageShow::self, 0, 0, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Next()
{
    Recorder::Display::MoveLeft();
}

DEF_BUTTON( bNext,                                                                                                                     //--- ������� - ����������� - �������� - ��������� ---
    "�����",
    "",
    &PageFunction::PageRecorder::PageShow::self, 0, OnPress_Next, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Prev()
{
    Recorder::Display::MoveRight();
}

DEF_BUTTON( bPrev,                                                                                                                    //--- ������� - ����������� - �������� - ���������� ---
    "������",
    "",
    &PageFunction::PageRecorder::PageShow::self, 0, OnPress_Prev, 0
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsActive_PageShow()
{
    return (Recorder::Storage::CurrentFrame()->NumPoints() != 0) && (!Recorder::IsRunning());
}

static bool FuncOnKey_PageShow(KeyEvent event)
{
    if (event.type == TypePress::Press || event.type == TypePress::Repeat)
    {
        if (event.key == Key::Left)
        {
            Recorder::Display::MoveCursorLeft();
            return true;
        }
        else if (event.key == Key::Right)
        {
            Recorder::Display::MoveCursorRight();
            return true;
        }
        else
        {
            // ����� ������ �� ����
        }
    }

    return false;
}

DEF_PAGE_3( pageShow, // -V641 // -V1027                                                                                                           //--- ������� - ����������� - �������� ---
    "��������",
    "�������� ���������� ������",
    //&cSource,                                                       ///< ������� - ����������� - �������� - ��������
    &bNext,                                                         ///< ������� - ����������� - �������� - ���������
    &bPrev,                                                         ///< ������� - ����������� - �������� - ����������
    &cCursor,
    //PageFunction::PageRecorder::PageShow::PageOperations::self,  ///< ������� - ����������� - �������� - ��������
    //PageFunction::PageRecorder::PageShow::PageView::self,        ///< ������� - ����������� - �������� - ��������
    Page::Name::Function_Recorder_Show, &PageFunction::PageRecorder::self, IsActive_PageShow, 0, 0, FuncOnKey_PageShow
)
