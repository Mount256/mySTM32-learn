#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "delay.h"

int main(void)
{	
	//uint8_t array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	uint8_t ch;
	USART_Config();
	//NVIC_Config();
	LED_Init();
	delay_init();

	while(1)
	{
		//USART_SendByte(USART1, 0x34);
		//USART_SendHalfWord(USART1, 0xFF56);
		//USART_SendArray(USART1, array, 10);
		//USART_SendStr(USART1, "���Ĳ���\n");
		printf("����Զϲ�������ȣ�����\n");
		putchar('A');
		//delay_ms(1000);
		
		ch = getchar();
		printf("��ѡ����%c�ƣ�\n", ch);
		switch(ch)
		{
			case '1':
				LED0 = !LED0;
				break;
			case '2':
				LED1 = !LED1;
				break;
			default:
				printf("�����������������룡\n");
				break;
		}
		
	}
}
