#include "defines.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Hardware/Beeper.h"
#include "Menu/Pages/Include/Definition.h"
#include "Display/Painter.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageFunction;

const Page * const PageFunction::self = (const Page *)&pageFunction;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_5( pageFunction,                                                                                                                                                   //--- ������� ---
    "�������",
    "����� �������",
    PageFrequencyCounter::self,   ///< ������� - ����������
    PageFFT::self,                ///< ������� - ������
    PageMultimeter::self,         ///< ������� - ����������
    PageTester::self,             ///< ������� - ������
    PageRecorder::self,           ///< ������� - �����������
    Page::Name::Function, nullptr, 0, 0, 0, 0
)
