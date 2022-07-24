#include "stm32f10x.h"
#include "USART1.h"
#include "USART2.h"
#include "delay.h"
#include <string.h>

u8 idfind(u8 *buf,u8 *val,u8 len);
void HMISends(char *buf1);
void HMISendb(u8 buf);
uint32_t dutyCnt;
uint32_t delay_cnt;
uint8_t  stage;
uint32_t fxCnt;
uint32_t fbaseCnt;

uint8_t rx_buf[30];
uint16_t num = 0;
uint8_t receive_flg = 0;


float  frequency;  //频率
float  period   ;  //周期
float  duty      ;  // 占空比
float  time;     //时间间隔
float  time_start;     //时间间隔
float  time_end;     //时间间隔


int main(void){
	delay_init();
	USART1_Config();
	USART2_Config();
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	while(1){
			num=0;
			receive_flg=0;
			
			stage = rx_buf[1];
			dutyCnt=   (rx_buf[2] << 24)+(rx_buf[3] << 16)+(rx_buf[4] << 8)+(rx_buf[5]  << 0);
			delay_cnt =(rx_buf[6] << 24)+(rx_buf[7] << 16)+(rx_buf[8] << 8)+(rx_buf[9]  << 0);
			fxCnt  =  (rx_buf[10] << 24)+(rx_buf[11]<< 16)+(rx_buf[12]<< 8)+(rx_buf[13] << 0);
			fbaseCnt =(rx_buf[14] << 24)+(rx_buf[15]<< 16)+(rx_buf[16]<< 8)+(rx_buf[17] << 0);
			
			frequency=200000000*((float)fxCnt / (float)fbaseCnt);//200M
			period =  1 / frequency;//显示单位微妙
			duty   = 100* (float)dutyCnt / (float)fbaseCnt;
			
			switch(stage>>4){//高8位
				case(0x00): time_start=0;
				case(0x01): time_start=0.005*0.25;
				case(0x11): time_start=0.005*0.5;
				case(0x10): time_start=0.005*0.75;
				default   : time_start =0;
			}
			switch((stage&0x0f)){//低8位
				case(0x10): time_end=0;
				case(0x11): time_end=-0.005*0.25;
				case(0x01): time_end=-0.005*0.5;
				case(0x00): time_end=-0.005*0.75;
				default   : time_end =-0;
			}				
			time   =   0.005 * (float)delay_cnt  +time_start +time_end;
			
			
			
			char tjcstr[100];
			if(frequency<1000.0){
				HMISendb(0xff);
				sprintf(tjcstr, "main.t2.txt=\"%.4f Hz\"", frequency);
				HMISends(tjcstr);
				HMISendb(0xff);}
			else if(frequency>=1000.0 && frequency<1000000.0){
				HMISendb(0xff);
				sprintf(tjcstr, "main.t2.txt=\"%.4f KHz\"", frequency/1000.0);
				HMISends(tjcstr);
				HMISendb(0xff);}
			else if(frequency>=1000000.0){
				HMISendb(0xff);
				sprintf(tjcstr, "main.t2.txt=\"%.4f MHz\"", frequency/1000000.0);
				HMISends(tjcstr);
				HMISendb(0xff);}
			
			if(time<1000.0){
				HMISendb(0xff);
				sprintf(tjcstr, "page0.t4.txt=\"%.4f us\"", time);
				HMISends(tjcstr);
				HMISendb(0xff);}
			else if(time>=1000.0 ){
				HMISendb(0xff);
				sprintf(tjcstr, "page0.t4.txt=\"%.4f ms\"", time);
				HMISends(tjcstr);
				HMISendb(0xff);}
			HMISendb(0xff);
			sprintf(tjcstr, "page1.t6.txt=\"%.4f %% \"", duty);
			HMISends(tjcstr);
			HMISendb(0xff);
			}
	}


void HMISends(char *buf1)
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


void USART2_IRQHandler(void)
{	
	if(USART_GetITStatus(DEBUG_USART2,USART_IT_RXNE)!=RESET)
	{	
		rx_buf[num++] = USART_ReceiveData(DEBUG_USART2);
		if((rx_buf[0] == 0xf0 ) && (rx_buf[18]==0x0d ) && (rx_buf[19]==0x0f ) && (num==20))
		{
			receive_flg=1;
			USART_ClearITPendingBit(DEBUG_USART2,USART_IT_RXNE);
		}
	}
}

void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(DEBUG_USART1,USART_IT_RXNE)!=RESET)
	{
		if(USART_ReceiveData(DEBUG_USART1)==0xf0)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			delay_ms(100);
			GPIO_SetBits(GPIOA,GPIO_Pin_12);
			USART_ClearITPendingBit(DEBUG_USART1,USART_IT_RXNE);
		}
	}
}
