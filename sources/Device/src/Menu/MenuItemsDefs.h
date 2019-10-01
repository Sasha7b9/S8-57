#pragma once
#include "defines.h"
#include "Utils/CommonFunctions.h"


typedef bool(*pFuncBKE)(const KeyEvent&);

struct PageName
{
    enum E
    {
        /// ����� 1
        ChannelA,
        /// ����� 2
        ChannelB,
        /// �������
        Debug,
        Debug_ADC,
        Debug_ADC_Balance,
        Debug_ADC_Shift,
        Debug_ADC_Stretch,
        Debug_Console,
        Debug_Console_Registers,
        Debug_Rand,
        Debug_SerialNumber,
        Debug_Settings,
        /// �������
        Display,
        Display_Accumulation,
        Display_Settings,
        Display_Settings_Colors,
        Display_View,
        /// �������
        Function,
        Function_FFT,
        Function_FFT_Cursors,
        Function_FrequencyCounter,
        Function_Multimeter,
        Function_Multimeter_Cal,
        Function_Recorder,
        Function_Recorder_Show,
        Function_Recorder_Show_Choice,
        Function_Recorder_Source,
        Function_Tester,
        /// ������
        Help,
        /// �����
        Measures,
        Measures_Auto,
        Measures_Auto_Tune,
        Measures_Cursors,
        Measures_Cursors_Set,
        Measures_Math,
        /// ������
        Memory,
        Memory_Drive,
        Memory_Drive_Manager,
        Memory_Drive_Mask,
        Memory_Internal,
        Memory_Last,
        Memory_SetName,
        /// ������
        Service,
        Service_Battery,
        Service_Calibrator,
        Service_Info,
        Service_RTC,
        /// ����
        Time,
        /// �����
        Trig,
        Trig_HoldOff,
        Trig_Search,

        Number
    } value;
};



