#include "defines.h"
#include "Transceiver.h"


namespace Transceiver
{
    namespace Transmitter
    {
        void InitPins();
        void Write_REQ_SEND(int);
        bool Read_ALLOW_SEND();
        bool Read_CONF_DATA();
        void Write_CLK(int);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Transceiver::InInteraction()
{
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::InitPins()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Write_REQ_SEND(int)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Transceiver::Transmitter::Read_ALLOW_SEND()
{
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Transceiver::Transmitter::Read_CONF_DATA()
{
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Transmitter::Write_CLK(int)
{

}
