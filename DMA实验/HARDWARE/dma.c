#include "dma.h"
#include "usart.h"

const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};

uint32_t aDST_Buffer[BUFFER_SIZE];
uint8_t  SendBuffer[SENDBUFFER_SIZE];

//M2M							
void M2M_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	/* 1. 配置DMA时钟（AHB总线）*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* 2. 设置外设基地址 */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
	/* 3. 设置存储器基地址 */
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	/* 4. 设置传输方向 */
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	/* 5. 设置传输数目 */
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	/* 6. 设置外设地址访问是否为增量模式 */
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	/* 7. 设置存储器地址访问是否为增量模式 */
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/* 8. 设置外设数据宽度 */
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	/* 9. 设置存储器数据宽度 */
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	/* 10. 设置工作模式 */
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	/* 11. 配置DMA优先级 */
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* 12. 配置是否为M2M模式 */
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	
	/* 13. 初始化DMA通道 */
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	/* 14. 清除发送标志 */
	DMA_ClearFlag(DMA1_FLAG_TC6);
	/* 15. 使能DMA通道 */
	DMA_Cmd(DMA1_Channel6, ENABLE);
}

//M2P
void USART_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)USART1_DR_ADDRESS;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
	DMA_InitStructure.DMA_BufferSize = SENDBUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	DMA_ClearFlag(DMA1_FLAG_TC4);
	DMA_Cmd(DMA1_Channel4, ENABLE);
}

/* 比较是否一致 */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* 数据长度递减 */
  while(BufferLength--)
  {
    /* 判断两个数据源是否对应相等 */
    if(*pBuffer != *pBuffer1)
    {
      /* 对应数据源不相等马上退出函数，并返回0 */
      return 0;
    }
    /* 递增两个数据源的地址指针 */
    pBuffer++;
    pBuffer1++;
  }
  /* 完成判断并且对应数据相对 */
  return 1;  
}
