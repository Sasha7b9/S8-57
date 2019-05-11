#pragma once

/*
    ���������������� �������������� ����� ������������
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Transceiver
{
    struct Functions
    {
        void InitPins();
    };

    void Init();

    bool InInteraction();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace Transmitter
    {
        void Send(uint8 *data, uint size);
        void Send(uint8 data);
        void Send(uint8 byte0, uint8 byte1);
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace Receiver
    {
        /// ������� ������������ ������. ��������� ������, ���� ������� �������, � ������� �� ����� �������, ������������� � SetCallbackReceive.
        void Update();
    };
};

