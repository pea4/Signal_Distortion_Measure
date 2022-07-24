#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
/*********************************************************************************/	 
//STM32串口示例程序
//更多资料：www.tftmcu.taobao.com									  
/*********************************************************************************/	
void delay_init(void);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#endif





























