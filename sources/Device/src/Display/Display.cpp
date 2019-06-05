#include "defines.h"
#include "log.h"
#include "device.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "Display/Display_Primitives.h"
#include "Hardware/Timer.h"
#include "Hardware/Beeper.h"
#include "Recorder/Recorder_Display.h"
#include <cstring>

#include "Osci/Display/Osci_Display.h"
#include "Osci/Display/PainterData.h"
#include "Multimeter/Multimeter.h"
#include "Utils/Debug.h"


using namespace Display::Primitives;
using namespace Osci::Settings;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NEED_SET_ORIENTATION    (bf.needSetOrientation)

#define NU {0, 0}

static struct StructWarning
{
    Warning             warning;
    bool                good;
    uint8               notUsed[2];
    const char * const  message[3];
}
warns[Warning::Number] =
{
    {Warning::LimitChan1_Volts, false, NU,           {"������ ����� 1 - �����/���"}},
    {Warning::LimitChan2_Volts, false, NU,           {"������ ����� 2 - �����/���"}},
    {Warning::LimitSweep_Time, false, NU,            {"������ ��������� - �����/���"}},
    {Warning::EnabledPeakDet, false, NU,             {"������� ������� ��������"}},
    {Warning::LimitChan1_RShift, false, NU,          {"������ ����� 1 - \x0d"}},
    {Warning::LimitChan2_RShift, false, NU,          {"������ ����� 2 - \x0d"}},
    {Warning::LimitSweep_Level, false, NU,           {"������ ��������� - �������"}},
    {Warning::LimitSweep_TShift, false, NU,          {"������ ��������� - \x97"}},
    {Warning::TooSmallSweepForPeakDet, false, NU,    {"���. ���. �� �������� �� ���������� ����� 0.5���/���"}},
    {Warning::TooFastScanForRecorder, false, NU,     {"��������� �� ����� �������� �� ������� ���¨�����"}},
    {Warning::FileIsSaved, true, NU,                 {"���� ��������"}},
    {Warning::SignalIsSaved, true, NU,               {"������ ��������"}},
    {Warning::SignalIsDeleted, true, NU,             {"������ ������"}},
    {Warning::MenuDebugEnabled, true, NU,            {"���� ������� ��������"}},
    {Warning::TimeNotSet, true, NU,                  {"����� �� �����������. ������ ���������� ��� ������"}},
    {Warning::SignalNotFound, true, NU,              {"������ �� ������"}},
    {Warning::SetTPosToLeft, true, NU,               {  "�� ���������� ��������� 10��/��� ���������� �������-",
                                                        "������ \"��������� - \x7b\" � ��������� \"����\" ��� ������-", 
                                                        "��� ������ �������"}},
    {Warning::NeedRebootDevice, true, NU,               {"��� ���������� ��������� � ����", 
                                                         "��������� ������"}},
    {Warning::ImpossibleEnableMathFunction, true, NU,   {"��������� ���������� ���"}},
    {Warning::ImpossibleEnableFFT, true, NU,            {"��������� �������������� �������"}},
    {Warning::WrongFileSystem, false, NU,               {"�� ���� ��������� ������. ���������, ��� �� ��� FAT32"}},
    {Warning::WrongModePeackDet, true, NU,              {"����� �������� ����� ������, ��������� ������� ��������"}},
    {Warning::DisableChannelB, true, NU,                {"������� ��������� ����� 2"}},
    {Warning::TooLongMemory, true, NU,                  {"������ ����� ��������� ��� ����� ������ 16� � �����"}},
    {Warning::NoPeakDet32k, true, NU,                   {"������� �������� �� �������� ��� ����� ������ 32�"}},
    {Warning::NoPeakDet16k, true, NU,                   {"��� ������ �������� ��������� ��� ����� ������ 16�", 
                                                         "��������� ����� 2"}},
    {Warning::Warn50Ohms, false, NU,                    {"��� �������� �������� ������������� 50 ��", 
                                                         "����������� �������� �� ���� ����� 5 �"}},
    {Warning::WarnNeedForFlashDrive, true, NU,          {"������� ���������� ����-����"}},
    {Warning::FirmwareSaved, true, NU,                  {"�������� ���������"}},
    {Warning::FullyCompletedOTP, false, NU,             {"������ OTP ��������� ���������"}}
};

#define NUM_WARNINGS    10
static const char       *warnings[NUM_WARNINGS] = {0};      ///< ����� ��������������� ���������.
static uint             timeWarnings[NUM_WARNINGS] = {0};   ///< ����� �����, ����� ��������������� ��������� ��������� �� �����.


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
volatile static bool drawRShiftMarkers = false;
static pFuncVV funcOnHand       = 0;
static uint timeStart = 0;
static const char *textWait = 0;
static bool clearBackground = false;
/// �������������� ������� ���������. ����������� ����� ����������� ���������, �� ����� ������� EndScene;
volatile static pFuncVV funcAdditionDraw = EmptyFuncVV;
/// true ��������, ��� ���������� ������� ���������
static bool inStateDraw = false;

