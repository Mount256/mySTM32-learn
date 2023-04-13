#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
	
	/* KEY0 & KEY1 -- Ground */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4; /* PinE3 -- KEY1, PinE4 -- KEY0 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; /* 上拉输入 */
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* KEY_UP(WK_UP) -- VCC */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; /* PinA0 -- KEY_UP */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /* 下拉输入 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

u8 KEY_Scan(void)
{
	static int isPrsBefore = 0;
	if((isPrsBefore == 0) && (KEY0 == IPU_ON || KEY1 == IPU_ON || KEY_UP == IPD_ON))
	{
		delay_ms(10);
		isPrsBefore = 1;
		if(KEY0 == IPU_ON)
			return KEY0_PRS;
		else if(KEY1 == IPU_ON)
			return KEY1_PRS;
		else if(KEY_UP == IPD_ON)
			return KEY_UP_PRS;
	}else if (KEY0 == !IPU_ON && KEY1 == !IPU_ON && KEY_UP == !IPD_ON)
		isPrsBefore = 0;
	return ALL_KEY_UNPRS; 
}
