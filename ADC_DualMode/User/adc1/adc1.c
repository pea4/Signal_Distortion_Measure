#include "adc1.h"

__IO uint32_t ADC_ConvertedValue[NOFCHANNEL]={0};

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_1_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADCx_1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_1_PORT, &GPIO_InitStructure);
	
	ADCx_2_GPIO_APBxClock_FUN ( ADCx_2_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADCx_2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_2_PORT, &GPIO_InitStructure);	
}

static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStructure.DMA_BufferSize=NOFCHANNEL;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ADC_ConvertedValue;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)(&(ADCx_1 -> DR));
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;
	DMA_Init(ADC_DMA_CHANNEL,&DMA_InitStructure);
	DMA_Cmd(ADC_DMA_CHANNEL,ENABLE);
	
	/*-------------------------------------*/
	
	ADC_InitTypeDef ADC_InitStructure;
	
	ADCx_1_APBxClock_FUN ( ADCx_1_CLK, ENABLE );
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANNEL;	
	ADC_Init(ADCx_1, &ADC_InitStructure);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	ADC_RegularChannelConfig(ADCx_1, ADCx_1_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	ADCx_2_APBxClock_FUN ( ADCx_2_CLK, ENABLE );
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANNEL;	
	ADC_Init(ADCx_2, &ADC_InitStructure);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	ADC_RegularChannelConfig(ADCx_2, ADCx_2_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADCx_1,ENABLE);
	ADC_Cmd(ADCx_1, ENABLE);
	ADC_Cmd(ADCx_2, ENABLE);
	
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	ADC_ResetCalibration(ADCx_1);
	while(ADC_GetResetCalibrationStatus(ADCx_1));
	ADC_StartCalibration(ADCx_1);
	while(ADC_GetCalibrationStatus(ADCx_1));
	
	ADC_ResetCalibration(ADCx_2);
	while(ADC_GetResetCalibrationStatus(ADCx_2));
	ADC_StartCalibration(ADCx_2);
	while(ADC_GetCalibrationStatus(ADCx_2));
	
	ADC_SoftwareStartConvCmd(ADCx_1, ENABLE);
}

void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();

}
