#include "adc.h"

__IO uint16_t ADC_ConversionValue[4] = {0, 0, 0, 0};

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ADC_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN1;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN2;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN3;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN4;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

static void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);
	ADC_InitStructure.ADC_Mode 				= ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode 		= ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv 	= ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign 		= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel 		= 4;
	
	ADC_Init(ADC_x, &ADC_InitStructure);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC_x, ENABLE);
	ADC_DMACmd(ADC_x, ENABLE);
	
	ADC_StartCalibration(ADC_x); // 开始校准
	while(ADC_GetCalibrationStatus(ADC_x) == SET); // 等待校准完成
	
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}

static void ADC_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&(ADC_x->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr 	= (uint32_t) (ADC_ConversionValue);
	DMA_InitStructure.DMA_DIR 				= DMA_DIR_PeripheralSRC;
	
	DMA_InitStructure.DMA_BufferSize 		= 4; // 4个数据
	DMA_InitStructure.DMA_PeripheralInc 	= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 		= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize 	= DMA_MemoryDataSize_HalfWord;
	
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
