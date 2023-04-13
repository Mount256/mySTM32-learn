#include "stm32f10x.h"
#include "delay.h"
#include "beep.h"
#include "led.h"

int main(void)
{	
	LED_Init();
	Beep_Init();
	delay_init();
	while(1)
	{
		BEEP_ON;
		LED0_OFF;
		LED1_ON;
		delay_ms(500);
		
		BEEP_OFF;
		LED0_ON;
		LED1_OFF;
		delay_ms(500);
	}
}
