#include "stm32f10x.h"
#include "USART1.h"
#include "adc1.h"
#include "delay.h"
#include <string.h>

extern __IO uint16_t ADC_ConvertedValue;
float ADC_ConvertedValueLocal; 

void Delay(int count){
	for(;count!=0;count--);
}

int main(void){
	delay_init();
	USART_Config();
	ADCx_Init();
	while(1){
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3;
		printf("\r\n The current AD value = 0x%04X \r\n", 
		       ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",
		       ADC_ConvertedValueLocal); 
		printf("\r\n\r\n");
		delay_ms(100);
	}
}
