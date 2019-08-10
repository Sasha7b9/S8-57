#pragma once
#include "Menu/MenuItems.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct PageService
{
    static const Page * const self;

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    struct PageBattery
    {
        static const Page * const self; 
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageCalibrate
    {
    public:
        static const Page * const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageInformation
    {
    public:
        static const Page * const self;
    };

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageSound
    {
    public:
        static const PageBase * const pointer;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageRTC
    {
    public:
        static const Page * const self;

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageSet
        {
        public:
            static const Page * const self;
        };

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageCorrect
        {
        public:
            static const Page *const self;
        };
    };
};


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class PageDebug
{
public:
    static void OnChanged_ADC_Stretch_Mode(bool);
    static void OnChanged_DisplayOrientation(bool);

    static const Page * const self;


    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageConsole
    {
    public:
        static const Page * const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageRegisters
    {
    public:
        static const Page * const self;
    };


    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageRand
    {
    public:

        static const Page * const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageMultimeter
    {
    public:
        static const Page * const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageSettings
    {
    public:
        static const Page * const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageSerialNumber
    {
    public:
        static const Page * const self;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageADC
    {
    public:
        static const Page * const self;

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageBalance
        {
        public:
            static const Page * const self;
        };

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageStretch
        {
        public:
            static const Page * const self;
        };

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageShift
        {
        public:
            static const Page * const self;
        };
    };
};
