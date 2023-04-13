#ifndef     __LCD_H__
#define     __LCD_H__
#include "stm32f10x.h"
 
#define LED0 PBout(5)
#define LED1 PEout(5)
#define RS PCout(0)
#define RW PCout(1)
#define EN PCout(2)
 
void LCD_init(void);
void Wcmd(u8 cmd);
void Wdat(u8 dat);
void Set_Cursor(u8 x, u8 y);
void Show_Str(u8 x, u8 y, u8 *str);
 
#endif
