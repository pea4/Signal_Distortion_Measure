#include "stm32f10x.h"
#include "USART1.h"
#include "adc1.h"
#include "delay.h"
#include <string.h>

extern __IO uint32_t ADC_ConvertedValue[NOFCHANNEL];
float ADC_ConvertedValueLocal[NOFCHANNEL*2]; 

void Delay(int count){
	for(;count!=0;count--);
}

int main(void){
	uint16_t temp0=0 ,temp1=0;
	delay_init();
	USART_Config();
	ADCx_Init();
	while(1){

    // 取出ADC1数据寄存器的高16位，这个是ADC2的转换数据
		temp0 = (ADC_ConvertedValue[0]&0XFFFF0000) >> 16;
		// 取出ADC1数据寄存器的低16位，这个是ADC1的转换数据
		temp1 = (ADC_ConvertedValue[0]&0XFFFF);	
		
		ADC_ConvertedValueLocal[0] =(float) temp0/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) temp1/4096*3.3;
		
		printf("\r\n ADCx_1 value = %f V \r\n",
		        ADC_ConvertedValueLocal[1]);
		printf("\r\n ADCx_2 value = %f V \r\n",
		        ADC_ConvertedValueLocal[0]);
		
		printf("\r\n\r\n");

		delay_ms(100);
	}
}
