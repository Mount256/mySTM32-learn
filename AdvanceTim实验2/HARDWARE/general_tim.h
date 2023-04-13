#ifndef __GENERAL_TIM_H
#define __GENERAL_TIM_H

#include "stm32f10x.h"

/*******ͨ�ö�ʱ��TIMx����Ƚ�******/
#define GENERAL_TIM  				TIM3
#define GENERAL_TIM_CLK             RCC_APB1Periph_TIM3
#define GENERAL_TIM_PERIOD			(100 - 1) 	// 100 * 1us = 100us, T = 1 / 10^(-4) = 10^4Hz = 10000Hz
#define GENERAL_TIM_PSC				(72 - 1) 	// 1us
#define GENERAL_TIM_RECNT			0

#define GENERAL_TIM_CH1_PORT_CLK	RCC_APB2Periph_GPIOA
#define GENERAL_TIM_CH1_PORT		GPIOA
#define GENERAL_TIM_CH1_PIN			GPIO_Pin_6
#define GENERAL_TIM_CCR1			10			// ռ�ձȣ�10%

#define GENERAL_TIM_CH2_PORT_CLK	RCC_APB2Periph_GPIOA
#define GENERAL_TIM_CH2_PORT		GPIOA
#define GENERAL_TIM_CH2_PIN			GPIO_Pin_7
#define GENERAL_TIM_CCR2			25			// ռ�ձȣ�25%

#define GENERAL_TIM_CH3_PORT_CLK	RCC_APB2Periph_GPIOB
#define GENERAL_TIM_CH3_PORT		GPIOB
#define GENERAL_TIM_CH3_PIN			GPIO_Pin_0
#define GENERAL_TIM_CCR3			50			// ռ�ձȣ�50%

#define GENERAL_TIM_CH4_PORT_CLK	RCC_APB2Periph_GPIOB
#define GENERAL_TIM_CH4_PORT		GPIOB
#define GENERAL_TIM_CH4_PIN			GPIO_Pin_1
#define GENERAL_TIM_CCR4			75			// ռ�ձȣ�75%

void GENERAL_TIM_Init(void);

#endif /* __GENERAL_TIM_H */
