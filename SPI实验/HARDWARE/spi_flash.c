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
	SPI_InitStructure.SPI_CPHA 			= SPI_CPHA_2Edge; 		// CPHA偶数边沿
	SPI_InitStructure.SPI_CPOL 			= SPI_CPOL_High; 		// CPOL空闲时高电平（模式3）
	SPI_InitStructure.SPI_CRCPolynomial = 0;					// 不使用CRC校验，数值随意写
	SPI_InitStructure.SPI_DataSize 		= SPI_DataSize_8b;		// 8位数据（可参考芯片数据手册的时序图）
	SPI_InitStructure.SPI_Direction 	= SPI_Direction_2Lines_FullDuplex; // 双线全双工
	SPI_InitStructure.SPI_FirstBit 		= SPI_FirstBit_MSB; 	// 高位先行（可参考芯片数据手册的时序图）
	SPI_InitStructure.SPI_Mode 			= SPI_Mode_Master;		// STM32作为主机
	SPI_InitStructure.SPI_NSS 			= SPI_NSS_Soft; 		// NSS引脚由软件控制
	
	SPI_Init(FLASH_SPIx, &SPI_InitStructure);
	SPI_Cmd (FLASH_SPIx, ENABLE);
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
}

void SPI_Init_FUN(void)
{
	SPI_GPIO_Config();
	SPI_Mode_Config();
}

/**********************************************/

/* 主机发送并接收一字节数据 */
static uint8_t SPI_FLASH_Send_Byte(uint8_t data)
{
	// 当发送缓冲区非空时，循环等待直至发送缓冲区为空
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET);
	
	// 发送缓冲区为空，可以发送数据
	SPI_I2S_SendData(FLASH_SPIx, data);
	
	// 当接收缓冲区为空时，循环等待直至接收缓冲区非空
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	
	// 接收缓冲区非空，可以接收数据
	return SPI_I2S_ReceiveData(FLASH_SPIx);
}

/* JEDEC ID */
uint32_t SPI_FLASH_JEDEC_ID(void)
{
	uint32_t FLASH_ID;
	
	FLASH_SPI_CS_LOW; // 片选信号为低电平，表示已选中
	
	SPI_FLASH_Send_Byte(JEDEC_ID);
	
	FLASH_ID = SPI_FLASH_Send_Byte(DUMMY);
	FLASH_ID <<= 8; // 左移8位
	
	FLASH_ID |= SPI_FLASH_Send_Byte(DUMMY);
	FLASH_ID <<= 8; // 左移8位
	
	FLASH_ID |= SPI_FLASH_Send_Byte(DUMMY);
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
	
	return FLASH_ID;
}

/* Write Enable */
void SPI_FLASH_Write_Enable(void)
{
	FLASH_SPI_CS_LOW; // 片选信号为低电平，表示已选中
	
	SPI_FLASH_Send_Byte(WRITE_ENABLE);
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
}

/* Read Status Register */
void SPI_FLASH_Wait(void)
{
	uint8_t reg = 0;
	
	FLASH_SPI_CS_LOW; // 片选信号为低电平，表示已选中
	
	SPI_FLASH_Send_Byte(READ_STATUS_1);
	
	do{
		reg = SPI_FLASH_Send_Byte(DUMMY);
	}while( (reg & 0x01) == 1 );
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
}

/* Sector Erase */
void SPI_FLASH_Sector_Erase(uint32_t addr)
{
	SPI_FLASH_Write_Enable(); // 开启写使能，允许写入芯片
	
	FLASH_SPI_CS_LOW; // 片选信号为低电平，表示已选中
	
	SPI_FLASH_Send_Byte(SECTOR_ERASE);
	SPI_FLASH_Send_Byte((addr<<16) & 0xFF); // 0xFF：掩码
	SPI_FLASH_Send_Byte((addr<<8)  & 0xFF);
	SPI_FLASH_Send_Byte((addr)     & 0xFF);
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
	
	SPI_FLASH_Wait(); // 等待擦除完毕
}

/* Page Program */
void SPI_FLASH_Page_Program(uint32_t addr, uint32_t num, uint8_t *data)
{
	SPI_FLASH_Write_Enable(); // 开启写使能，允许写入芯片
	
	FLASH_SPI_CS_LOW; // 片选信号为低电平，表示已选中
	
	SPI_FLASH_Send_Byte(PAGE_PROGRAM);
	SPI_FLASH_Send_Byte((addr<<16) & 0xFF); // 0xFF：掩码
	SPI_FLASH_Send_Byte((addr<<8)  & 0xFF);
	SPI_FLASH_Send_Byte((addr)     & 0xFF);
	
	while(num--)
	{
		SPI_FLASH_Send_Byte(*data); // 传送字节数据
		data++; // 指针指向下一字节数据
	}
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
	
	SPI_FLASH_Wait(); // 等待写入完毕
}

/* Read Data */
void SPI_FLASH_Read_Data(uint32_t addr, uint32_t num, uint8_t *data)
{
	FLASH_SPI_CS_LOW; // 片选信号为低电平，表示已选中
	
	SPI_FLASH_Send_Byte(READ_DATA);
	SPI_FLASH_Send_Byte((addr<<16) & 0xFF); // 0xFF：掩码
	SPI_FLASH_Send_Byte((addr<<8)  & 0xFF);
	SPI_FLASH_Send_Byte((addr)     & 0xFF);
	
	while(num--)
	{
		*data = SPI_FLASH_Send_Byte(DUMMY); // 接收字节数据
		data++; // 准备下一字节空间用以接收新的数据
	}
	
	FLASH_SPI_CS_HIGH; // 片选信号为高电平，表示未选中
}
