#include "stm32f10x.h"
#include  "led.h"
#include "rcc_config.h"

void delay( uint32_t count)
{
	for(; count != 0; count--);
}

int main(void)
{
 
HSE_SetSysClk(RCC_PLLMul_12);
LED_Init();

while(1){

	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	delay(0xFFFFF);

	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	delay(0xFFFFF);

}
}

