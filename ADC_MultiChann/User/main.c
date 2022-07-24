#include "stm32f10x.h"
#include "USART1.h"
#include "adc1.h"
#include "delay.h"
#include <string.h>

extern __IO uint16_t ADC_ConvertedValue[];
float ADC_ConvertedValueLocal[NOFCHANNEL]; 

void Delay(int count){
	for(;count!=0;count--);
}

int main(void){
	delay_init();
	USART_Config();
	ADCx_Init();
	while(1){
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
		ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
		ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
		ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
		
		printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[0]); 
		printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[1]); 
		printf("\r\n CH3 value = %f V \r\n",ADC_ConvertedValueLocal[2]); 
		printf("\r\n CH4 value = %f V \r\n",ADC_ConvertedValueLocal[3]); 
		printf("\r\n CH5 value = %f V \r\n",ADC_ConvertedValueLocal[4]); 
		printf("\r\n CH6 value = %f V \r\n",ADC_ConvertedValueLocal[5]); 
		printf("\r\n\r\n");
		delay_ms(100);
	}
}
