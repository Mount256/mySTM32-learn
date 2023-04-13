/*mian Ö÷º¯Êý*/
#include "Systick.h"
#include "1602.h"
 
int main(void)
{
	u8 str[] = "ATOM@ALIENTEK";
	
	GPIO_Configuration();
	LCD1602_Init();
	LCD1602_ClearScreen();
	LCD1602_Show_Str(2, 0, str);     
 	//LCD1602_Show_Str(2, 1, "I love STM32");
	
}
