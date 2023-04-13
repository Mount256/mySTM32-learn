#ifndef __ADVANCE_TIM_H
#define __ADVANCE_TIM_H

#include "stm32f10x.h"

#define ADVANCE_TIM					TIM1

#define ADVANCE_TIM_CLK				RCC_APB2Periph_TIM1
#define ADVANCE_TIM_PERIOD			(1000 - 1)  	// ��װ��ֵ��1000us
#define ADVANCE_TIM_PSC				(72 - 1)  	// ��Ƶ��72���õ����ڣ�1us
#define ADVANCE_TIM_CCR1			5			// ��ʼ�����ȣ�5us
#define ADVANCE_TIM_RECNT			0

#define ADVANCE_TIM_CH1_PORT_CLK	RCC_APB2Periph_GPIOA
#define ADVANCE_TIM_CH1_PORT		GPIOA
#define ADVANCE_TIM_CH1_PIN			GPIO_Pin_8

#define ADVANCE_TIM_CH1N_PORT_CLK	RCC_APB2Periph_GPIOB
#define ADVANCE_TIM_CH1N_PORT		GPIOB
#define ADVANCE_TIM_CH1N_PIN		GPIO_Pin_13

#define ADVANCE_TIM_BKIN_PORT_CLK	RCC_APB2Periph_GPIOB
#define ADVANCE_TIM_BKIN_PORT		GPIOB
#define ADVANCE_TIM_BKIN_PIN		GPIO_Pin_12
#define ADVANCE_TIM_DEAD_TIME		11

void ADVANCE_TIM_Init(void);

#endif /* __ADVANCE_TIM_H */
