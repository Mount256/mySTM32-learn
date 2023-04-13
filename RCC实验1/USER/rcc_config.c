#include "rcc_config.h"
#include "stm32f10x.h"

void HSE_SetSysClk( uint32_t RCC_PLLMul_x )
{
	ErrorStatus HSEStatus;
	
	RCC_DeInit();
	
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if( HSEStatus == SUCCESS )
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		
		RCC_PLLCmd(ENABLE);
		
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		while( RCC_GetSYSCLKSource() != 0x08 );
	}
	else
	{
		//用户在此处添加错误代码
	}
}