static pFuncVV funcAfterUpdateOnce = EmptyFuncVV;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� �������, ����������� ��� ���������� ����� ���������
static void ExecuteFuncAfterUpdateOnce();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Display::Init()
{
    for(uint8 i = 0; i < Color::NUMBER.value; i++)
    {
        Color(i).SetValue(COLOR(i));
    }

    Painter::Init();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Update()
{
    DEBUG_POINT;

    uint startTime = TIME_MS;

    inStateDraw = true;

    DEF_STRUCT(StructDraw, pFuncVV) funcs[Device::Mode::Size] =
    {
        Osci::Display::Update,
        Tester::Display::Update,
        Multimeter::Display::Update,
        Recorder::Display::Update
    };

    DEBUG_POINT;

    HANDLER_CHOICE_AND_SAFE_RUN(pFuncVV, Device::State::CurrentMode());

    DEBUG_POINT;

    Console::Draw();

    DEBUG_POINT;

    funcAdditionDraw();

    DEBUG_POINT;

    Painter::EndScene();

    DEBUG_POINT;

    inStateDraw = false;

    DEBUG_POINT;

    ExecuteFuncAfterUpdateOnce();

    DEBUG_POINT;

    LOG_WRITE("%d ms", TIME_MS - startTime);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Display::InProcess()
{
    return inStateDraw;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void ExecuteFuncAfterUpdateOnce()
{
    funcAfterUpdateOnce();
    funcAfterUpdateOnce = EmptyFuncVV;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetFuncAfterUpadteOnce(pFuncVV func)
{
    funcAfterUpdateOnce = func;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnTimerShowWarning()
{
    uint time = TIME_MS;
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if (time - timeWarnings[i] > (uint)TIME_MESSAGES * 1000)
        {
            timeWarnings[i] = 0;
            warnings[i] = 0;
        }
    }

    int pointer = 0;
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if (warnings[i] != 0)
        {
            warnings[pointer] = warnings[i];
            timeWarnings[pointer] = timeWarnings[i];
            if (pointer != i)
            {
                timeWarnings[i] = 0;
                warnings[i] = 0;
            }
            pointer++;
        }
    }

    if (pointer == 0)
    {
        Timer::Disable(Timer::Type::ShowMessages);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void ShowWarn(const char *message)
{
    if (warnings[0] == 0)
    {
        Timer::SetAndEnable(Timer::Type::ShowMessages, OnTimerShowWarning, 100);
    }
    bool alreadyStored = false;

    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if (warnings[i] == 0 && !alreadyStored)
        {
            warnings[i] = message;
            timeWarnings[i] = TIME_MS;
            alreadyStored = true;
        }
        else if (warnings[i] == message)
        {
            timeWarnings[i] = TIME_MS;
            return;
        }
        else
        {
            // ������ ������ �� ����
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::ShowWarning(Warning::E warning)
{
    Color::ResetFlash();
    for (int i = 2; i >= 0; i--)
    {
        const char *message = warns[warning].message[i];
        if (message)
        {
            ShowWarn(message);
        }
    }
    if (warns[warning].good)
    {
        Beeper::WarnBeepGood();
    }
    else
    {
        Beeper::WarnBeepBad();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnRShiftMarkersAutoHide()
{
    drawRShiftMarkers = false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::ChangedRShiftMarkers(bool /*active*/)
{
    drawRShiftMarkers = !ALT_MARKERS_HIDE;
    Timer::SetAndStartOnce(Timer::Type::RShiftMarkersAutoHide, OnRShiftMarkersAutoHide, 5000);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetDrawMode(DrawMode::E mode, pFuncVV func)
{
    funcOnHand = func;
    if (mode == DrawMode::Hand)
    {
        Timer::SetAndEnable(Timer::Type::Display, funcOnHand, 40);
    }
    else
    {
        Timer::Disable(Timer::Type::Display);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::FuncOnWaitStop()
{
    Display::SetDrawMode(DrawMode::Auto, 0);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void FuncOnWait()
{
    if (clearBackground)
    {
        Painter::BeginScene(Color::BACK);
    }

    uint time = ((TIME_MS - timeStart) / 50) % 100;

    if (time > 50)
    {
        time = (100 - time);
    }

    int width = 200;
    int height = 80;
    int x = 160 - width / 2;
    int y = 120 - height / 2;

    Region(width, height).Fill(x, y, Color::BACK);
    Rectangle(width, height).Draw(x, y, Color::FILL);

    Text(textWait).DrawInCenterRect(x, y, width, height - 20);

    char buf[100];
    buf[0] = 0;

    for (uint i = 0; i < time; i++)
    {
        std::strcat(buf, "."); //-V2513
    }

    Text(buf).DrawInCenterRect(x, y + 20, width, height - 20);

    Painter::EndScene();
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::FuncOnWaitStart(const char *text, bool eraseBackground)
{
    timeStart = TIME_MS;
    textWait = text;
    clearBackground = eraseBackground;
    Display::SetDrawMode(DrawMode::Hand, FuncOnWait);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::RemoveAddDrawFunction()
{
    funcAdditionDraw = EmptyFuncVV;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetOrientation(Orientation::E orientation)
{
    DISPLAY_ORIENTATION = orientation;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetAddDrawFunction(pFuncVV func, uint time)
{
    funcAdditionDraw = func;
    Timer::SetAndStartOnce(Timer::Type::RemoveAddFunction, RemoveAddDrawFunction, time);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Display::TimeMenuAutoHide()
{
    static const int times[] =
    {
        0, 5, 10, 15, 30, 60
    };
    return times[MENU_AUTO_HIDE] * 1000;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Display::IsSeparate()
{
    return (FUNC_MODE_DRAW_IS_SEPARATE || FFT_ENABLED);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Display::ENumSignalsInSec::TimeBetweenFramesMS() const
{
    static const uint time[] = { 40, 100, 200, 500, 1000 };

    return time[value];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Display::ENumSmoothing::ToNumber() const
{
    return (uint)value + 1U;
}
