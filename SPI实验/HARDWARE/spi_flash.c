#include "spi_flash.h"

static void SPI_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(FLASH_SPI_GPIO_CLK, ENABLE);
	
	// CS -> PB12
	GPIO_InitStructure.GPIO_Pin 	= FLASH_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);
	
	// SCK -> PB13
	GPIO_InitStructure.GPIO_Pin 	= FLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);
	
	// MISO -> PB14
	GPIO_InitStructure.GPIO_Pin 	= FLASH_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);
	
	// MOSI -> PB15
	GPIO_InitStructure.GPIO_Pin 	= FLASH_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);
}

static void SPI_Mode_Config(void)
{
	SPI_InitTypeDef  SPI_InitStructure; 
	
	RCC_APB1PeriphClockCmd(FLASH_SPI_CLK, ENABLE);
	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  // SCK = f(PCLK)/2
	SPI_InitStructure.SPI_CPHA 			= SPI_CPHA_2Edge; 		// CPHAż������
	SPI_InitStructure.SPI_CPOL 			= SPI_CPOL_High; 		// CPOL����ʱ�ߵ�ƽ��ģʽ3��
	SPI_InitStructure.SPI_CRCPolynomial = 0;					// ��ʹ��CRCУ�飬��ֵ����д
	SPI_InitStructure.SPI_DataSize 		= SPI_DataSize_8b;		// 8λ���ݣ��ɲο�оƬ�����ֲ��ʱ��ͼ��
	SPI_InitStructure.SPI_Direction 	= SPI_Direction_2Lines_FullDuplex; // ˫��ȫ˫��
	SPI_InitStructure.SPI_FirstBit 		= SPI_FirstBit_MSB; 	// ��λ���У��ɲο�оƬ�����ֲ��ʱ��ͼ��
	SPI_InitStructure.SPI_Mode 			= SPI_Mode_Master;		// STM32��Ϊ����
	SPI_InitStructure.SPI_NSS 			= SPI_NSS_Soft; 		// NSS�������������
	
	SPI_Init(FLASH_SPIx, &SPI_InitStructure);
	SPI_Cmd (FLASH_SPIx, ENABLE);
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
}

void SPI_Init_FUN(void)
{
	SPI_GPIO_Config();
	SPI_Mode_Config();
}

/**********************************************/

/* �������Ͳ�����һ�ֽ����� */
static uint8_t SPI_FLASH_Send_Byte(uint8_t data)
{
	// �����ͻ������ǿ�ʱ��ѭ���ȴ�ֱ�����ͻ�����Ϊ��
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET);
	
	// ���ͻ�����Ϊ�գ����Է�������
	SPI_I2S_SendData(FLASH_SPIx, data);
	
	// �����ջ�����Ϊ��ʱ��ѭ���ȴ�ֱ�����ջ������ǿ�
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	
	// ���ջ������ǿգ����Խ�������
	return SPI_I2S_ReceiveData(FLASH_SPIx);
}

/* JEDEC ID */
uint32_t SPI_FLASH_JEDEC_ID(void)
{
	uint32_t FLASH_ID;
	
	FLASH_SPI_CS_LOW; // Ƭѡ�ź�Ϊ�͵�ƽ����ʾ��ѡ��
	
	SPI_FLASH_Send_Byte(JEDEC_ID);
	
	FLASH_ID = SPI_FLASH_Send_Byte(DUMMY);
	FLASH_ID <<= 8; // ����8λ
	
	FLASH_ID |= SPI_FLASH_Send_Byte(DUMMY);
	FLASH_ID <<= 8; // ����8λ
	
	FLASH_ID |= SPI_FLASH_Send_Byte(DUMMY);
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
	
	return FLASH_ID;
}

/* Write Enable */
void SPI_FLASH_Write_Enable(void)
{
	FLASH_SPI_CS_LOW; // Ƭѡ�ź�Ϊ�͵�ƽ����ʾ��ѡ��
	
	SPI_FLASH_Send_Byte(WRITE_ENABLE);
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
}

/* Read Status Register */
void SPI_FLASH_Wait(void)
{
	uint8_t reg = 0;
	
	FLASH_SPI_CS_LOW; // Ƭѡ�ź�Ϊ�͵�ƽ����ʾ��ѡ��
	
	SPI_FLASH_Send_Byte(READ_STATUS_1);
	
	do{
		reg = SPI_FLASH_Send_Byte(DUMMY);
	}while( (reg & 0x01) == 1 );
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
}

/* Sector Erase */
void SPI_FLASH_Sector_Erase(uint32_t addr)
{
	SPI_FLASH_Write_Enable(); // ����дʹ�ܣ�����д��оƬ
	
	FLASH_SPI_CS_LOW; // Ƭѡ�ź�Ϊ�͵�ƽ����ʾ��ѡ��
	
	SPI_FLASH_Send_Byte(SECTOR_ERASE);
	SPI_FLASH_Send_Byte((addr<<16) & 0xFF); // 0xFF������
	SPI_FLASH_Send_Byte((addr<<8)  & 0xFF);
	SPI_FLASH_Send_Byte((addr)     & 0xFF);
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
	
	SPI_FLASH_Wait(); // �ȴ��������
}

/* Page Program */
void SPI_FLASH_Page_Program(uint32_t addr, uint32_t num, uint8_t *data)
{
	SPI_FLASH_Write_Enable(); // ����дʹ�ܣ�����д��оƬ
	
	FLASH_SPI_CS_LOW; // Ƭѡ�ź�Ϊ�͵�ƽ����ʾ��ѡ��
	
	SPI_FLASH_Send_Byte(PAGE_PROGRAM);
	SPI_FLASH_Send_Byte((addr<<16) & 0xFF); // 0xFF������
	SPI_FLASH_Send_Byte((addr<<8)  & 0xFF);
	SPI_FLASH_Send_Byte((addr)     & 0xFF);
	
	while(num--)
	{
		SPI_FLASH_Send_Byte(*data); // �����ֽ�����
		data++; // ָ��ָ����һ�ֽ�����
	}
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
	
	SPI_FLASH_Wait(); // �ȴ�д�����
}

/* Read Data */
void SPI_FLASH_Read_Data(uint32_t addr, uint32_t num, uint8_t *data)
{
	FLASH_SPI_CS_LOW; // Ƭѡ�ź�Ϊ�͵�ƽ����ʾ��ѡ��
	
	SPI_FLASH_Send_Byte(READ_DATA);
	SPI_FLASH_Send_Byte((addr<<16) & 0xFF); // 0xFF������
	SPI_FLASH_Send_Byte((addr<<8)  & 0xFF);
	SPI_FLASH_Send_Byte((addr)     & 0xFF);
	
	while(num--)
	{
		*data = SPI_FLASH_Send_Byte(DUMMY); // �����ֽ�����
		data++; // ׼����һ�ֽڿռ����Խ����µ�����
	}
	
	FLASH_SPI_CS_HIGH; // Ƭѡ�ź�Ϊ�ߵ�ƽ����ʾδѡ��
}
