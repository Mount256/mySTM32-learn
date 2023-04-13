#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f10x.h"
#include "sys.h"
 
#define DS18B20_OutPut_Mode() {GPIOB->CRL &= 0x0FFFFFFF;GPIOB->CRL |= 0x30000000;}
#define DS18B20_InPut_Mode()  {GPIOB->CRL &= 0x0FFFFFFF;GPIOB->CRL |= 0x80000000;}
 
#define DS18B20_IN  PBin(7)
#define DS18B20_OUT PBout(7)
 
extern u8 Refresh_OLED_Data;
 
void DS18B20_Init(void);
u8 DS18B20_CheckDevice(void);
void DS18B20_SendRestSingle(void);
u8 DS18B20_CheckReadySingle(void);
u8 BS18B20_WriteByte(u8 cmd);
u8 BS18B20_ReadByte(void);
u16 DS18B20_GetTemperature(void);
u8 DS18B20_ReadRomInfo(void);
u8 DS18B20_MatchROM(void);

#endif /* __DS18B20_H */
