#ifndef __BEEP_H
#define __BEEP_H

#define BEEP_ON GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define BEEP_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_8)

void Beep_Init(void);

#endif
