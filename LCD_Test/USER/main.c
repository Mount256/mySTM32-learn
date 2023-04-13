#include "stm32f10x.h"
#include "lcd.h"

int main(void)
{	
	u8 str[] = "abcdef";
	LCD_init();
	Show_Str(1, 2, str);
	while(1)
	{
	
	}
 }
