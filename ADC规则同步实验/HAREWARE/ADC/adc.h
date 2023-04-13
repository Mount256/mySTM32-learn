#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

/*******双ADC规则同步实验*******/

#define ADC_PORT 			GPIOC
#define ADC_PORT_CLK 		RCC_APB2Periph_GPIOC
#define ADC_PIN1			GPIO_Pin_1
#define ADC_PIN2 			GPIO_Pin_2
#define ADC_PIN3 			GPIO_Pin_3
#define ADC_PIN4 			GPIO_Pin_4

#define ADC_DMA_CLK 		RCC_AHBPeriph_DMA1
#define ADC_DMA_CHANNEL		DMA1_Channel1

void ADC_Init_Config(void);

#endif /* __ADC_H */
