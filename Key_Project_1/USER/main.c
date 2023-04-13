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
				LED0_ON;
				while(KEY_Scan() != ALL_KEY_UNPRS); /* À… ÷ºÏ≤‚ */
				break;
			case KEY1_PRS:
				LED1_ON;
				while(KEY_Scan() != ALL_KEY_UNPRS);
				break;
			case KEY_UP_PRS:
				BEEP_ON;
				while(KEY_Scan() != ALL_KEY_UNPRS);
				break;
			default:
				LED0_OFF;
				LED1_OFF;
				BEEP_OFF;
				break;
		}
	}
}
