#include "basic_tim.h"

void BASIC_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	/* ����APB1ʱ�� */
	RCC_APB1PeriphClockCmd(BASIC_TIMx_CLK, ENABLE);
	/* ����Ԥ��Ƶ */
	TIM_TimeBaseInitStructure.TIM_Prescaler = BASIC_TIM_Prescaler;
	/* ���ü���ģʽ */
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	/* �����Զ���װ���ֵ */
	TIM_TimeBaseInitStructure.TIM_Period = BASIC_TIM_Period;
	/* ����ʱ�ӷ�Ƶ���� */
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	/* �����ظ�����ֵ */
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	/* ��ʼ��������ʱ�� */
	TIM_TimeBaseInit(BASIC_TIMx, &TIM_TimeBaseInitStructure);
	/* ����жϱ�־λ */
	TIM_ClearFlag(BASIC_TIMx, TIM_FLAG_Update);
	/* �����ж� */
	TIM_ITConfig(BASIC_TIMx, TIM_IT_Update, ENABLE);
	/* ʹ�ܶ�ʱ�� */
	TIM_Cmd(BASIC_TIMx, ENABLE);
}

void BASIC_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIMx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
