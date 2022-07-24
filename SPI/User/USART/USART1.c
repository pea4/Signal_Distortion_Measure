#include "USART1.h"

static void NVIC_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /*分组配置*/
	NVIC_InitStructure.NVIC_IRQChannel=DEBUG_USART_IRQ; /*中断源*/
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; /*使能指令*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; /*抢占优先级*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; /*子优先级*/
	NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK | DEBUG_USART_CLK , ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=DEBUG_USART_TX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=DEBUG_USART_RX_PIN;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=DEBUG_USART_BAUDRATE;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(DEBUG_USART,&USART_InitStructure);
	
	NVIC_Configuration();
	USART_ITConfig(DEBUG_USART,USART_IT_RXNE,ENABLE);
	USART_Cmd(DEBUG_USART,ENABLE);
}

/**重定向printf**/

int fputc(int ch,FILE *f){
	USART_SendData(DEBUG_USART,(uint8_t) ch);
	while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TXE)==RESET);
	return(ch);
}

/**重定向scanf**/

int fgetc(FILE *f){
	while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TXE)==RESET);
	return (int) USART_ReceiveData(DEBUG_USART);
}
