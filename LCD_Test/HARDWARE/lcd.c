 #include "sys.h"
#include "lcd.h"
#include "delay.h"
 
 
//发送命令
void Wcmd(u8 cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	GPIO_Write(GPIOD,(GPIO_ReadOutputData(GPIOD) & 0xff00) | cmd);
	delay_ms(10);
	EN = 0;
}
//发送数据
void Wdat(u8 dat)
{
	RS = 1;
	RW = 0;
	EN = 1;
	GPIO_Write(GPIOD,(GPIO_ReadOutputData(GPIOD) & 0xff00) | dat);
	delay_ms(10);
	EN = 0;
}
//
void LCD_init()
{
	GPIO_InitTypeDef  GPIO_Initlcd;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//
	
	GPIO_Initlcd.GPIO_Mode=GPIO_Mode_Out_PP;    //设置工作模式
	GPIO_Initlcd.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 
							| GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_Initlcd.GPIO_Speed=GPIO_Speed_50MHz;   //选择工作频率
	GPIO_Init(GPIOD,&GPIO_Initlcd);             //控制寄存器写入
	
	GPIO_Initlcd.GPIO_Mode=GPIO_Mode_Out_PP;    //设置工作模式
	GPIO_Initlcd.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;  //选定引脚
	GPIO_Initlcd.GPIO_Speed=GPIO_Speed_50MHz;   //选择工作频率
	GPIO_Init(GPIOC,&GPIO_Initlcd);
	
	Wcmd(0x38); //功能设置
	delay_ms(5);
	Wcmd(0x38); //功能设置
	delay_ms(5);
	Wcmd(0x38); //功能设置
	delay_ms(5);
	Wcmd(0x08);
	Wcmd(0x01); //清屏
	Wcmd(0x06); //设置输入模式
	Wcmd(0x0C); //显示设置
	Wcmd(0x02); //光标归位
	
}

void Set_Cursor(u8 x, u8 y)
{
        u16 addr;
         
         if (y == 0)
                addr = 0x0000 + (x<<8);
         else
                 addr = 0x4000 + (x<<8);
         Wcmd(addr | 0x8000);
}

void Show_Str(u8 x, u8 y, u8 *str)
{
         Set_Cursor(x, y);
         while(*str != '\0')
         {
                 Wdat(*str++);
         }
}
