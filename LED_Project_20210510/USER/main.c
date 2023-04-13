#include "stm32f10x.h"
#include "led.h"
#include "delay.h"


void Delay(u32 count)
 {
  uint32_t i=0;
  for(;i<count;i++);
 }


int main(void)
{
	LED_Init();
	
	while(1)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
		GPIO_SetBits(GPIOD, GPIO_Pin_6);
		GPIO_SetBits(GPIOF, GPIO_Pin_6);
		Delay(3000000);
		
		GPIO_SetBits(GPIOD, GPIO_Pin_5);
		GPIO_ResetBits(GPIOD, GPIO_Pin_6);
		GPIO_ResetBits(GPIOF, GPIO_Pin_6);
		Delay(3000000);
	}
	
}
