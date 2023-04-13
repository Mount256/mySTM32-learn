#include "stm32f10x.h"
#include "sys.h"
#include "beep.h"
#include "key.h"
#include "led.h"
#include "delay.h"

int main()
{
	u8 key = 0;
	delay_init();
	KEY_Init();
	LED_Init();
	Beep_Init();
	while(1)
	{
		key = KEY_Scan();
		switch(key)
		{
			case KEY0_PRS:
				LED0 = !LED0;
				break;
			case KEY1_PRS:
				LED1 = !LED1;
				break;
			case KEY_UP_PRS:
				BEEP = !BEEP;
				break;
			default:
				break;
		}
	}
}
