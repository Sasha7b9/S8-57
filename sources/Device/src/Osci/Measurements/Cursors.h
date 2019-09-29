#pragma once
#include "Utils/String.h"
#include "Osci/Osci_Settings.h"


/// ������������� �������� ��� �������� ����� ��������� - �� ������ ��� ���������
#define CURS_MOVEMENT               (set.curs.movement)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == CursorsMovement::Percents)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1 �������
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == CursorsMovement::Pixels)

/// ������ ��������� ��������� ����� ���������
#define CURS_ACTIVE                 (set.curs.active)
/// ����� ��������� ��������� ��������� ����������
#define CURS_ACTIVE_U               (CURS_ACTIVE == CursorsActive::U)
/// ����� ��������� ��������� ��������� �������
#define CURS_ACTIVE_T               (CURS_ACTIVE == CursorsActive::T)

/// ������� ������� ����������
#define CURsU_POS(ch, num)          (set.curs.posCurU[ch][num])
/// ������� ������� �������
#define CURsT_POS(ch, num)          Cursors::PosT(ch, num)

/// ����� �������� �� ���������
#define CURS_LOOK_MODE(ch)          (set.curs.lookMode[ch])
/// �������� �������� �� ��������� ����������
#define CURS_LOOK_U(ch)             (CURS_LOOK_MODE(ch) == CursorsLookMode::Voltage)
/// �������� �������� �� ��������� �������
#define CURS_LOOK_T(ch)             (CURS_LOOK_MODE(ch) == CursorsLookMode::Time)
/// �������� �������� �� ��������� ������� � ����������
#define CURS_LOOK_BOTH(ch)          (CURS_LOOK_MODE(ch) == CursorsLookMode::Both)

#define CURsU_CNTRL_CH(ch)          (set.curs.cntrlU[ch])
#define CURsU_CNTRL                 (CURsU_CNTRL_CH(CURS_SOURCE))
#define CURsU_CNTRL_1               (CURsU_CNTRL == CursorsControl::_1)
#define CURsU_CNTRL_2               (CURsU_CNTRL == CursorsControl::_2)
#define CURsU_CNTRL_1_2             (CURsU_CNTRL == CursorsControl::_1_2)
#define CURsU_DISABLED              (CURsU_CNTRL == CursorsControl::Disable)
#define CURsU_ENABLED               (!CURsU_DISABLED)

#define CURsT_CNTRL_CH(ch)          (set.curs.cntrlT[ch])
#define CURsT_CNTRL                 (CURsT_CNTRL_CH(CURS_SOURCE))
#define CURsT_CNTRL_1               (CURsT_CNTRL == CursorsControl::_1)
#define CURsT_CNTRL_2               (CURsT_CNTRL == CursorsControl::_2)
#define CURsT_CNTRL_1_2             (CURsT_CNTRL == CursorsControl::_1_2)
#define CURsT_DISABLED              (CURsT_CNTRL == CursorsControl::Disable)
#define CURsT_ENABLED               (!CURsT_DISABLED)

#define CURSORS_SHOW_FREQ           (set.curs.showFreq)

/// ������� ������ ������ ������ �������
#define CURS_SOURCE                 (set.curs.source)
/// ������� ������� ������ A
#define CURS_SOURCE_A               (CURS_SOURCE == Chan::A)
/// ������� ������� ������ B
#define CURS_SOURCE_B               (CURS_SOURCE == Chan::B)

/// ���������� �������� ����������, ��������������� 100%
#define dUperc(ch)                  (set.curs.deltaU100percents[ch])
/// ���������� �������� �������, �������������� 100%
#define dTperc(ch)                  (set.curs.deltaT100percents[ch])

#define CURS_SHOW                   (set.curs.showCursors)


namespace Osci
{
    namespace Measurements
    {
        struct Cursors
        {
            /// ���������� ������� � ���������� ��������� ���������
            static void Draw();
            /// ���������� true,���� ����� �������� �������
            static bool  NecessaryDraw();
            /// �������� ������� ������� ����������
            static float PosU(Chan::E ch, int numCur);
            /// ���������� �������� ������� �������
            static float PosT(Chan::E ch, int num);
            /// �������� ������ ������� ����������
            static String Voltage(Chan::E source, int numCur);
            /// ������� ������ ������� �������
            static String Time(Chan::E source, int numCur);
            /// ���������� ������ ���������� ��������� �� ����������
            static String PercentsU(Chan::E source);
            /// ���������� ������ ���������� ��������� �� �������
            static String PercentsT(Chan::E source);

            static void SetCursPosT_temp(Chan::E ch, int num, float value);
        };
    };
};
