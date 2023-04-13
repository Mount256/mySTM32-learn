#ifndef __DMA_H
#define __DMA_H
#include "stm32f10x_dma.h"

#define BUFFER_SIZE 		32
#define SENDBUFFER_SIZE 	500

void M2M_DMA_Config(void);
void USART_DMA_Config(void);

uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

#endif /* __DMA_H */
