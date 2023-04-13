#include "stm32f10x.h"
#include "usart.h"
#include "i2c.h"
#include "led.h"

uint8_t data = 45;
uint8_t data_a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
uint8_t data_rec = 0;
uint8_t data_rec_a[8] = {0};
uint8_t addr = 8;

int main(void)
{		
	uint8_t i;
	LED_Init();
	USART_Config();
	I2C_Config();
	
	LED0_ON;
	LED1_OFF;
	printf("这是一个IIC通讯实验\n");
	
	//EEPROM_ByteWrite(addr, data);
	EEPROM_PageWrite(addr, data_a, 4);
	
	EEPROM_WaitForWriteEnd();
	//EEPROM_RandomRead(addr, &data_rec);
	
	EEPROM_SeqRead(addr, data_rec_a, 4);
	
	//printf("发送和接收成功！数据为：%d\n", data_rec);
	for(i = 0; i < 8; i++)
	{
		printf("%d  \n", data_rec_a[i]);
	}
	
	LED0_OFF;
	LED1_ON;
	
	while(1)
	{
		
	}
}
