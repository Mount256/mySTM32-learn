#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

#define ADC_PORT 			GPIOC
#define ADC_PORT_CLK 		RCC_APB2Periph_GPIOC
#define ADC_PIN 			GPIO_Pin_1

#define ADC_x				ADC2
#define ADC_CLK				RCC_APB2Periph_ADC2
#define ADC_CHANNEL			ADC_Channel_11

#define ADC_IRQ				ADC1_2_IRQn
#define ADC_IRQHandler 		ADC1_2_IRQHandler

void ADC_Init_Config(void);

#endif /* __ADC_H */
