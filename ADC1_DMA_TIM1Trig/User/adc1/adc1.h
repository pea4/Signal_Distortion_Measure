#ifndef __ADC1_H
#define	__ADC1_H

#include "stm32f10x.h"

#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1
#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC 
#define    ADC_PORT                      GPIOC
#define    ADC_PIN                       GPIO_Pin_1
#define    ADC_CHANNEL                   ADC_Channel_11
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_LEN                       256

#define ARR DEBUG_TIM_PERIOD
#define PSC DEBUG_TIM_PRESCAL

#define    DEBUG_TIM TIM1
#define    DEBUG_TIM_PERIOD          72-1   
#define    DEBUG_TIM_PRESCAL 10-1
#define    DEBUG_TIM_OC_MODE TIM_OCMode_PWM1
#define    DEBUG_TIM_OUTPUTSTATE TIM_OutputState_Enable
#define    DEBUG_TIM_PULSE 35
#define    DEBUG_TIM_OCPOLARITY TIM_OCPolarity_Low

void ADCx_Init(void);

#endif
