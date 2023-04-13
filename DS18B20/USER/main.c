#include "stm32f10x.h"
#include "delay.h"
#include "ds18b20.h"

int main(void)
{	
	delay_init();
	DS18B20_Init();
	while(1)
	{

		if(DS18B20_CheckDevice() == 0)
		{
			DS18B20_GetTemperature();
		}
	}
 }
