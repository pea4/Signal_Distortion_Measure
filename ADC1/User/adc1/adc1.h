#ifndef __ADC1_H
#define	__ADC1_H

#include "stm32f10x.h"

#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx                          ADC2
#define    ADC_CLK                       RCC_APB2Periph_ADC2
#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC
#define    ADC_PIN                       GPIO_Pin_1
#define    ADC_CHANNEL                   ADC_Channel_11
#define    ADC_IRQ                       ADC1_2_IRQn
#define    ADC_IRQHandler                ADC1_2_IRQHandler

void ADCx_Init(void);

#endif
