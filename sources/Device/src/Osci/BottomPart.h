#pragma once
#include "Settings/SettingsChannel.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ����� �������� �� ����� ���������� � ������ ���� ������� ������
class BottomPart
{
public:
    static void Draw();
    /// �������� ��������� ������������� ������ ��������� ������
    static void WriteTextVoltage(Chan::E ch, int x, int y);

private:
    static int WriteChannel(Chan::E ch, int x, int y);

    static void WriteTBase(int x, int y);

    static void WriteStringAndNumber(const char *text, int16 x, int16 y, int number);

    static void DrawTime(int x, int y);
};

