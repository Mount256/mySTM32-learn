#include "general_tim.h"

TIM_ICUserValueTypeDef TIM_ICUserValueStructure = {0,0,0,0};

/* GPIO初始化，WK_UP 和 TIM5_CH1 对应的是PA0 */
static void GENERAL_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_PORT_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GENERAL_TIM_CH1_PIN;
	GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
}

/* 时基单元和输入捕获通道初始化 */
static void GENERAL_TIM_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef		TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE);
	
	/* 时基单元结构体初始化 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 		= GENERAL_TIM_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler 	= GENERAL_TIM_PSC;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/* 输入捕获通道结构体初始化 */
	TIM_ICInitStructure.TIM_Channel 	= GENERAL_TIM_CHANNEL_x;
	TIM_ICInitStructure.TIM_ICFilter 	= 0;
	TIM_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(GENERAL_TIM, &TIM_ICInitStructure);
	
	//清除更新和捕获中断标志位
	TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update | TIM_FLAG_CC1);	
	//开启更新和捕获中断  
	TIM_ITConfig(GENERAL_TIM, TIM_IT_Update | TIM_IT_CC1, ENABLE);
	//使能计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);
}

/* NVIC中断初始化 */
static void GENERAL_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel 						= GENERAL_TIM_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_MODE_Config();
	GENERAL_TIM_NVIC_Config();
}
