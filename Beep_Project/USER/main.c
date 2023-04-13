#include "stm32f10x.h"
#include "delay.h"
#include "beep.h"

int main(void)
{	
	Beep_Init();
	delay_init();
	while(1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		delay_ms(500);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		delay_ms(500);
	}
}
