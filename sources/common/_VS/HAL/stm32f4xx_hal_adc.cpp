#include "stdafx.h"
#include <stm32f4xx_hal_adc.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C"
{
    HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* /*hadc*/)
    {
        return HAL_ERROR;
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* /*hadc*/, ADC_ChannelConfTypeDef* /*sConfig*/)
    {
        return HAL_ERROR;
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* /*hadc*/)
    {
        return 0;
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* /*hadc*/)
    {
        return HAL_ERROR;
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* /*hadc*/, uint32_t /*Timeout*/)
    {
        return HAL_ERROR;
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* /*hadc*/)
    {
        return HAL_ERROR;
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    void HAL_ADC_IRQHandler(ADC_HandleTypeDef* /*hadc*/)
    {

    }
}
