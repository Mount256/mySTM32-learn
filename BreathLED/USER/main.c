#include "stm32f10x.h"
#include "systick.h"
#include "led.h"

int main(void)
{	
	uint16_t i = 0;
	uint16_t num = 1500;
	LED_Init();
	while(1)
	{
		for(i = 0; i < num; i++)
		{
			LED0_ON;
			Systick_Delay_us(i);
			LED0_OFF;
			Systick_Delay_us(num - i);
		}
		for(i = num; i > 0; i--)
		{
			LED0_ON;
			Systick_Delay_us(i);
			LED0_OFF;
			Systick_Delay_us(num - i);
		}
	}
}
