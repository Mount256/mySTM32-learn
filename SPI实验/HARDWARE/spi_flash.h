#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f10x.h"

/*********** Definition ***********/

#define FLASH_SPIx 				SPI2

#define FLASH_SPI_CLK 			RCC_APB1Periph_SPI2
#define FLASH_SPI_GPIO_CLK 		RCC_APB2Periph_GPIOB

#define FLASH_SPI_CS_PORT 		GPIOB
#define FLASH_SPI_CS_PIN 		GPIO_Pin_12

#define FLASH_SPI_SCK_PORT 		GPIOB
#define FLASH_SPI_SCK_PIN 		GPIO_Pin_13

#define FLASH_SPI_MISO_PORT 	GPIOB
#define FLASH_SPI_MISO_PIN 		GPIO_Pin_14

#define FLASH_SPI_MOSI_PORT 	GPIOB
#define FLASH_SPI_MOSI_PIN 		GPIO_Pin_15

#define FLASH_SPI_CS_HIGH  		GPIO_SetBits  (FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN)
#define FLASH_SPI_CS_LOW 		GPIO_ResetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN)

/*********** Function Declaration ***********/

void SPI_Init_FUN(void);  					// 初始化SPI
uint32_t SPI_FLASH_JEDEC_ID(void);			// 读取Flash的ID号
void SPI_FLASH_Sector_Erase(uint32_t addr); // 擦除Flash扇区
void SPI_FLASH_Write_Enable(void);			// 读写使能
void SPI_FLASH_Wait(void);					// 等待写/读/擦除操作完毕
void SPI_FLASH_Sector_Erase(uint32_t addr); // 擦除指定扇区
void SPI_FLASH_Page_Program(uint32_t addr, uint32_t num, uint8_t *data); // 写入数据
void SPI_FLASH_Read_Data(uint32_t addr, uint32_t num, uint8_t *data); // 读取数据

/************** Instructions ****************/

#define DUMMY 			0x00
#define JEDEC_ID 		0x9F
#define WRITE_ENABLE	0x06
#define READ_STATUS_1	0x05
#define READ_STATUS_2	0x35
#define SECTOR_ERASE 	0x20
#define PAGE_PROGRAM 	0x02
#define READ_DATA		0x03

#endif  /* __SPI_FLASH_H */
