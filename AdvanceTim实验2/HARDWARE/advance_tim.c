#include "advance_tim.h"

static void ADVANCE_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStrutcure;
	
	/* 输入捕获通道初始化(PA8) */
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_PORT_CLK, ENABLE);
	GPIO_InitStrutcure.GPIO_Pin 	= ADVANCE_TIM_CH1_PIN;
	GPIO_InitStrutcure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStrutcure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(ADVANCE_TIM_CH1_PORT ,&GPIO_InitStrutcure);
}

static void ADVANCE_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
    NVIC_InitStructure.NVIC_IRQChannel 					 = ADVANCE_TIM_IRQ; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void ADVANCE_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef 		TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE);
	
	/* 时基单元初始化 */
	TIM_TimeBaseStructure.TIM_Prescaler 		= ADVANCE_TIM_PSC; 	   	// 计数器时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up; 	// 计数模式
	TIM_TimeBaseStructure.TIM_Period 			= ADVANCE_TIM_PERIOD; 	// 自动重装载寄存器
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1; 		// 时钟分频因子
	TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVANCE_TIM_RECNT; 	// 重复计数器
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
	/* 输入捕获IC1初始化（测量周期） */
	TIM_ICInitStructure.TIM_Channel 	= TIM_Channel_1;			// 选择捕获通道1
	TIM_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	// 上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // 直连捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			// 捕获分频因子为1，即不分频
	TIM_ICInitStructure.TIM_ICFilter 	= 0;						// 滤波系数，这里不进行滤波
	TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* 不用初始化IC2 */

	/* 选择输入捕获的触发信号 */
	TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);	
	/* 使能主从模式 */
	TIM_SelectMasterSlaveMode(ADVANCE_TIM, TIM_MasterSlaveMode_Enable); 	
	/* 选择从模式: 复位模式 */
	TIM_SelectSlaveMode(ADVANCE_TIM, TIM_SlaveMode_Reset); 
	// 若输入模式是PWM1，从模式必须工作在复位模式，当捕获开始时，计数器CNT会被复位
	
	/* 使能捕获中断 */
	TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);	
	/* 清除中断标志位 */
	TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);
	/* 使能定时器 */
	TIM_Cmd(ADVANCE_TIM, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
	ADVANCE_TIM_Mode_Config();
}
