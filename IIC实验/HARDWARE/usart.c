#include "usart.h"


void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	// USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// USART1-TX���� GPIOA.9 ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = USART1_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);
	
	// USART1-RX���� GPIOA.10 ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = USART1_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ����USART1���ڲ���
	USART_InitStructure.USART_BaudRate = USART_BAUDRATE;			// ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// ���������ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// ����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				// ����У��λ
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	// ���ù���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // ����Ӳ��������
	USART_Init(USART1, &USART_InitStructure);						// ��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);	 									// ʹ�ܴ���
}


// ���ڷ���һ���ֽ�
void USART_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

// ���ڷ��������ֽ�
void USART_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data)
{
	uint8_t temp_h, temp_l;
	temp_h = (data & 0xFF00) >> 8;
	temp_l = data & 0x00FF;
	
	USART_SendData(pUSARTx, temp_h);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	USART_SendData(pUSARTx, temp_l);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

// ���ڷ���8λ���ݵ�����
void USART_SendArray(USART_TypeDef* pUSARTx, uint8_t* Array, uint8_t num)
{
	uint8_t i;
	for( i = 0; i < num; i++)
	{
		USART_SendData(pUSARTx, Array[i]);
		while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	}
}

// ���ڷ����ַ���
void USART_SendStr(USART_TypeDef* pUSARTx, uint8_t* str)
{
	while( *(str) != '\0')
	{
		USART_SendData(pUSARTx, *(str++));
		while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	}
}


//�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf��putchar����
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(USART1, (uint8_t)ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
	return (ch);
}

//�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar����
int fgetc(FILE *f)
{
	/* �ȴ������������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}
