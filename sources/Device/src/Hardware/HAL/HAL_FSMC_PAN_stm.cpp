#include "defines.h"
#include "common/Decoder_d.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/HAL_PIO.h"
#include <stm32f4xx_hal.h>
#ifdef DEVICE
#include "Osci/Osci.h"
#endif


struct OutPin
{
    OutPin(HPort::E _port, uint16 _pin) : port(_port), pin(_pin) {}

    void Init()       { HAL_PIO::Init(port, pin, HMode::Output_PP, HPull::Up); SetPassive(); }
    void SetActive()  { HAL_PIO::Reset(port, pin); }
    void SetPassive() { HAL_PIO::Set(port, pin); }

    HPort::E port;
    uint16 pin;
};


struct InPin
{
    InPin(HPort::E _port, uint16 _pin) : port(_port), pin(_pin) {}

    void Init()        { HAL_PIO::Init(port, pin, HMode::Input, HPull::Up); }
    bool IsActive()    { return HAL_PIO::Read(port, pin) == 0; };
    bool IsPassive()   { return HAL_PIO::Read(port, pin) == 1; };
    void WaitActive()  { while(IsPassive()) { } }
    void WaitPassive() { while(IsActive()) { } }

    HPort::E port;
    uint16 pin;
};


struct DataBus
{
    /// �������������� �������������
    static void Init();
};


/// �� ��������� ��������� ����� ���� ������ ����������, ��� ������� �� ����� � ��������������
static OutPin pinCS(PIN_CS);
/// �� ������������ ��������� ����� ���� ������ ����������, ��� ������� �� ����� ������ ��������
static OutPin pinWR(PIN_WR);
/// �� ��������� ��������� ����� ���� ������ ����������, ��� ������� �� ����� ������ ������
static OutPin pinRD(PIN_RD);

/// �������� ���������� ����� ���� ������ �������� � ���������� � ��������������
static InPin pinReadyPAN(PIN_PAN_READY);
/// �������� ��������� ����� ���� �������� � ���, ��� ������ ����� ������ ��� ��������
static InPin pinDataPAN(PIN_PAN_DATA);

/// true ��������, ��� ���� ��������� � �������� ������ � ������� � ������ �� ������� FSMC � ������� � ������ ���������
static bool interactionWithPanel = false;

void HAL_BUS::InitPanel()
{
    pinReadyPAN.Init();
    pinDataPAN.Init();
    pinCS.Init();

    DataBus::Init();
}


bool HAL_BUS::Panel::Receive()
{
    //if(pinReadyPAN.IsPassive() || pinDataPAN.IsPassive())
    if((GPIOA->IDR & GPIO_PIN_7) || (GPIOC->IDR & GPIO_PIN_4))
    {
        return false;
    }
   
    interactionWithPanel = true;
    
    if(mode != Mode::PanelRead)
    {
        mode = Mode::PanelRead;

        pinRD.Init();

        // ������������� �� �� ������

        GPIOD->MODER &= 0x0ffffff0U;        // �������� ���� 14, 15, 0, 1 �� ������ D0, D1, D2, D3

        GPIOE->MODER &= 0xffc03fffU;        // �������� ���� 7, 8, 9, 10 �� ������ D4, D5, D6, D7
    }
    
    pinRD.SetActive();

    pinCS.SetActive();
    
    pinReadyPAN.WaitPassive();
    while(pinReadyPAN.IsActive()) {};
    
    uint8 data = 0;

    while((GPIOA->IDR & GPIO_PIN_7) == 0)
    {
        if(pinDataPAN.IsPassive())
        {
            goto exit;
        }
    }
    
    //                                                 4,5,6,7              2,3                          0,1
    data = static_cast<uint8>((GPIOE->IDR >> 3) & 0xF0 | (GPIOD->IDR << 2) & 0x0C | (GPIOD->IDR >> 14));

    DDecoder::AddData(data);
    
exit:
    
    //pinRD.SetPassive();
    GPIOD->BSRR = GPIO_PIN_4;

    //pinCS.SetPassive();
    GPIOG->BSRR = GPIO_PIN_12;
    
    interactionWithPanel = false;

#ifdef DEVICE
    if(Osci::InModeP2P())
    {
        Osci::ReadPointP2P();
    }
#endif

    return true;
}


void HAL_BUS::Panel::Send(uint8 byte)
{
    Send(&byte, 1);
}


void HAL_BUS::Panel::Send(uint8 byte0, uint8 byte1)
{
    uint8 buffer[2] = { byte0, byte1 };
    
    Send(buffer, 2);
}

void HAL_BUS::Panel::Send(uint8 *data, uint size)
{
    interactionWithPanel = true;

    if(mode != Mode::PanelWrite)
    {
        mode = Mode::PanelWrite;

        pinWR.Init();

        // ������������� �� �� ������

        GPIOD->MODER &= 0x0ffffff0U;        // �������� ���� 14, 15, 0, 1 �� ������ D0, D1, D2, D3
        GPIOD->MODER |= 0x50000005U;        // ������������� ��� ���� ����� GPIO_MODE_OUTPUT_PP

        GPIOE->MODER &= 0xffc03fffU;        // �������� ���� 7, 8, 9, 10 �� ������ D4, D5, D6, D7
        GPIOE->MODER |= 0x00154000U;        // ������������� ��� ���� ����� GPIO_MODE_OUTPUT_PP
    }

    for(uint i = 0; i < size; i++)
    {
        uint8 d = *data++;

        //                                                                             ���� 0,1                                 ���� 2,3
        GPIOD->ODR = (GPIOD->ODR & 0x3ffc) + static_cast<uint16>((static_cast<int16>(d) & 0x03) << 14) + ((static_cast<uint16>(d & 0x0c)) >> 2);  // ���������� ������ � �������� ����
        //                                                                          ���� 4,5,6,7
        GPIOE->ODR = (GPIOE->ODR & 0xf87f) + static_cast<uint16>((static_cast<int16>(d) & 0xf0) << 3);

        pinWR.SetActive();                  // ��� ������ ������
        
        while(pinReadyPAN.IsPassive()) {}   // � ������� ������ ������ � ���, ��� ��� ��������

        pinCS.SetActive();                  // ��� ������� ����, ��� ������ ���������� � ����� �� ���������

        while(pinReadyPAN.IsActive()) {}    // ������������ PIN_PAN_READY � ���������� ��������� ��������, ��� ������ ������� ������ � ������������ ��

        pinWR.SetPassive();                 // \ ������������� WR � CS � ���������� ��������� - ������������ ���� ������ �������

        pinCS.SetPassive();                 // /
    }

    interactionWithPanel = false;
}


bool HAL_BUS::Panel::InInteraction()
{
    return interactionWithPanel;
}


void DataBus::Init()
{
    // ������������� �� �� ������

    GPIOD->MODER &= 0x0ffffff0U;        // �������� ���� 14, 15, 0, 1 �� ������ D0, D1, D2, D3

    GPIOE->MODER &= 0xffc03fffU;        // �������� ���� 7, 8, 9, 10 �� ������ D4, D5, D6, D7
}
