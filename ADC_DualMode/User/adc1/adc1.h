#ifndef __ADC1_H
#define	__ADC1_H

#include "stm32f10x.h"

#define    ADCx_1_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx_1                           ADC1
#define    ADCx_1_CLK                       RCC_APB2Periph_ADC1
#define    ADCx_1_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADCx_1_GPIO_CLK                  RCC_APB2Periph_GPIOC
#define    ADCx_1_PORT                      GPIOC
#define    ADCx_1_GPIO_PIN					GPIO_Pin_1
#define    ADC_DMA_CLK                   	RCC_AHBPeriph_DMA1
#define    ADC_DMA_CHANNEL               	DMA1_Channel1
#define    ADCx_1_CHANNEL                   ADC_Channel_11

#define    ADCx_2_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx_2                           ADC2
#define    ADCx_2_CLK                       RCC_APB2Periph_ADC2
#define    ADCx_2_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADCx_2_GPIO_CLK                  RCC_APB2Periph_GPIOC
#define    ADCx_2_GPIO_PIN					GPIO_Pin_4
#define    ADCx_2_PORT                      GPIOC
#define    ADCx_2_CHANNEL                   ADC_Channel_14

#define    NOFCHANNEL                    1

void ADCx_Init(void);

#endif
