#include "LED_Key.h"

void Delay(uint32_t count){
	for(;count!=1;count--);
}

void KEY_GPIO_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin){
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON){
		Delay(0xfff);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON){
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON){
				return KEY_ON;
			}
		}
	}
	else return KEY_OFF;
}
