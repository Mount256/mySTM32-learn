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
	
	/* 1. ����DMAʱ�ӣ�AHB���ߣ�*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* 2. �����������ַ */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
	/* 3. ���ô洢������ַ */
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	/* 4. ���ô��䷽�� */
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	/* 5. ���ô�����Ŀ */
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	/* 6. ���������ַ�����Ƿ�Ϊ����ģʽ */
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	/* 7. ���ô洢����ַ�����Ƿ�Ϊ����ģʽ */
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/* 8. �����������ݿ�� */
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	/* 9. ���ô洢�����ݿ�� */
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	/* 10. ���ù���ģʽ */
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	/* 11. ����DMA���ȼ� */
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* 12. �����Ƿ�ΪM2Mģʽ */
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	
	/* 13. ��ʼ��DMAͨ�� */
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	/* 14. ������ͱ�־ */
	DMA_ClearFlag(DMA1_FLAG_TC6);
	/* 15. ʹ��DMAͨ�� */
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

/* �Ƚ��Ƿ�һ�� */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--)
  {
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer != *pBuffer1)
    {
      /* ��Ӧ����Դ����������˳�������������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer++;
    pBuffer1++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;  
}
