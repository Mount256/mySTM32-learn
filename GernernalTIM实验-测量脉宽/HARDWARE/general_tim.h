#ifndef __GENERAL_TIM_H
#define __GENERAL_TIM_H

#include "stm32f10x.h"

#define GENERAL_TIM  				TIM5
#define GENERAL_TIM_CLK             RCC_APB1Periph_TIM5
#define GENERAL_TIM_PERIOD			0xFFFF  // = 65535
#define GENERAL_TIM_PSC				(72 - 1)
#define GENERAL_TIM_RECNT			0

#define GENERAL_TIM_CH1_PORT_CLK	RCC_APB2Periph_GPIOA
#define GENERAL_TIM_CH1_PORT		GPIOA
#define GENERAL_TIM_CH1_PIN			GPIO_Pin_0
#define GENERAL_TIM_CHANNEL_x		TIM_Channel_1

#define GENERAL_TIM_IRQn			TIM5_IRQn

void GENERAL_TIM_Init(void);

// 定时器输入捕获用户自定义变量结构体声明
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // 捕获结束标志位
	uint8_t   Capture_StartFlag;    // 捕获开始标志位
	uint16_t  Capture_CcrValue;     // 捕获寄存器的值
	uint16_t  Capture_Period;       // 自动重装载寄存器更新标志（记录过去了多少个定时器周期） 
}TIM_ICUserValueTypeDef;

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;

#endif /* __GENERAL_TIM_H */
