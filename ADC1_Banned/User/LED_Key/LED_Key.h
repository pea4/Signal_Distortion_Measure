#ifndef _LED_Key_H
#define _LED_Key_H
#include "stm32f10x.h"
#define KEY_ON 1
#define KEY_OFF 0
void Delay(uint32_t count);
void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
#endif
