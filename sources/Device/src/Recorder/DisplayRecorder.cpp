#include "defines.h"
#include "log.h"
#include "Display/Grid.h"
#include "Display/Painter.h"
#include "Display/Primitives.h"
#include "Display/Warnings.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Menu/Menu.h"
#include "Menu/Pages/Include/PageRecorder.h"
#include "Recorder/DisplayRecorder.h"
#include "Recorder/StorageRecorder.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include "Utils/Values.h"
#include <cmath>
#include <cstring>



static Record *displayed = nullptr;             // ������� ������������ ������
static int startPoint = -1;                     // � ���� ����� ���������� �����
static int posCursor[2] = { 100, 220 };
static bool inProcessUpdate = false;            // true, ���� � ������ ������ ���������� ���������


DisplayRecorder::SpeedWindow DisplayRecorder::speed = DisplayRecorder::SpeedWindow::_1Window;


// ���������� ������������� ���������
static void DrawSettings(int x, int y);

// ���������� ������
static void DrawData();

// ���������� ������ ������, ������� � ����� start
static void DrawChannel(Chan::E ch);

// ���������� ������ �������
static void DrawSensor();

static void DrawMemoryWindow();

// ���������� �������� Y ������ ��� value �����
static int Y(int value);


static void DrawCursors();


static void DrawParametersCursors();


static char *TimeCursor(int numCur, char buffer[20]);


static char *VoltageCursor(Chan::E, int, char[20]);


static char *DeltaTime(char buffer[20]);

// ���������� ��������� �� ���������� � �������� �������� ������� (0, ���� ������ ��� ����������� �� ������)
static int *CurrentPosCursor();


// ������, ������� ����������, � ����� ��������� ������ ��������� �����������
struct RecordIcon
{
    static void Upate(int x, int y);
};


void DisplayRecorder::Update()
{
    Painter::BeginScene(Color::BLACK);

    Grid::Draw();

    inProcessUpdate = true;

    DrawData();

    inProcessUpdate = false;

    StorageRecorder::LastRecord()->AddMissingPoints();

    DrawSettings(289, 0);

    DrawCursors();

    DrawMemoryWindow();

    DFont::Set(DTypeFont::_8);

    Warnings::Draw();

    Menu::Draw();

    RecordIcon::Upate(5, 5);
}


static void DrawSettings(int x, int y)
{
    if (Menu::OpenedItem() == PageRecorder::Show::self)
    {
        return;
    }

    Region(30, 30).DrawBounded(x, y, Color::BACK, Color::FILL);

    Text(Recorder::ScaleX::ToString()).Draw(x + 2, y + 2);

    Text(Range::ToString(ChanA, S_DIVIDER_A)).Draw(x + 2, y + 11, Color::CHAN[ChanA]);

    Text(Range::ToString(ChanB, S_DIVIDER_B)).Draw(x + 2, y + 20, Color::CHAN[ChanB]);
}


static int Y(int value)
{
    int delta = VALUE::AVE - value;

    float scale = 120.0F / 125.0F;

    int y = 120 + static_cast<int>(delta * scale);

    if (y < 0)
    {
        y = 0;
    }
    if (y > 239)
    {
        y = 239;
    }

    return y;
}


static char *DeltaTime(char buffer[20])
{
    float delta = std::fabsf(static_cast<float>(posCursor[0] - posCursor[1])) * Recorder::ScaleX::TimeForPointMS() / 1000.0F;

    std::strcpy(buffer, Time(delta).ToString(false).c_str());

    return buffer;
}


static char *TimeCursor(int numCur, char buffer[20])
{
    PackedTime time = displayed->timeStart;

    time.AddTime((startPoint + posCursor[numCur]) * displayed->timeForPointMS);

    std::strcpy(buffer, time.ToString().c_str());

    return buffer;
}


static char *VoltageCursor(Chan::E, int, char [20])
{
//    uint numPoint = static_cast<uint>(startPoint + posCursor[numCur]);
//
//    Record *record = StorageRecorder::LastRecord();
//
//    Point16 *point = record->GetPoint(numPoint, record->NumPoints());
//
//    uint8 value = static_cast<uint8>((point.Min(ch) + point.Max(ch)) / 2);
//
//    float voltage = VALUE::ToVoltage(value, Range(ch), 0);
//
//    std::strcpy(buffer, Voltage(voltage).ToString(false).c_str());
//
//    return buffer;

    return nullptr;
}


static void DrawParametersCursors()
{
    int width = 49;

    int x = 319 - width;
    int y = 10;

    int x1 = x + 9;

    int y1 = y + 1;
    int y2 = y1 + 8;
    int y3 = y2 + 8;
    int y4 = y3 + 8;
    int y5 = y4 + 8;
    int y6 = y5 + 8;
    int y7 = y6 + 8;

    char buffer[20];

    Region(width, 58).DrawBounded(x, y, Color::BACK, Color::FILL);

    Text(String("1:%s", TimeCursor(0, buffer))).Draw(x + 2, y1, Color::FILL);

    Text(VoltageCursor(ChanA, 0, buffer)).Draw(x1, y2, Color::CHAN[ChanA]);

    Text(VoltageCursor(ChanB, 0, buffer)).Draw(x1, y3, Color::CHAN[ChanB]);

    Text(String("2:%s", TimeCursor(1, buffer))).Draw(x + 2, y4, Color::FILL);

    Text(VoltageCursor(ChanA, 1, buffer)).Draw(x1, y5, Color::CHAN[ChanA]);

    Text(VoltageCursor(ChanB, 1, buffer)).Draw(x1, y6, Color::CHAN[ChanB]);

    Text(String("dT %s", DeltaTime(buffer))).Draw(x + 2, y7, Color::FILL);
}

