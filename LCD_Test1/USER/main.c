#include "stm32f10x.h"
#include "lcd.h"

int main(void)
{	
	u8 str[] = "abcdef";
	LCD1602Configuration();
	LCD_Show_Str(1, 0, str);
	while(1)
	{
	
	}
 }
