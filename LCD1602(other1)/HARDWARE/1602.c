/*
        1602.C�ļ�
	1602�������ߴ���
*/
#include "1602.h"
#include "systick.h"
 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//��ʱ��
       //dataIO GPIOD4~7 ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);				
        // RS RW E IO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);				
}
 
/* ���Һ��æ��æ */
void LCD1602_Wait_Ready(void)
{
	int8_t sta;
	
	DATAOUT(0xff);    //PD�˿�ȫ����1
	LCD_RS_Clr();     //RS 0
	LCD_RW_Set();     //RW 1
	do
	{
		LCD_EN_Set();   //EN 1
		SysTick_Delay_Ms(5);	//��ʱ5MS
 		sta = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);//��ȡ״̬��
		LCD_EN_Clr();  //EN  0
	}while(sta & 0x80);//bit7����1��ʾæ,�ظ���⵽��Ϊ0ֹͣ
}
 
/*��1602д��һ�ֽ�����,cmd-��д������ */
//д��ָ��PA4-7 RS-0  RW-0
void LCD1602_Write_Cmd(u8 cmd)
{
	LCD1602_Wait_Ready();  //�ж�æ��æ
	LCD_RS_Clr();   
	LCD_RW_Clr();
	DATAOUT(cmd);  //�ȴ�����λ
	LCD_EN_Set();
	LCD_EN_Clr();
	
	DATAOUT(cmd<<4); //����λ���Ƶ�����λ
	LCD_EN_Set();
	LCD_EN_Clr();
}
 
/* ��1602д��һ�ֽ�����*/
void LCD1602_Write_Dat(u8 dat)
{
	LCD1602_Wait_Ready(); //�ж�æ��æ
	LCD_RS_Set();   //1
	LCD_RW_Clr();   //0
	
	DATAOUT(dat);   //�ȴ�����λ
	LCD_EN_Set();  
	LCD_EN_Clr();
	
	DATAOUT(dat<<4); //����λ���Ƶ�����λ
	LCD_EN_Set(); 
	LCD_EN_Clr();
	
}
 
/*����*/
void LCD1602_ClearScreen(void)
{
	LCD1602_Write_Cmd(0x01);
	
}
 
/* ����RAM��ʵ��ַ,�����λ��,��X,Y����Ӧ��Ļ�ϵ��ַ����� */
void LCD1602_Set_Cursor(u8 x, u8 y)
{
	u8 addr;
	
	if (y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_Write_Cmd(addr | 0x80);
}
 
/* ��Һ������ʾ�ַ���,��X,Y��-��Ӧ��Ļ�ϵ���ʵ���꣬str-�ַ���ָ�� */
void LCD1602_Show_Str(u8 x, u8 y, u8 *str)
{
	LCD1602_Set_Cursor(x, y);
	while(*str != '\0')
	{
		LCD1602_Write_Dat(*str++);
	}
}
 
/* ��ʼ��Һ�� */
void LCD1602_Init(void)
{
	LCD1602_Write_Cmd(0x28);	//16*2��ʾ��5*7����4λ���ݿ�
	LCD1602_Write_Cmd(0x0C);	//����ʾ�����ر�
	LCD1602_Write_Cmd(0x06);	//���ֲ�������ַ�Զ�+1
	LCD1602_Write_Cmd(0x01);	//����
}
