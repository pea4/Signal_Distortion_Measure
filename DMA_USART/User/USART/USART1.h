#ifndef _USART1_H
#define _USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#define DEBUG_USART USART1
#define DEBUG_USART_CLK RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE 9600

#define DEBUG_USART_RX_GPIO_PORT GPIOA
#define DEBUG_USART_RX_GPIO_CLK RCC_APB2Periph_GPIOA
#define DEBUG_USART_RX_PIN GPIO_Pin_10
#define DEBUG_USART_RX_AF GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT GPIOA
#define DEBUG_USART_TX_GPIO_CLK RCC_APB2Periph_GPIOA
#define DEBUG_USART_TX_PIN GPIO_Pin_9
#define DEBUG_USART_TX_AF GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE GPIO_PinSource9

#define DEBUG_USART_IRQHandler USART1_IRQHandler
#define DEBUG_USART_IQR USART1_IRQn

#define DEBUG_DMA_TX_CHN DMA1_Channel7
#define DEBUG_DMA_TX_PeriphBaseAddr ((uint32_t)USART2+0x04)
#define DEBUG_DMA_TX_DIR DMA_DIR_PeripheralDST
#define DEBUG_DMA_TX_PeriphInc DMA_PeripheralInc_Disable
#define DEBUG_DMA_TX_MemInc DMA_MemoryInc_Enable
#define DEBUG_DMA_TX_PeriDataSize DMA_PeripheralDataSize_Byte
#define DEBUG_DMA_TX_MemDataSize DMA_MemoryDataSize_Byte
#define DEBUG_DMA_TX_Mode DMA_Mode_Normal
#define DEBUG_DMA_TX_Priority DMA_Priority_VeryHigh
#define DEBUG_DMA_TX_M2M DMA_M2M_Disable


void USART_Config(void);

#endif
