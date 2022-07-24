#include "stm32f10x.h"                  // Device header

void USART1_FPGA_Init(void)
{
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No ;
  USART_InitStruct.USART_Mode = USART_Mode_Rx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
	USART_Init(USART1, &USART_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_BufferSize = 4;  //FPGA传递四次数据32中断一次
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)spi_buf;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)SPI1+0x0c);
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_Init(DMA1_Channel2,&DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel2,ENABLE);
	
	USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
	USART_ITConfig(USART1, uint16_t USART_IT, FunctionalState NewState)
	
	
	

}