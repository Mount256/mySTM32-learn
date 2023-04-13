#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"

extern uint16_t ADC_ConversionValue;

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main(void)
{
	float ADC_Result;
	ADC_Init_Config();
	USART_Config();
	printf("\r\n开始测试！！！\r\n");
	
	while(1)
	{
		ADC_Result = (float)ADC_ConversionValue / 4096 * 3.30;
		printf("\r\n测试结果：%f V (0x%04X)\r\n", ADC_Result, ADC_ConversionValue);
		Delay(0xffffee); 
	}
}

