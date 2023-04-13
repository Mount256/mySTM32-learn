#include "adc.h"

__IO uint32_t ADC_ConversionValue = 0;

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1; // PC1
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2; // PC2
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

static void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_InitStructure.ADC_Mode 				= ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode 		= DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv 	= ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign 		= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel 		= 1;
	
	ADC_DMACmd(ADC1, ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
	ADC_StartCalibration(ADC1); 
	while(ADC_GetCalibrationStatus(ADC1) == SET); 

	ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);	
	ADC_Init(ADC2, &ADC_InitStructure);
	ADC_Cmd(ADC2, ENABLE);
	// ADC_DMACmd(ADC2, ENABLE); // ADC2与DMA不相连 
	ADC_StartCalibration(ADC2); 
	while(ADC_GetCalibrationStatus(ADC2) == SET); 
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	ADC_ExternalTrigConvCmd (ADC2, ENABLE);
}

static void ADC_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&(ADC1->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr 	= (uint32_t) (&ADC_ConversionValue);
	DMA_InitStructure.DMA_DIR 				= DMA_DIR_PeripheralSRC;
	
	DMA_InitStructure.DMA_BufferSize 		= 1; // 1个数据
	DMA_InitStructure.DMA_PeripheralInc 	= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 		= DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize 	= DMA_MemoryDataSize_Word;
	
	DMA_InitStructure.DMA_Mode 				= DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority 			= DMA_Priority_High;
	DMA_InitStructure.DMA_M2M 				= DMA_M2M_Disable;
	
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
}

void ADC_Init_Config(void)
{
	ADC_Mode_Config();
	ADC_GPIO_Config();
	ADC_DMA_Config();
}
