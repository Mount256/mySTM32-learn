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

// ��ʱ�����벶���û��Զ�������ṹ������
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // ���������־λ
	uint8_t   Capture_StartFlag;    // ����ʼ��־λ
	uint16_t  Capture_CcrValue;     // ����Ĵ�����ֵ
	uint16_t  Capture_Period;       // �Զ���װ�ؼĴ������±�־����¼��ȥ�˶��ٸ���ʱ�����ڣ� 
}TIM_ICUserValueTypeDef;

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;

#endif /* __GENERAL_TIM_H */
