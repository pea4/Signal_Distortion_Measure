#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "tftlcd.h"
#include "fft_calculate.h"
#include "adc.h"
#include "time.h"

u32 Freq;
u16 Row;
u16 Max_Val=0;
u16 adc_value[5];
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	//u16 i;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	//LED_Init();
	USART1_Init(115200);
	//TFTLCD_Init();			//LCD��ʼ��
	
	TIM1_Init();
  ADC1_DMA1_Init();
  ADC1_Init();
  TIM_Cmd(TIM1, ENABLE);

	while(1)
	{
		//Max_Val=0;
		/*for(i=2;i<NPT/2;i++)
		{
			if(MagBufArray[i]>Max_Val)
			{
				Max_Val=MagBufArray[i];
				Row=i;
			}
		}
		Freq=(72000000)/(NPT*(ARR+1)*(PSC+1)/Row);
		printf("Freq: %d \r\n",Freq);*/
	}
}
