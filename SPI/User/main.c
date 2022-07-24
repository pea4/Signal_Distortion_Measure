#include "stm32f10x.h"
#include "USART1.h"
#include "LED_Key.h"

int main(void){
	USART_Config();
	while(1){
		printf("hello STM32!\n");
		Delay(3000000);
	}
}
