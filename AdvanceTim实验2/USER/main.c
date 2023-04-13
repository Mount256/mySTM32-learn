#include "stm32f10x.h"
#include "systick.h"
#include "advance_tim.h"
#include "general_tim.h"
#include "usart.h"

int main(void)
{	
	USART_Config();
	printf("\r\n¿ªÊ¼²âÊÔ£¡\r\n");
	GENERAL_TIM_Init();
	ADVANCE_TIM_Init();
	while(1)
	{
		
	}
}
