#include "advance_tim.h"

static void ADVANCE_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStrutcure;
	
	/* ����Ƚ�ͨ����ʼ�� */
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_PORT_CLK, ENABLE);
	GPIO_InitStrutcure.GPIO_Pin 	= ADVANCE_TIM_CH1_PIN;
	GPIO_InitStrutcure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStrutcure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(ADVANCE_TIM_CH1_PORT ,&GPIO_InitStrutcure);

	/* ����Ƚϻ���ͨ����ʼ�� */
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1N_PORT_CLK, ENABLE);
	GPIO_InitStrutcure.GPIO_Pin 	= ADVANCE_TIM_CH1N_PIN;
	GPIO_InitStrutcure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStrutcure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(ADVANCE_TIM_CH1N_PORT ,&GPIO_InitStrutcure);
	
	/* ����Ƚ�ɲ��ͨ����ʼ�� */
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_BKIN_PORT_CLK, ENABLE);
	GPIO_InitStrutcure.GPIO_Pin 	= ADVANCE_TIM_BKIN_PIN;
	GPIO_InitStrutcure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStrutcure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(ADVANCE_TIM_BKIN_PORT ,&GPIO_InitStrutcure);

	/* BKIN����Ĭ������͵�ƽ */
	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT, ADVANCE_TIM_BKIN_PIN);
}

static void ADVANCE_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 		TIM_OCInitStructure;
	TIM_BDTRInitTypeDef 	TIM_BDTRInitStructure;
	
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE);
	
	/* ʱ����Ԫ��ʼ�� */
	TIM_TimeBaseStructure.TIM_Prescaler 		= ADVANCE_TIM_PSC;
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 			= ADVANCE_TIM_PERIOD;
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVANCE_TIM_RECNT;
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
	/* ����Ƚϳ�ʼ�� */
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OutputNState 	= TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse 			= ADVANCE_TIM_PULSE;
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState 	= TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState 	= TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
	
	/* ɲ��������ʼ�� */
	TIM_BDTRInitStructure.TIM_OSSRState 		= TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState 		= TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel 		= TIM_LOCKLevel_1;
	TIM_BDTRInitStructure.TIM_DeadTime 			= ADVANCE_TIM_DEAD_TIME;
	TIM_BDTRInitStructure.TIM_Break 			= TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity 	= TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput 	= TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);
	
	/* ʹ�ܶ�ʱ�� */
	TIM_Cmd(ADVANCE_TIM, ENABLE);
	TIM_CtrlPWMOutputs(ADVANCE_TIM, ENABLE);
	
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_Mode_Config();
}
