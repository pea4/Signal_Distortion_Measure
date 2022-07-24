#include "SPI_W25Q128.h"

static __IO uint32_t SPITimeout=SPIT_LONG_TIMEOUT;
static uint16_t SPI_TIMEOUT_UserCallBack(uint8_t errorCode);

void SPI_FLASH_Init(void){
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MISO_GPIO_CLK | 
		FLASH_SPI_MOSI_GPIO_CLK | FLASH_CS_GPIO_CLK,ENABLE);
	FLASH_SPI_CLK_INIT(FLASH_SPI_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=FLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_SCK_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=FLASH_SPI_MISO_PIN;
	GPIO_Init(FLASH_SPI_MISO_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=FLASH_SPI_MOSI_PIN;
	GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=FLASH_CS_PIN;
	GPIO_Init(FLASH_CS_GPIO_PORT,&GPIO_InitStructure);
	
	SPI_FLASH_CS_HIGH();
	
	SPI_InitStructure
}