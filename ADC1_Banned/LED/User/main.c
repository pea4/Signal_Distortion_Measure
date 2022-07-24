#include "stm32f10x.h"
#include "led.h"

void Delay(uint32_t count){
	for(;count!=0;count--);
}

int main(void){
    LED_GPIO_Config();
    while(1){
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			GPIO_SetBits(GPIOD,GPIO_Pin_2);
			Delay(0xffffff);
			GPIO_ResetBits(GPIOD,GPIO_Pin_2);
			GPIO_SetBits(GPIOA,GPIO_Pin_8);
			Delay(0xffffff);
    }
}
