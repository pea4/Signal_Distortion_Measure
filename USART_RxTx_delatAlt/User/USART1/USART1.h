#ifndef _USART1_H
#define _USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#define DEBUG_USART1 USART1
#define DEBUG_USART1_CLK RCC_APB2Periph_USART1
#define DEBUG_USART1_BAUDRATE 9600

#define DEBUG_USART1_RX_GPIO_PORT GPIOA
#define DEBUG_USART1_RX_GPIO_CLK RCC_APB2Periph_GPIOA
#define DEBUG_USART1_RX_PIN GPIO_Pin_10
#define DEBUG_USART1_RX_AF GPIO_AF_USART1
#define DEBUG_USART1_RX_SOURCE GPIO_PinSource10

#define DEBUG_USART1_TX_GPIO_PORT GPIOA
#define DEBUG_USART1_TX_GPIO_CLK RCC_APB2Periph_GPIOA
#define DEBUG_USART1_TX_PIN GPIO_Pin_9
#define DEBUG_USART1_TX_AF GPIO_AF_USART1
#define DEBUG_USART1_TX_SOURCE GPIO_PinSource9

#define DEBUG_USART1_IRQHandler USART1_IRQHandler
#define DEBUG_USART1_IQR USART1_IRQn

#define  Meter_OFF   	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
#define  Meter_ON   	GPIO_SetBits(GPIOA, GPIO_Pin_12);

void USART1_Config(void);

#endif
