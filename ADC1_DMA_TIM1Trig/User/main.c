#include "stm32f10x.h"
#include "USART1.h"
#include "adc1.h"
#include "fft_calculate.h"
#include "delay.h"
#include <string.h>

extern __IO uint16_t ADC_ConvertedValue[];
extern uint16_t ADC_Value[];
float ADC_ConvertedValueLocal; 


int main(void){
	delay_init();
	USART_Config();
	ADCx_Init();
	while(1){
	}
}


void DMA1_Channel1_IRQHandler(void){
//	u16 Max_Val=0;
	int i = 0;
//	u16 Row;
//	float Freq;
	DMA_Cmd(ADC_DMA_CHANNEL,DISABLE);
	DMA_ClearITPendingBit(DMA_IT_HT);
	DMA_ClearITPendingBit(DMA1_IT_TC1);
	for(i=0;i<NPT;i++){
		printf("i= %d Mag=%f \r\n",i,(float)ADC_Value[i]/4096*3.3);
		//InBufArray[i] = ((signed short)(ADC_Value[i])) << 16;
		}
//	cr4_fft_1024_stm32(OutBufArray, InBufArray, NPT);
//	GetPowerMag();
//	for(i=2;i<NPT/2;i++)
//		{
//			printf("i= %d Mag=%d \r\n",i,(int)MagBufArray[i]);
//			if(MagBufArray[i]>Max_Val)
//			{
//				Max_Val=MagBufArray[i];
//				Row=i;
//			}
//		}
		//printf("DC Component: %f \r\n",(float)(((float)MagBufArray[0])/4096*3.3));
	//Freq=(float)(72000000)/(NPT*(ARR+1)*(PSC+1)/Row);
	//printf("Frequency: %f \r\n",Freq);
	DMA_Cmd(ADC_DMA_CHANNEL,ENABLE);
}
