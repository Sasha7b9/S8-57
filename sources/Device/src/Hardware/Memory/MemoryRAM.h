#pragma once


struct DataSettings;


struct MemoryRAM
{
    /// ����� �������� � ����� �������. 0 - ��������� ��������� ������, 1 - ������������� ��������� ������.
    static int16 currentSignal;
    /// �������� ����� ��������� ������
    static void Save(const DataSettings *ds);
    /// ������� ���������� � num � ����� ����������� ������. 0 - ��������� ������, 1 - �������������
    static bool Read(DataSettings **ds, uint num = 0);
    /// ���������� ���������� ������� � ������
    static uint NumberDatas();
};
