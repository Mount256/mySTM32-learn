#include "lcd.h"

void LCD_Wait_Ready(void)
{
	uint8_t status;
	
	GPIOD->ODR = 0xFF;
	RS = 0;
	RW = 1;
	do
	{
		EN = 1;
		delay_ms(5);
		status = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
		EN = 0;
	}while(status & 0x80);
}

void LCD_Write_Cmd(uint8_t cmd)
{
	LCD_Wait_Ready();
	RS = 0;
	RW = 0;
	GPIOD->ODR = cmd;
	EN = 1;
	EN = 0;
}

void LCD_Write_Dat(uint8_t dat)
{
	LCD_Wait_Ready();
	RS = 1;
	RW = 0;
	GPIOD->ODR = dat; 
	EN = 1;
	EN = 0;
}

void LCD_ClearScreen(void)
{
	LCD_Write_Cmd(0x01);
}

void LCD_Set_Cursor(uint8_t x, uint8_t y)
{
	uint8_t addr;
	
	if (y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD_Write_Cmd(addr | 0x80);
}

void LCD_Show_Str(uint8_t x, uint8_t y, uint8_t *str)
{
	LCD_Set_Cursor(x, y);
	while(*str != '\0')
	{
		LCD_Write_Dat(*str++);
	}
}

void LCD1602Configuration(void)
{
	GPIO_InitTypeDef    GPIO;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC, ENABLE);
    
    //Control IO 
    GPIO.GPIO_Pin   = RS_Pin | RW_Pin | EN_Pin;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	
#if defined (POWER_3V3)
	GPIO.GPIO_Mode  = GPIO_Mode_Out_PP;
#elif defined (POWER_5V0)
    GPIO.GPIO_Mode  = GPIO_Mode_Out_OD;
#endif
	
    GPIO_Init(GPIOC, &GPIO);
   
	//Data Port IO, PD0 ~ PD7
	GPIO.GPIO_Pin   = 0xFF;
	GPIO_Init(GPIOD, &GPIO);
	
	delay_ms(15);
	LCD_Write_Cmd(0x38);	//16*2显示，5*7点阵，8位数据口
	delay_ms(5);
	LCD_Write_Cmd(0x38);	//16*2显示，5*7点阵，8位数据口
	delay_ms(5);
	LCD_Write_Cmd(0x38);	//16*2显示，5*7点阵，8位数据口
	delay_ms(5);
	LCD_Write_Cmd(0x0c);	//开显示，光标关闭
	LCD_Write_Cmd(0x06);	//文字不动，地址自动+1
	LCD_Write_Cmd(0x01);	//清屏
}

