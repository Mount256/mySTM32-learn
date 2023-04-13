#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

/*
void Delay(u32 count)
 {
  u32 i=0;
  for(;i<count;i++);
 }
*/

int main(void)
{
	delay_init();
	LED_Init();
	
	while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		GPIO_SetBits(GPIOE, GPIO_Pin_5);
		delay_ms(500);
		//Delay(3000000);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		delay_ms(500);
		//Delay(3000000);
	}
	
}