#define DEF_BUTTON(name, title, hint, keeper, funcActive, handlerPress)                                                                                                                     \
static const DataButton db##name = { handlerPress };                                                                                                                                        \
static const DataItem di##name = { Item::Type::Button, title, hint, keeper, funcActive, &db##name };                                                                                        \
static const Button name(&di##name);


#define DEF_GOVERNOR(name, title, hint, cell, min, max, keeper, funcActive, handlerChange)                                                                                                  \
static const DataGovernor dg##name = { (int16 *)&cell, min, max, handlerChange };                                                                                                           \
static const DataItem di##name = { Item::Type::Button, title, hint, keeper, funcActive, &dg##name };                                                                                        \
static const Governor name(&di##name);


#define DEF_GOVERNOR_COLOR(name, title, hint, colorType, keeper)                                                                                                                            \
static const DataGovernorColor dgc##name = { &colorType };                                                                                                                                  \
static const DataItem di##name = { Item::Type::GovernorColor, title, hint, keeper, Item::Active, &dgc##name };                                                                                     \
static const GovernorColor name(&di##name);


#define DEF_GRAPH_BUTTON(name, title, hint, keeper, funcActive, handlerPress, funcDraw)                                                                                                     \
static const DataGraphButton dgb##name = { handlerPress, funcDraw, nullptr };                                                                                                               \
static const DataItem di##name = { Item::Type::GovernorColor, title, hint, keeper, funcActive, &dgb##name };                                                                                \
static const GraphButton name(&di##name);

#define DEF_GRAPH_BUTTON_HINTS_2(name, title, hint, keeper, funcActive, handlerPress, funcDraw, funcDrawHint1, hint1, funcDrawHint2, hint2)                                                 \
static const StructHelpDrawButton shdb##name[] = { { funcDrawHint1, hint1 }, { funcDrawHint2, hint2 }, { nullptr } };                                                                       \
static const DataGraphButton dgb##name = { handlerPress, funcDraw, shdb##name };                                                                                                            \
static const DataItem di##name = { Item::Type::GovernorColor, title, hint, keeper, funcActive, &dgb##name };                                                                                \
static const GraphButton name(&di##name);

#define DEF_GRAPH_BUTTON_HINTS_3(name, title, hint, keeper, funcActive, handlerPress, funcDraw, funcDrawHint1, hint1, funcDrawHint2, hint2, funcDrawHint3, hint3)                           \
static const StructHelpDrawButton shdb##name[] = { { funcDrawHint1, hint1 }, { funcDrawHint2, hint2 }, { funcDrawHint3, hint3 }, { nullptr } };                                             \
static const DataGraphButton dgb##name = { handlerPress, funcDraw, shdb##name };                                                                                                            \
static const DataItem di##name = { Item::Type::GovernorColor, title, hint, keeper, funcActive, &dgb##name };                                                                                \
static const GraphButton name(&di##name);

#define DEF_GRAPH_BUTTON_HINTS_5(name, title, hint, keeper, funcActive, handlerPress, funcDraw,                                                                                             \
    funcDrawHint1, hint1, funcDrawHint2, hint2, funcDrawHint3, hint3, funcDrawHint4, hint4, funcDrawHint5, hint5)                                                                           \
static const StructHelpDrawButton shdb##name[] = { { funcDrawHint1, hint1 }, { funcDrawHint2, hint2 },                                                                                      \
    { funcDrawHint3, hint3 }, { funcDrawHint4, hint4 }, { funcDrawHint5, hint5 }, { nullptr } };                                                                                            \
static const DataGraphButton dgb##name = { handlerPress, funcDraw, shdb##name };                                                                                                            \
static const DataItem di##name = { Item::Type::GovernorColor, title, hint, keeper, funcActive, &dgb##name };                                                                                \
static const GraphButton name(&di##name);


#define DEF_PAGE_1(name, title, hint, item1, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                                                       \
static const Item * const i##name[] = { (Item *)item1, nullptr };                                                                                                                           \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_2(name, title, hint, item1, item2, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                                                \
static const Item * const  i##name[] = { (Item *)item1, (Item *)item2, nullptr };                                                                                                           \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_3(name, title, hint, item1, item2, item3, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                                         \
static const Item * const i##name[] = { (Item *)(item1), (Item *)(item2), (Item *)(item3), nullptr };                                                                                       \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name};                                                                                           \
static const Page name(&di##name);

#define DEF_PAGE_4(name, title, hint, item1, item2, item3, item4, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                                  \
static const Item * const i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, nullptr };                                                                              \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_5(name, title, hint,  item1, item2, item3, item4, item5, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                          \
static const Item * const i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, (Item *)item5, nullptr };                                                               \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_5_VAR(name, title, hint,  item1, item2, item3, item4, item5, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                      \
static const Item *i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, (Item *)item5, nullptr };                                                                      \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_6(name, title, hint, item1, item2, item3, item4, item5, item6, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                                    \
static const Item * const i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, (Item *)item5, (Item *)item6, nullptr };                                                \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_7(name, title, hint, item1, item2, item3, item4, item5, item6, item7, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                             \
static const Item * const  i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, (Item *)item5, (Item *)item6, (Item *)item7, nullptr };                                \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_8(name, title, hint, item1, item2, item3, item4, item5, item6, item7, item8, namePage, keeper, funcActive, funcOpenClose, funcBeforeDraw, funcArrows)                      \
static const Item * const  i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, (Item *)item5, (Item *)item6, (Item *)item7, (Item *)item8, nullptr };                 \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);

#define DEF_PAGE_12(name, title, hint, item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, namePage, keeper, funcActive, funcOpenClose,                  \
    funcBeforeDraw, funcArrows)                                                                                                                                                             \
static const Item * const  i##name[] = { (Item *)item1, (Item *)item2, (Item *)item3, (Item *)item4, (Item *)item5,                                                                         \
    (Item *)item6, (Item *)item7, (Item *)item8, (Item *)item9, (Item *)item10, (Item *)item11, (Item *)item12, nullptr };                                                                  \
static const DataPage dp##name = { namePage, i##name, funcOpenClose, funcBeforeDraw, funcArrows };                                                                                          \
static const DataItem di##name = { Item::Type::Page, title, hint, keeper, funcActive, &dp##name };                                                                                          \
static const Page name(&di##name);


#define DEF_CHOICE_2(name, title, hint, name1, name2, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                                                                 \
static const pString n##name[] = { name1, name2, nullptr };                                                                                                                                 \
static const DataChoice dc##name[] = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_3(name, title, hint, name1, name2, name3, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                                                          \
static const pString n##name[] = { name1, name2, name3, nullptr };                                                                                                                          \
static const DataChoice dc##name[] = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_4(name, title, hint, name1, name2, name3, name4, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                                                   \
static const pString n##name[] = { name1, name2, name3, name4, nullptr };                                                                                                                   \
static const DataChoice dc##name[] = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_5(name, title, hint, name1, name2, name3, name4, name5, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                                            \
static const pString n##name[] = { name1, name2, name3, name4, name5, nullptr };                                                                                                            \
static const DataChoice dc##name[] = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_6(name, title, hint, name1, name2, name3, name4, name5, name6, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                                     \
static const pString n##name[] = { name1, name2, name3, name4, name5, name6, nullptr };                                                                                                     \
static const DataChoice dc##name[] = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_7(name, title, hint, name1, name2, name3, name4, name5, name6, name7, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                              \
static const pString n##name[] = { name1, name2, name3, name4, name5, name6, name7, nullptr };                                                                                              \
static const DataChoice dc##name[] = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_9(name, title, hint, name1, name2, name3, name4, name5, name6, name7, name8, name9, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                \
static const pString n##name[] = { name1, name2, name3, name4, name5, name6, name7, name8, name9, nullptr };                                                                                \
static const DataChoice dc##name = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                  \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_10(name, title, hint, name1, name2, name3, name4, name5, name6, name7, name8, name9, name10, cell, keeper, funcActive, funcChanged, funcAfterDraw)                       \
static const pString n##name[] = { name1, name2, name3, name4, name5, name6, name7, name8, name9, name10, nullptr };                                                                        \
static const DataChoice dc##name = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                  \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);

#define DEF_CHOICE_16(name, title, hint, name1, name2,  name3,  name4,  name5,  name6,  name7,  name8, name9, name10,                                                                       \
    name11, name12, name13, name14, name15, name16, cell, keeper, funcActive, funcChanged, funcAfterDraw)                                                                                   \
static const pString n##name[] = { name1,  name2, name3,  name4,  name5,  name6, name7, name8, name9, name10, name11, name12, name13, name14, name15, name16, nullptr };                    \
static const DataChoice dc##name = { (int8 *)&cell, n##name, funcChanged, funcAfterDraw };                                                                                                  \
static const DataItem di##name = { Item::Type::Choice, title, hint, keeper, funcActive, &dc##name };                                                                                        \
static const Choice name(&di##name);
