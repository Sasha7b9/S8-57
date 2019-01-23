#pragma once


namespace Osci
{
    namespace Measurements
    {
        namespace Settings
        {
            //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            /// ������� �� ������� ��� ������ ���������.
            struct ModeViewSignals
            {
                enum E
                {
                    AsIs,       ///< ���������� ������� ��� ����.
                    Compress    ///< ������� ����� � ���������.
                } value;
                explicit ModeViewSignals(E v) : value(v) {};
            };
    
            //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            struct Source
            {
                enum E
                {
                    A,
                    B,
                    A_B
                } value;
                explicit Source(E v) : value(v) {};
            };
    
            //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            struct OnDisplay
            {
                enum E
                {
                    _1,      ///< 1 ��������� ����� �����.
                    _2,      ///< 2 ��������� ����� �����.
                    _1_5,    ///< 1 ������ � 5 �����������.
                    _2_5,    ///< 2 ������ �� 5 ���������.
                    _3_5,    ///< 3 ������ �� 5 ���������.
                    _6_1,    ///< 6 ����� �� 1 ���������.
                    _6_2     ///< 6 ����� �� 2 ���������.
                } value;
                explicit OnDisplay(E v) : value(v) {};
            };
        }
    }
}
