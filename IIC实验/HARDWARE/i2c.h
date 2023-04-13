#ifndef  __I2C_H
#define  __I2C_H
#include "stm32f10x.h"

/****** ѡ��ʹ�ã�I2C1 ******/

/******  �궨����  ******/
#define I2C_CLK_SPEED	400000

/* STM32�豸��ַ�����ⶨ�壬ֻҪ��EEPROM��ַ���غϼ��� */
#define STM32_ADDR 		0x5F
#define EEPROM_ADDR   	0xA0

#define SCL_PORT_CLK 	RCC_APB2Periph_GPIOB
#define SDA_PORT_CLK 	RCC_APB2Periph_GPIOB
#define I2Cx_CLK		RCC_APB1Periph_I2C1

#define I2Cx			I2C1
#define SCL_GPIO_PORT   GPIOB
#define SDA_GPIO_PORT   GPIOB
#define SCL_GPIO_PIN	GPIO_Pin_6
#define SDA_GPIO_PIN	GPIO_Pin_7

/******  ����������  ******/
void I2C_Config(void);

void EEPROM_ByteWrite(uint8_t addr, uint8_t data);
void EEPROM_PageWrite(uint8_t addr, uint8_t *data, uint8_t num);

void EEPROM_RandomRead(uint8_t addr, uint8_t* data);
void EEPROM_SeqRead(uint8_t addr, uint8_t* data, uint8_t num);

void EEPROM_WaitForWriteEnd(void);

#endif /* __I2C_H */
