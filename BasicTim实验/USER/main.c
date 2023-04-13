#include "stm32f10x.h"
#include "led.h"
#include "basic_tim.h"

volatile uint16_t time = 0;

int main(void)
{	
	LED_Init();
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Config();
	
	while(1)
	{
		if(time == 1000)
		{
			time = 0;
			LED0 = !LED0;
		}
	}
}
