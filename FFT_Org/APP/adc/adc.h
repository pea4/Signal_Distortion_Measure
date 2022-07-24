#ifndef _adc_H
#define _adc_H

#include "system.h"

#define ARR 36-1
#define PSC 1-1
#define ADC_LEN    1024

void ADC_Configuration(void);

void ADC1_Init(void);
void ADC1_DMA1_Init(void);
void TIM1_Init(void);

#endif
