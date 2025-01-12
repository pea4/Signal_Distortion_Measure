#ifndef _USART2_H
#define _USART2_H

#include "stm32f10x.h"
#include <stdio.h>
#define DEBUG_USART2 USART2
#define DEBUG_USART2_CLK RCC_APB1Periph_USART2
#define DEBUG_USART2_BAUDRATE 9600

#define DEBUG_USART2_RX_GPIO_PORT GPIOA
#define DEBUG_USART2_RX_GPIO_CLK RCC_APB2Periph_GPIOA
#define DEBUG_USART2_RX_PIN GPIO_Pin_3
#define DEBUG_USART2_RX_AF GPIO_AF_USART2
#define DEBUG_USART2_RX_SOURCE GPIO_PinSource3

#define DEBUG_USART2_TX_GPIO_PORT GPIOA
#define DEBUG_USART2_TX_GPIO_CLK RCC_APB2Periph_GPIOA
#define DEBUG_USART2_TX_PIN GPIO_Pin_2
#define DEBUG_USART2_TX_AF GPIO_AF_USART2 
#define DEBUG_USART2_TX_SOURCE GPIO_PinSource2

#define DEBUG_USART2_IRQHandler USART2_IRQHandler
#define DEBUG_USART2_IQR USART2_IRQn

void USART2_Config(void);

#endif
