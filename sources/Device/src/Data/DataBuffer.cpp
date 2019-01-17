#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "DataBuffer.h"
#include "DataSettings.h"
#include <cstring>
#include <climits>

#include "Data/Heap.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������������� ����� ��� �������� ������ � �������� DataSettings
class Stack
{
public:

    static uint Size();
    /// � ����������� ��������� ����� ������� �������� � ���������� ���������
    static void Clear();

    static void Push(DataSettings *ds);

    static DataSettings *Top();
};

/// ������������ ����� ����������� �������� - ���������� ����� ����� 512, ������� ��������� ��������, ������� ������ ���� �����
#define MAX_DATAS 150

/// \todo ��� ������ ����� ��������� � backup SRAM
/// �������� �������� �� ������ ������� � ������ �������� ������ �� �������.
/// ��������� ����, ��� ������� ������, �������� ��������� ���� ������ ������ ���� �������� (��������� �� ������ ����� ������� ����� ����)
static DataSettings settings[MAX_DATAS];
/// �� ����� ������� �������� ��������� ������ � settings. -1 - ����� �� ���������
static int lastIndex = -1;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������ ������� ������� �������� � settings
static int Stack_FindFirstEmptyElement();
/// ���������� ����� � ������, ���� ����� �������� ������. ���� 0, �� ����� ��� ������ ���
static uint8 *Stack_AddressToPlace(const DataSettings *ds);
/// ������� ����� ������ ������ 
static void Stack_RemoveFirst();
/// ���������� � ����� ����� ������
static void Stack_AddToEnd(DataSettings *ds, uint8 *address);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DataBuffer::Init()
{
    Stack::Clear();

    uint8 *buffer = (uint8 *)Heap::Data();

    for(uint i = 0; i < Heap::Size(); i++)
    {
        buffer[i] = (uint8)i;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint DataBuffer::Size()
{
    return Stack::Size();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Stack::Clear()
{
    std::memset(settings, 0, sizeof(DataSettings) * MAX_DATAS);
    for (int i = 0; i < MAX_DATAS; i++)
    {
        settings[i].Erase();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Stack::Push(DataSettings *ds)
{
    uint8 *address = Stack_AddressToPlace(ds);  // ������� ����� ��� ������ ������

    if(address == 0)                            // ���� ��� ����� ��� ���������� ����� ������
    {
        Stack_RemoveFirst();                    // �� ������� ����� ������ ������
        address = Stack_AddressToPlace(ds);
    }

    Stack_AddToEnd(ds, address);                // � ��������� � ����� ����� ������
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataSettings *Stack::Top()
{
    if (lastIndex == -1)
    {
        return 0;
    }
    return &settings[lastIndex];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Stack::Size()
{
    uint result = 0U;

    for (int i = 0; i < MAX_DATAS; i++)
    {
        if (settings[i].IsExist())
        {
            result++;
        }
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint8 *Stack_AddressToPlace(const DataSettings *_ds)
{
    // � ���� ������� �������� true, ���� ������� ������ ��������
    bool freeData[MAX_DATAS];

    // ������ ��� ������� "����������"
    for(int i = 0; i < MAX_DATAS; i++)
    {
        freeData[i] = true;
    }

    uint8 *buffer = (uint8 *)Heap::Data();

    // ������ ����� �� "��������"
    for(int i = 0; i < MAX_DATAS; i++)
    {
        DataSettings *ds = &settings[i];

        if(ds->IsExist() &&                 // ���� ������ ����� �����
            !ds->IsEmpty())             // � � �������
        {
            int size = _ds->SizeData();                     // ������ ������ "�����" � ������ ������

            uint8 *addressFirst = &buffer[0];               // ����� ���������� "�����" ������
            uint8 *address = ds->Data();                    // ����� ���������� "�����" ������

            uint index = (uint)(address - addressFirst) / (uint)size;    // ������� "������" ������ ��������� ��������� � �������   // -V202

            freeData[index] = false;                        // ������������� ������� ����, ��� ������ ���� �����
        }
    }

    // ������ ������� ������ ��������� ���� ������
    int index = 0;
    for(; index < MAX_DATAS; index++)
    {
        if(freeData[index])
        {
            break;
        }
    }

    uint8 *address = &buffer[0] + index * _ds->SizeData();          // ������� ����� ������� ���������� ����� ������

    return (&buffer[Heap::Size()] - address) >= _ds->SizeData() ? address : 0;   // -V104
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Stack_RemoveFirst()
{
    // ������ ������� ��� �������� ����� �� ����
    std::memcpy(&settings[0], &settings[1], sizeof(DataSettings) * (MAX_DATAS - 1));

    // � �������� ��������� ������� � �������
    std::memset(&settings[MAX_DATAS - 1], 0, sizeof(DataSettings));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Stack_AddToEnd(DataSettings *ds, uint8 *address)
{
    int index = Stack_FindFirstEmptyElement();

    settings[index] = *ds;
    
    lastIndex = index;

    if(ds->DataA())
    {
        std::memcpy(address, ds->DataA(), (uint)ds->SizeChannel());
        settings[index].dataA = address;
        address += ds->SizeChannel();   // -V102
    }
    if(ds->DataB())
    {
        std::memcpy(address, ds->DataB(), (uint)ds->SizeChannel());
        settings[index].dataB = address;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static int Stack_FindFirstEmptyElement() // -V2506
{
    for (int i = 0; i < MAX_DATAS; i++)
    {
        DataSettings *ds = &settings[i];
        if (!ds->IsExist() || ds->IsEmpty())
        {
            return i;
        }
    }

    return INT_MAX;
}
