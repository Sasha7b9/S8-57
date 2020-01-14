#include "defines.h"
#include "device.h"
#include "common/Decoder_d.h"
#include "Display/Console.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/FPGA.h"
#include "Hardware/Battery.h"
#include "Hardware/Beeper.h"
#include "Hardware/Timer.h"
#include "Hardware/VCP.h"
#include "Hardware/HAL/HAL.h"
#include "Keyboard/BufferButtons.h"
#include "Menu/MenuItems.h"
#include "Recorder/Recorder.h"
#include "SCPI/SCPI.h"
#include <cstdlib>


/// ��������� ���������� � ������������ � ������������� �������
static void SetCurrentMode();
/// ���������� ����� ������ mode, ���� ������� �������� page ��� � ����� ������� �������� �������� ���� page
static bool SetCurrentMode(const Page *page, Device::Mode::E mode);

static Device::Mode::E currentMode = Device::Mode::Osci;



void Device::Init()
{
    HAL::Init();

    Console::Init();

    Timer::Init();
    
    PAUSE_ON_MS(500);

    Beeper::Init();

    Battery::Init();

    HAL_RTC::Init();

    VCP::Init();

    Tester::Init();

    FPGA::Init();

    Settings::Load();

    Display::Init();

    FreqMeter::Init();

    Osci::Init();

    Menu::Init();

    Multimeter::Init();

    FDrive::Init();

    SetCurrentMode();
}


void SetCurrentMode()
{
    if (!SetCurrentMode(PageMultimeter::self, Device::Mode::Multimeter))
    {
        if (!SetCurrentMode(PageTester::self, Device::Mode::Tester))
        {
            if (!SetCurrentMode(PageRecorder::self, Device::Mode::Recorder))
            {
                Device::SetMode(Device::Mode::Osci);
            }
        }
    }
}


bool SetCurrentMode(const Page *page, Device::Mode::E mode)
{
    Item *opened = Menu::OpenedItem();

    if (opened && 
        (opened == const_cast<Page *>(page) || opened->ExistKeeper(page)))
    {
        Device::SetMode(mode);
        return true;
    }

    return false;
}


void Device::Update()
{
    START_MULTI_MEASUREMENT();

    Osci::Update();
    
    Display::Update();

    Menu::SaveSettings();

    Recorder::Update();

    Tester::Update();

    Multimeter::Update();

    Menu::Update();

    FDrive::Update();

    while (HAL_FSMC::Receive()) {};

    SCPI::Update();

    DDecoder::Update();
}


Device::Mode::E Device::CurrentMode()
{
    return currentMode;
}


void Device::SetMode(Mode::E mode)
{
    if (mode != currentMode)
    {
        currentMode = mode;

        Osci::DeInit();
        Tester::Disable();
        Multimeter::DeInit();
        Recorder::DeInit();

        if (InModeOsci())
        {
            Keyboard::Unlock();
            Osci::Init();
        }
        else if (InModeTester())
        {
            static const Key::E keys[] =
            {
                Key::RangeMoreA, Key::RangeLessA, Key::RShiftMoreA, Key::RShiftLessA,
                Key::RangeMoreB, Key::RangeLessB, Key::RShiftMoreB, Key::RShiftLessB,
                Key::F1, Key::F2, Key::F3, Key::F4, Key::F5,
                Key::Left, Key::Right, Key::Up, Key::Down,
                Key::Start, Key::Enter, Key::None
            };

            Keyboard::Lock(keys);
            Tester::Init();
            Tester::Enable();
        }
        else if (InModeMultimeter())
        {
            static const Key::E keys[] =
            {
                Key::F1, Key::F2, Key::F3, Key::F4, Key::F5,
                Key::Left, Key::Right, Key::Up, Key::Down,
                Key::Enter, Key::None
            };

            Keyboard::Lock(keys);
            Multimeter::Init();
        }
        else if (InModeRecorder())
        {
            Keyboard::Unlock();
            Recorder::Init();
        }
        else
        {
            // ����� ������ ���� - ��� �������� ���������
        }
    }
}


bool Device::InModeTester()
{
    return (CurrentMode() == Device::Mode::Tester);
}


bool Device::InModeMultimeter()
{
    return (CurrentMode() == Device::Mode::Multimeter);
}


bool Device::InModeOsci()
{
    return (CurrentMode() == Device::Mode::Osci);
}


bool Device::InModeRecorder()
{
    return (CurrentMode() == Device::Mode::Recorder);
}


void Device::Reset()
{
    HAL_NVIC::SystemReset();
}
