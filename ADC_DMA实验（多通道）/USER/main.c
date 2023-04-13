#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"

extern uint16_t ADC_ConversionValue[5];

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main(void)
{
	uint8_t i = 0;
	float ADC_Result = 0;
	ADC_Init_Config();
	USART_Config();
	printf("\r\nADC_DMA开始测试！！！\r\n");
	
	while(1)
	{
		for(i = 0; i < 4; i++)
		{
			ADC_Result = (float)ADC_ConversionValue[i] / 4096 * 3.30;
			printf("\r\n测试结果%d：%f V (0x%04X)\r\n", i+1, ADC_Result, ADC_ConversionValue[i]);
		}
		Delay(0xffffee); 
		printf("\r\n");
	}
}

