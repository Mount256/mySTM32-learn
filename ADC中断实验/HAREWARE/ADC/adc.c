#include "adc.h"

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ADC_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin 	= ADC_PIN;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

static void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);
	ADC_InitStructure.ADC_Mode 				= ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode 		= DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv 	= ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign 		= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel 		= 1;
	
	ADC_Init(ADC_x, &ADC_InitStructure);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	// void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, 
	//															uint8_t Rank, uint8_t ADC_SampleTime);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	// void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
	ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC_x, ENABLE);
	
	ADC_StartCalibration(ADC_x); // 开始校准
	while(ADC_GetCalibrationStatus(ADC_x) == SET); // 等待校准完成
	
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}

static void ADC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel 						= ADC_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void ADC_Init_Config(void)
{
	ADC_Mode_Config();
	ADC_GPIO_Config();
	ADC_NVIC_Config();
}