static void DrawCursors()
{
    if (Menu::OpenedItem() != PageRecorder::Show::self)
    {
        return;
    }

    DashedVLine cursor(239, 3, 1, 0);

    Color::FILL.SetAsCurrent();

    cursor.Draw(posCursor[0], 0);
    
    cursor.Draw(posCursor[1], 0);

    DrawParametersCursors();
}


static void DrawData()
{
    HAL_BUS_CONFIGURE_TO_FSMC();

    if(displayed->ContainsChannelA())
    {
        DrawChannel(ChanA);
    }

    if(displayed->ContainsChannelB())
    {
        DrawChannel(ChanB);
    }

    if(displayed->ContainsSensor())
    {
        DrawSensor();
    }
}


static void DrawChannel(Chan::E ch)
{
    int numPoints = displayed->NumPoints();

    if(numPoints == 0)
    {
        return;
    }

    typedef Point16 *(Record::*funcValue)(int);

    funcValue funcs[2] = { &Record::ValueA, &Record::ValueB };

    funcValue func = funcs[ch];

    int index = (numPoints < 320) ? 0 : (numPoints - 320);

    if (startPoint >= 0)
    {
        index = startPoint;
    }

    Point16 *point = (displayed->*func)(index);

    for(int x = 0; x < 320; x++)
    {
        if(!point->IsEmpty())
        {
            int min = Y(point->min);
            int max = Y(point->max);

            VLine(max - min).Draw(x, min, Color::CHAN[ch]);
        }

        HAL_BUS_CONFIGURE_TO_FSMC();

        point = point->Next(displayed);
    };
}


static void DrawSensor()
{

}


static void DrawMemoryWindow()
{
    static int prevNumPoints = 0;

    HAL_BUS_CONFIGURE_TO_FSMC();

    if (Menu::OpenedItem() != PageRecorder::Show::self || displayed->NumPoints() == 0)
    {
        return;
    }

    int numPoints = static_cast<int>(displayed->NumPoints());

    if (prevNumPoints != numPoints)
    {
        prevNumPoints = numPoints;
    }

    Region(319, 5).DrawBounded(0, 3, Color::BACK, Color::FILL);

    int width = static_cast<int>(320.0F / numPoints * 320.0F + 0.5F);

    if (width > 319)
    {
        width = 319;
    }

    int x = 0;

    if (numPoints > 320)
    {
        x = static_cast<int>(static_cast<float>(startPoint) / numPoints * 320.0F + 0.5F);
    }

    Region(width, 10).DrawBounded(x, 0, Color::BACK, Color::FILL);
}


void DisplayRecorder::MoveWindowLeft()
{
    HAL_BUS_CONFIGURE_TO_FSMC();

    if (displayed->NumPoints() < 321)
    {
        return;
    }

    startPoint -= speed.NumPoints();

    if (startPoint < 0)
    {
        startPoint = 0;
    }
}


void DisplayRecorder::MoveWindowRight()
{
    HAL_BUS_CONFIGURE_TO_FSMC();

    if (displayed->NumPoints() < 321)
    {
        return;
    }

    startPoint += speed.NumPoints();

    if (startPoint > static_cast<int>(displayed->NumPoints() - 320))
    {
        startPoint = static_cast<int>(displayed->NumPoints() - 320);
    }
}


void DisplayRecorder::MoveCursorLeft()
{
    Math::LimitationDecrease(CurrentPosCursor(), 0);
}


void DisplayRecorder::MoveCursorRight()
{
    Math::LimitationIncrease(CurrentPosCursor(), 319);
}


static int *CurrentPosCursor()
{
    static int nullPos;
    int *result = &nullPos;

    if (S_REC_CURSOR_IS_1)      { result = &posCursor[0]; }
    else if (S_REC_CURSOR_IS_2) { result = &posCursor[1]; }

    return result;
}


bool DisplayRecorder::InProcessUpdate()
{
    return inProcessUpdate;
}


void RecordIcon::Upate(int x, int y)
{
    if (Menu::OpenedItem() != PageRecorder::self)
    {
        return;
    }

    if (Recorder::InRecordingMode())
    {
        static uint timeStart = 0;              // ����� ������ ����� (������/�����)

        while (TIME_MS - timeStart >= 1000)
        {
            timeStart += 1000;
        }

        if (TIME_MS - timeStart <= 500)
        {
            Circle(6).Fill(x, y, Color::RED);
        }
    }
    else
    {
        Region(10, 10).Fill(x, y, Color::GREEN);
    }
}


void DisplayRecorder::SetDisplayedRecord(Record *record, bool forListening)
{
    HAL_BUS_CONFIGURE_TO_FSMC();

    displayed = record;

    if (forListening)
    {
        startPoint = -1;
    }
    else
    {
        startPoint = 0;

        if (displayed)
        {
            if (displayed->NumPoints() > 320)
            {
                startPoint = displayed->NumPoints() - 320;
            }
        }
    }
}


int DisplayRecorder::SpeedWindow::NumPoints() const
{
    static const int nums[3] = { 20, 320, 320 * 10 };

    return nums[value];
}
