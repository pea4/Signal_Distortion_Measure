#include "stm32f10x.h"
#include "USART1.h"
#include "delay.h"
#include <string.h>

u8 idfind(u8 *buf,u8 *val,u8 len);
void Sends(char *buf1);
int a=1;
int b=1;

void Delay(int count){
	for(;count!=0;count--);
}

/*void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USART,USART_IT_RXNE)!=RESET)
	{
		uint8_t Temp;
		Temp=USART_ReceiveData(DEBUG_USART);
		if(Temp==0x31){
			char tjcstr[100];
			sprintf(tjcstr, "t1.txt=\"rx ok b=%d\"",b);
			HMISends(tjcstr);
			HMISendb(0xff);
			b+=1;
		}

	}
}*/


int main(void){
	delay_init();
	USART_Config();
	while(1){
		char str[100];
		sprintf(str, "%d", a);
		Sends(str);
		Delay(7200000);
		a++;
		if(a>100)a=0;
	}
}

void Sends(char *buf1)
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			USART_SendData(USART1,buf1[i]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
		 	i++;
		}
	 else 
	 return ;

	}
}
