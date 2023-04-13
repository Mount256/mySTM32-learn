#include "systick.h"

void Systick_Delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	
	for( i = 0; i < us; i++)
	{
		while( !((SysTick -> CTRL) & (1 << 16)) );
	}
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	
}

void Systick_Delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	
	for( i = 0; i < ms; i++)
	{
		while( !((SysTick -> CTRL) & (1 << 16)) );
	}
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	
}

/* use interrupt */
__IO uint32_t TimingDelay;

void SysTick_Init(void)
{
	if(SysTick_Config(72000) == 1)
    {
       while(1);
    }
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(uint32_t ms)
{
	TimingDelay = ms;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay != 0);
}

/*
void timeDec(void)
{
	if(TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}
*/
