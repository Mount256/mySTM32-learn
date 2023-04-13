#include "stm32f10x.h"
#include "systick.h"
#include "advance_tim.h"

int main(void)
{	
	uint16_t i;
	ADVANCE_TIM_Init();
	while(1)
	{
		for(i = 0; i < 1000; i++)
		{
			TIM_SetCompare1(TIM1, i); // ÉèÖÃCH1Âö³å¿í¶È
			Systick_Delay_us(1500);
		}
		for(i = 999; i > 0; i--)
		{
			TIM_SetCompare1(TIM1, i);
			Systick_Delay_us(1500);
		}
		Systick_Delay_ms(500);
	}
}
