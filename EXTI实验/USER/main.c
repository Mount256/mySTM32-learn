#include  "stm32f10x.h"
#include  "led.h"
#include  "delay.h"
#include  "exti_config.h"

int main(void)
{ 
	LED_Init();
	delay_init();
	EXTI_Key_Config();
	EXTI_NVIC_Config();
	
	while(1){}
		
}

