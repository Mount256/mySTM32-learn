#include "stm32f10x.h"
#include "dma.h"
#include "usart.h"
#include "led.h"
#include "delay.h"

#define M2M

extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];
extern uint8_t SendBuffer[SENDBUFFER_SIZE];

int main(void)
{	
	#ifdef M2M  // ´æ´¢Æ÷->´æ´¢Æ÷
	
	uint8_t status = 0;
	delay_init();
	M2M_DMA_Config();
	
	LED_Init();
	LED0_ON;
	LED1_OFF;
	delay_ms(500);
	
	while( DMA_GetFlagStatus(DMA1_FLAG_TC6) == RESET );
	status = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	if(status == 0)
	{
		LED0_ON;
		LED1_OFF;
	}
	else
	{
		LED0_OFF;
		LED1_ON;
	}
	
	#else // ´æ´¢Æ÷ -> USART
	
	uint16_t i = 0;
	delay_init();		
	LED_Init();
	
	for(i = 0; i < SENDBUFFER_SIZE; i++)
	{
		SendBuffer[i] = 'p';
	}
	
	USART_Config();
	USART_DMA_Config();
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	while(1)
	{
		LED1 = !LED1;
		delay_ms(500);
	}
	
	#endif
}
