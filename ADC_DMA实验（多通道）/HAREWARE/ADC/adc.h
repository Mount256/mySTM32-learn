#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

#define ADC_PORT 			GPIOC
#define ADC_PORT_CLK 		RCC_APB2Periph_GPIOC
#define ADC_PIN1			GPIO_Pin_1
#define ADC_PIN2 			GPIO_Pin_2
#define ADC_PIN3 			GPIO_Pin_3
#define ADC_PIN4 			GPIO_Pin_4

#define ADC_x				ADC1
#define ADC_CLK				RCC_APB2Periph_ADC1
#define ADC_CHANNEL1		ADC_Channel_11
#define ADC_CHANNEL2		ADC_Channel_12
#define ADC_CHANNEL3		ADC_Channel_13
#define ADC_CHANNEL4		ADC_Channel_14

#define ADC_DMA_CLK 		RCC_AHBPeriph_DMA1
#define ADC_DMA_CHANNEL		DMA1_Channel1

#define ADC_IRQ				ADC1_2_IRQn
#define ADC_IRQHandler 		ADC1_2_IRQHandler

void ADC_Init_Config(void);

#endif /* __ADC_H */
