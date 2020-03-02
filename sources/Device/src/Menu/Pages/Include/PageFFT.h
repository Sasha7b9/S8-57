#pragma once


struct ScaleFFT
{
    enum E
    {
        Log,           ///< ��� �������� �������� ��������������� ����� ������ �������.
        Linear         ///< ��� �������� �������� �������� ����� ������ �������.
    };
    static ScaleFFT::E &Ref();
    static bool IsLog() { return Ref() == Log; }
};

struct SourceFFT
{
    enum E
    {
        A,
        B,
        Both
    };
    static SourceFFT::E &Ref();
    static bool IsA() { return Ref() == A; }
    static bool IsB() { return Ref() == B; }
};

struct WindowFFT
{
    enum E
    {
        Rectangle,
        Hamming,
        Blackman,
        Hann
    };
    static WindowFFT::E &Ref();
    static bool IsHamming()  { return Ref() == Hamming; }
    static bool IsBlackman() { return Ref() == Blackman; }
    static bool IsHann()     { return Ref() == Hann; }
};

struct MaxDBFFT
{
    enum E
    {
        _40,
        _60,
        _80
    };
    MaxDBFFT() {}
    static MaxDBFFT::E &Ref();
    operator MaxDBFFT::E() { return Ref(); }

    static float MaxDBforFFT(MaxDBFFT::E maxDB)
    {
        static const float arrayMAX_DB_FOR_FFT[] = { -40.0F, -60.0F, -80.0F };

        return arrayMAX_DB_FOR_FFT[maxDB];
    }
};


struct SettingsFFT
{ //-V802
    bool            enabled;
    uint8           posCur[2];      ///< ������� ������� �������. ���������� 0...256.
    ScaleFFT::E     scale;
    SourceFFT::E    source;
    WindowFFT::E    window;
    MaxDBFFT::E     maxDB;
    uint8           cursor;         ///< ����������, ����� �������� ������� ��������� ����� ���������.
};


struct PageFFT
{
    static const Page *const self;

    struct Cursors
    {
        static const Page *const self;
    };
};
