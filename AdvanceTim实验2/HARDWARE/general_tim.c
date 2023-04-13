#include "general_tim.h"

/* ���ͨ�� GPIO��ʼ�� */
static void GENERAL_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ���ͨ��CH1 GPIO��ʼ��(PA6) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH1_PIN;
	GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	
	/* ���ͨ��CH2 GPIO��ʼ��(PA7) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH2_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH2_PIN;
	GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);
	
	/* ���ͨ��CH3 GPIO��ʼ��(PB0) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH3_PIN;
	GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);
	
	/* ���ͨ��CH4 GPIO��ʼ��(PB1) */
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH4_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH4_PIN;
	GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStructure);
}

/* ʱ����Ԫ�����벶��ͨ����ʼ�� */
static void GENERAL_TIM_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE);
	
	/* ʱ����Ԫ�ṹ���ʼ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 		= GENERAL_TIM_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler 	= GENERAL_TIM_PSC;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/* ����Ƚ�ͨ���ṹ���ʼ�� */
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;
	//TIM_OCInitStructure.TIM_OutputNState 	= TIM_OutputNState_Disable; // ��ʹ�û���������������
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_High;
	//TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;		// ��ʹ�û���������������
	//TIM_OCInitStructure.TIM_OCIdleState 	= TIM_OCIdleState_Set;		// ��ʹ�ÿ��е�ƽ���������
	//TIM_OCInitStructure.TIM_OCNIdleState 	= TIM_OCNIdleState_Reset;	// ��ʹ�û���������������
	
	/* ���ͨ��CH1��ʼ�� */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR1;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* ���ͨ��CH2��ʼ�� */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR2;
	TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* ���ͨ��CH3��ʼ�� */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR3;
	TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* ���ͨ��CH4��ʼ�� */
	TIM_OCInitStructure.TIM_Pulse = GENERAL_TIM_CCR4;
	TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	/* ʹ�ܼ����� */
	TIM_Cmd(GENERAL_TIM, ENABLE);
}


void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_MODE_Config();
}
