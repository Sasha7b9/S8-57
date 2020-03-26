#pragma once
#include "Osci/ParametersOsci.h"


class IntRAM
{
public:
    // ��������� �� 16k ���� ������, ��������������� ��� ������ �����������
    static uint16 *Averager16k(Chan::E ch);

    // ������ ��� ������ ������ � ������ �������������
    static uint8 *_DataRand(Chan::E ch);

    // ��������� �� ������ ����������� ������
    static DataSettings *PrepareForP2P();
};
