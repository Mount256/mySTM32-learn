#ifndef __LCD_1602_H__
#define	__LCD_1602_H__
#include "stm32f10x.h"
#include "delay.h"

#define		POWER_5V0
//#define		POWER_3V3

//IO Definitions
#define		RS		PCout(0)
#define		RW		PCout(1)
#define		EN		PCout(2)

#define		RS_Pin		GPIO_Pin_0
#define		RW_Pin		GPIO_Pin_1
#define		EN_Pin		GPIO_Pin_2

typedef enum
{
	cmd,
	data
}Write_Mode;
extern void LCD1602Configuration(void);
extern void LCD_Show_Str(uint8_t x, uint8_t y, uint8_t *str);
extern void LCD_ClearScreen(void);
#endif

