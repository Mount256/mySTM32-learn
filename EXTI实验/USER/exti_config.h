#ifndef __EXTI_CONFIG_H
#define __EXTI_CONFIG_H

#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)

void EXTI_Key_Config(void);
void EXTI_NVIC_Config(void);

#endif /* __EXTI_CONFIG_H */
