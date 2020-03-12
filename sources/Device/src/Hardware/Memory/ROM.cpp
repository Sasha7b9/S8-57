#include "defines.h"
#include "Hardware/Memory/ROM.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Memory/Sector.h"
#include <cstring>


#define READ_BYTE(address)  (*((uint8 *)address))
#define SIZE_RECORD         512                      // ������ ����� ������


class Record;

struct SectorSet
{
    // ���������� ����� ������ ������ (����������, ������ �������)
    Record *FirstRecord();

    // ���������� ��������� �� ��������� ������ � ����������
    Record *LastSaved();

    // ���������� ��������� �� ��������� � record ������ ������ (�����, � ������� ����� �������� ���������). ���� ������� �� �������, ���������� nullptr
    Record *NextFree(Record *record);

    // ���������� ����� ������ ��������� ��� ���������� ������
    Record *FirstFree();

    // ���������� true, ���� ������ record ����������� ����� �������
    bool Belong(Record *record);

    Sector sector;
};


static SectorSet sectorFirst = { Sector::Get(Sector::_10_SETTINGS_1) };
static SectorSet sectorSecond = { Sector::Get(Sector::_11_SETTINGS_2) };


/*
    � ������ ������� ����������� (128 * 1024 / SIZE_RECORD) �������
*/

class Record
{
public:

    // ���������� ��������� �� ��������� ������ ������ (������, � ������� ����� ��������� ���������)
    Record *NextFree();

    // ���������� ��������� �� ��������� ������
    Record *Next();

    // ���������� true, ���� ������ �������� (� �� ��� ������ �� ���������, ������ ����� 0xFFFFFFFF)
    bool IsFree();

    // ������� ������. ��������� ������ ������. ��� ����� ������ � ������������ �������� (� ����, � ������� �� ��������� ����������� �����)
    void Erase();

    // ���������� true, ���� ����� ���������. ��� ���������� � �������� ������� :
    // 1 - ������ ����� (������ �����  0xFFFFFFFF)
    // 2 - ������ ����� (������ ����� 0x00000000)
    // 3 - ������ ������ ��������� � ����������� ����� ���������
    bool IsCorrect();

    // ���������� true, ���� � ������ ���-�� �������� (������ ����� �� ����� 0xFFFFFFFF � 0x00000000). ��� ����� ����������� ����
    bool IsSaved();

    // ���������� ������, �������� ����������� ������ ������
    SectorSet *GetSector();

    // ���������� ��������� �� ������ ������
    SectorSet *GetAnotherSector();

    Settings set;
};


// ���������� ��������� �� ��������� ����������� ������
static Record *LastSaved();


void ROM::Settings::Save()
{
    Record *record = nullptr;

    Record *lastSaved = LastSaved();

    if(lastSaved)
    {
        record = lastSaved->GetSector()->FirstFree();

        if(!record)
        {
            SectorSet *sector = record->GetAnotherSector();

            record = sector->FirstFree();

            if(!record)
            {
                sector->sector.Erase();

                record = sector->FirstFree();
            }
        }
    }
    else
    {
        record = sectorFirst.FirstFree();
    }

    set.number = record->set.number + 1;                // ���� ������ ������, �� ����� ����� ����� 0 = 0xFFFFFFFF + 1
    set.crc32 = set.CalcWriteCRC32();
    HAL_ROM::WriteBufferBytes(reinterpret_cast<uint>(record), &set, sizeof(set));
}


bool ROM::Settings::Load()
{
    Record *record = LastSaved();

    while(record && !record->IsCorrect())
    {
        record->Erase();
        record = LastSaved();
    }

    if(record)
    {
        std::memcpy(&set, &record->set, sizeof(record->set));
    }

    return (record != nullptr);
}


String OTP::GetSerialNumber(int *freeForWrite)
{
    char buffer[20];
    *freeForWrite = HAL_OTP::GetSerialNumber(buffer);
    return String(buffer);
}


bool OTP::SaveSerialNumber(char *servialNumber)
{
    return HAL_OTP::SaveSerialNumber(servialNumber);
}


static Record *LastSaved()
{
    Record *saved1 = sectorFirst.LastSaved();
    Record *saved2 = sectorFirst.LastSaved();

    if (saved1 && saved2)
    {
        return (saved1->set.number > saved2->set.number) ? saved1 : saved2;
    }

    if (!saved1 && !saved2)
    {
        return nullptr;
    }

    if (!saved2)
    {
        return saved1;
    }

    return saved2;
}


Record *Record::NextFree()
{
    return GetSector()->NextFree(this);
}


Record *Record::Next()
{
    return (this + 1);
}


bool Record::IsFree()
{
    return (set.crc32 == 0xFFFFFFFF);
}


SectorSet *Record::GetSector()
{
    if(sectorFirst.Belong(this))
    {
        return &sectorFirst;
    }

    if(sectorSecond.Belong(this))
    {
        return &sectorSecond;
    }

    return nullptr;
}


SectorSet *Record::GetAnotherSector()
{
    if(sectorFirst.Belong(this))
    {
        return &sectorSecond;
    }

    if(sectorSecond.Belong(this))
    {
        return &sectorFirst;
    }

    return nullptr;
}


bool Record::IsSaved()
{
    return (set.crc32 != 0xFFFFFFFF) && (set.crc32 != 0x00000000);
}


bool Record::IsCorrect()
{
    return (set.crc32 == 0xFFFFFFFF) ||
        (set.crc32 == 0x00000000) ||
        set.crc32 == set.CalcWriteCRC32();
}


void Record::Erase()
{
    HAL_ROM::Fill(reinterpret_cast<uint>(this), 0, SIZE_RECORD);
}


Record *SectorSet::FirstRecord()
{
    return reinterpret_cast<Record *>(&sector);
}


bool SectorSet::Belong(Record *record)
{
    uint addressRecord = reinterpret_cast<uint>(record);

    return addressRecord >= sector.address && addressRecord < sector.End();
}


Record *SectorSet::NextFree(Record *record)
{
    record = record->Next();

    while(Belong(record))
    {
        if(record->IsFree())
        {
            return record;
        }
        record = record->Next();
    }

    return nullptr;
}


Record *SectorSet::LastSaved()
{
    Record *result = nullptr;

    Record *record = FirstRecord();

    while(Belong(record))
    {
        if(record->IsSaved())
        {
            if(record->IsCorrect())
            {
                if(result == nullptr)
                {
                    result = record;
                }
                else
                {
                    if(record->set.number > result->set.number)
                    {
                        result = record;
                    }
                }
            }
            else
            {
                record->Erase();
            }
        }

        record = record->Next();
    }

    return result;
}


Record *SectorSet::FirstFree()
{
    Record *record = FirstRecord();

    while(Belong(record))
    {
        if(record->IsFree())
        {
            return record;
        }

        record = record->Next();
    }

    return nullptr;
}
