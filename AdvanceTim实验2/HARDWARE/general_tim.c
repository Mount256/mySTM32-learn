#include "general_tim.h"

/* 输出通道 GPIO初始化 */
static void GENERAL_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 输出通道CH1 GPIO初始化(PA6) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH1_PIN;
	GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	
	/* 输出通道CH2 GPIO初始化(PA7) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH2_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH2_PIN;
	GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);
	
	/* 输出通道CH3 GPIO初始化(PB0) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH3_PIN;
	GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);
	
	/* 输出通道CH4 GPIO初始化(PB1) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH4_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH4_PIN;
	GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStructure);
}

/* 时基单元和输入捕获通道初始化 */
static void GENERAL_TIM_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE);
	
	/* 时基单元结构体初始化 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 		= GENERAL_TIM_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler 	= GENERAL_TIM_PSC;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/* 输出比较通道结构体初始化 */
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;
	//TIM_OCInitStructure.TIM_OutputNState 	= TIM_OutputNState_Disable; // 不使用互补输出，不用理会
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_High;
	//TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;		// 不使用互补输出，不用理会
	//TIM_OCInitStructure.TIM_OCIdleState 	= TIM_OCIdleState_Set;		// 不使用空闲电平，不用理会
	//TIM_OCInitStructure.TIM_OCNIdleState 	= TIM_OCNIdleState_Reset;	// 不使用互补输出，不用理会
	
	/* 输出通道CH1初始化 */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR1;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* 输出通道CH2初始化 */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR2;
	TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* 输出通道CH3初始化 */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR3;
	TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* 输出通道CH4初始化 */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR4;
	TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* 使能计数器 */
	TIM_Cmd(GENERAL_TIM, ENABLE);
}


void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_MODE_Config();
}
