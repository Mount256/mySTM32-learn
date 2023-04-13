#include "basic_tim.h"

void BASIC_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	/* 开启APB1时钟 */
	RCC_APB1PeriphClockCmd(BASIC_TIMx_CLK, ENABLE);
	/* 设置预分频 */
	TIM_TimeBaseInitStructure.TIM_Prescaler = BASIC_TIM_Prescaler;
	/* 设置计数模式 */
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	/* 设置自动重装溢出值 */
	TIM_TimeBaseInitStructure.TIM_Period = BASIC_TIM_Period;
	/* 设置时钟分频因子 */
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	/* 设置重复计数值 */
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	/* 初始化基本定时器 */
	TIM_TimeBaseInit(BASIC_TIMx, &TIM_TimeBaseInitStructure);
	/* 清除中断标志位 */
	TIM_ClearFlag(BASIC_TIMx, TIM_FLAG_Update);
	/* 开启中断 */
	TIM_ITConfig(BASIC_TIMx, TIM_IT_Update, ENABLE);
	/* 使能定时器 */
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
