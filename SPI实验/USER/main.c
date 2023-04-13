#include "stm32f10x.h"
#include "spi_flash.h"
#include "usart.h"

int main(void)
{	
	uint32_t id, i;
	uint8_t array_write[100], array_read[100];
	
	USART_Config();
	printf("\r\nSPI��дFlash��ʼ���ԣ�����\r\n");
	
	SPI_Init_FUN();
	id = SPI_FLASH_JEDEC_ID();
	printf("\r\n Flash ID = 0x%x \r\n", id);
	
	SPI_FLASH_Sector_Erase(0x000000);
	printf("\r\n Flashĳ�����Ѳ�����ϣ�����\r\n");
	
	for(i = 0; i < 25; i++)
		array_write[i] = i + 15;
	SPI_FLASH_Page_Program(0x000000, 25, array_write);
	printf("\r\n����д����ϣ�����\r\n");
	
	SPI_FLASH_Read_Data(0x000000, 100, array_read); //error
	printf("\r\n��ȡ�������£�\r\n");
	for(i = 0; i < 100; i++)
	{
		printf("0x%x ", array_read[i]);
		if(i % 10 == 0)
			printf("\r\n");
	}
	
	while(1)
	{
		//...	
	}
 }

 /*************** END OF FILE **************/
