#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "fft_calculate.h"
#include "adc.h"
#include "time.h"
#include "math.h"
#include <string.h>

u16 ARR=719;
u16 PSC=0;
u16 ADC_LEN = 1024;
u32 Freq;
u16 Row;
u16 Max_Val=0;u16 Max_Val2=0;u16 Max_Val3=0;u16 Max_Val4=0;u16 Max_Val5=0;
u16 adc_value[5];
u16 points=0;
int a=0xFF;
extern uint16_t ADC_Value[];
int fft_Complete_Flag = 0;

void HMISendb(u8 k)
{
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(USART1,k);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
		}
	 else
	 return ;
	 } 
}

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	u16 i;
	float u1,u2,u3,u4,u5=0.0;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	USART1_Init(115200);
	
	TIM1_Init();
  ADC1_DMA1_Init();
  ADC1_Init();
	delay_ms(50);
  TIM_Cmd(TIM1, ENABLE);
	
	while(1)
	{
		if(fft_Complete_Flag == 1)
		{
				Max_Val=0;Max_Val2=0;Max_Val3=0;Max_Val4=0;Max_Val5=0;
				for(i=2;i<NPT/2;i++)
				{
					if(MagBufArray[i]>Max_Val)
					{
						Max_Val=MagBufArray[i];
						Row=i;
					}
					//printf("\r\n Voltage = %f \r\n",(float)adc_value[i]/4096*3.3);
					//printf("Freq = %d Hz , Voltage = %f V\r\n",i,(float)MagBufArray[i]/4096*3.3);
				}
				for(i=0;i<NPT/2;i++)
				{

					printf("add 1,0,%d",(int)(MagBufArray[NPT/2-i]*200.0/4096));
					HMISendb(0xff);
				}
				printf("add 1,0,0");HMISendb(0xff);printf("add 1,0,0");HMISendb(0xff);
				printf("add 1,0,0");HMISendb(0xff);printf("add 1,0,0");HMISendb(0xff);
				printf("add 1,0,0");HMISendb(0xff);printf("add 1,0,0");HMISendb(0xff);
				printf("add 1,0,0");HMISendb(0xff);printf("add 1,0,0");HMISendb(0xff);
				Freq=(72000000)/(NPT*(ARR+1)*(PSC+1)/Row);
//				points=(int)((1.0f/(Freq*1.0f))*1.5f/0.00171f*1024);
				//printf("%d\r\n",points);
//				for(i=0;i<points;i++)
//				{
//					printf("add 1,0,%d",adc_value[i]*200/4096);
//					HMISendb(0xff);
//				}
				if(Freq<1000.0){
					printf("t3.txt=\"%f Hz\"",(float)Freq);
					HMISendb(0xff);}
				else if(Freq>=1000.0 && Freq<1000000.0){
					printf("t3.txt=\"%.3f kHz\"",(float)Freq/1000);
					HMISendb(0xff);}
				else if(Freq>=1000000.0){
					printf("t3.txt=\"%.3f MHz\"",(float)Freq/1000000);
					HMISendb(0xff);}
				u1=(float)MagBufArray[Row]/4096*3.3;
				for(int j=0;j<7;j++)
				{
					if(MagBufArray[2*Row-3+j]>Max_Val2)Max_Val2=MagBufArray[2*Row-3+j];
					if(MagBufArray[3*Row-3+j]>Max_Val3)Max_Val3=MagBufArray[3*Row-3+j];
					if(MagBufArray[4*Row-3+j]>Max_Val4)Max_Val4=MagBufArray[4*Row-3+j];
					if(MagBufArray[5*Row-3+j]>Max_Val5)Max_Val5=MagBufArray[5*Row-3+j];
				}
				u2=(float)Max_Val2/4096.0*3.3;
				u3=(float)Max_Val3/4096.0*3.3;
				u4=(float)Max_Val4/4096.0*3.3;
				u5=(float)Max_Val5/4096.0*3.3;
				printf("t1.txt=\"%.4f %%\"" , (float)100*(sqrt(u2*u2+u3*u3+u4*u4+u5*u5)/u1));
				HMISendb(0xff);
				printf("t10.txt=\"1\"");
				HMISendb(0xff);
				printf("t11.txt=\"%.3f\"",u2/u1);
				HMISendb(0xff);
				printf("t12.txt=\"%.3f\"",u3/u1);
				HMISendb(0xff);
				printf("t13.txt=\"%.3f\"",u4/u1);
				HMISendb(0xff);
				printf("t14.txt=\"%.3f\"",u5/u1);
				HMISendb(0xff);
				
//			printf("\r\n BaseFrequency = %d , Mag= %f V \r\n",Freq,(float)MagBufArray[Row]/4096*3.3);
//			printf("\r\n 2Frequency = %d , Mag= %f V \r\n",2*Freq,(float)(MagBufArray[2*Row]+MagBufArray[2*Row-1]+MagBufArray[2*Row+1])/4096*3.3);
//			printf("\r\n 3Frequency = %d , Mag= %f V \r\n",3*Freq,(float)(MagBufArray[3*Row]+MagBufArray[3*Row-1]+MagBufArray[3*Row+1])/4096*3.3);
//			printf("\r\n 4Frequency = %d , Mag= %f V \r\n",4*Freq,(float)(MagBufArray[4*Row]+MagBufArray[4*Row-1]+MagBufArray[4*Row+1])/4096*3.3);
//			printf("\r\n 5Frequency = %d , Mag= %f V \r\n",5*Freq,(float)(MagBufArray[5*Row]+MagBufArray[5*Row-1]+MagBufArray[5*Row+1])/4096*3.3);
//			printf("\r\n u1= %f \r\n" , u1);
//			printf("\r\n u2= %f \r\n" , u2);
//			printf("\r\n u3= %f \r\n" , u3);
//			printf("\r\n u4= %f \r\n" , u4);
//			printf("\r\n u5= %f \r\n" , u5);
//			printf("\r\n THD= %f %% \r\n" , (float)100*(sqrt(pow(u2,2)+pow(u3,2)+pow(u4,2)+pow(u5,2))/u1));
			fft_Complete_Flag = 0;
//			ADC1_DMA1_Init();
//			DMA_Cmd(DMA1_Channel1, ENABLE);
		}

	}
}
