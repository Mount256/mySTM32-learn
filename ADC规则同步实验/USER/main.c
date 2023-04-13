#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"

extern uint32_t ADC_ConversionValue;

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main(void)
{
	float ADC_Result1 = 0, ADC_Result2 = 0;
	ADC_Init_Config();
	USART_Config();
	printf("\r\nADC_DMA��ʼ���ԣ�����\r\n");
	
	while(1)
	{
		ADC_Result1 = (float)( (ADC_ConversionValue & 0xFFFF0000) >> 16) / 4096 * 3.30;	// ��16λ���ݴ���
		ADC_Result2 = (float)    (ADC_ConversionValue & 0xFFFF)      	 / 4096 * 3.30; // ��16λ���ݴ���
		printf("\r\n���Խ��1��%f V (0x%04X)\r\n", ADC_Result1, ADC_ConversionValue);
		printf("\r\n���Խ��2��%f V (0x%04X)\r\n", ADC_Result2, ADC_ConversionValue);
		printf("\r\n");
		Delay(0xffffee); 
	}
}

