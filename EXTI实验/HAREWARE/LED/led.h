#ifndef __LED_H
#define __LED_H

#define LED0_OFF GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED0_ON GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LED1_OFF GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define LED1_ON GPIO_ResetBits(GPIOE, GPIO_Pin_5)

#define LED0 PBout(5) 
#define LED1 PEout(5)

void LED_Init(void);

#endif


