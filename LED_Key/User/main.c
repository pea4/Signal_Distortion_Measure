#include "stm32f10x.h"
#include "led.h"
#include "LED_Key.h"

/*void GPIO_ToggleBits(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin){
	if(GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
		GPIO_ResetBits(GPIOx,GPIO_Pin);
	else GPIO_SetBits(GPIOx,GPIO_Pin);
}*/

int main(void){
	LED_GPIO_Config();
	KEY_GPIO_Config();
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	while(1){
		if(Key_Scan(GPIOE,GPIO_Pin_4)==KEY_ON){
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);}
		else if(Key_Scan(GPIOE,GPIO_Pin_4)==KEY_OFF){
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);}
	}
}
