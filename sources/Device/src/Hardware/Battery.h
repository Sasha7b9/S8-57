#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BAT_SHOW_ON_DISPLAY (Battery::ShowOnDisplay())


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Battery
{
    /// �������������
    void Init();

    void Draw();
    /// �������� �������� ����������
    float GetVoltage();
    /// �������� �� ���������� � ���������� �� �������
    bool &ShowOnDisplay();
}
