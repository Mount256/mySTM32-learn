#ifndef  __BASIC_TIM_H
#define  __BASIC_TIM_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"

/****** 基本定时器TIM6、7 ******/
#define BASIC_TIMx				TIM6
#define BASIC_TIMx_CLK			RCC_APB1Periph_TIM6
#define BASIC_TIM_Period    	(1000 - 1)  //自动重装溢出值，必须减1，因为在内部计算时会自动加1
#define BASIC_TIM_Prescaler  	(72 - 1) 	//预分频值，必须减1，因为在内部计算时会自动加1
#define BASIC_TIMx_IRQn  		TIM6_IRQn
#define BASIC_TIMx_IRQHandler   TIM6_IRQHandler

void BASIC_TIM_Config(void);
void BASIC_TIM_NVIC_Config(void);

#endif	 /* __BASIC_TIM_H */
