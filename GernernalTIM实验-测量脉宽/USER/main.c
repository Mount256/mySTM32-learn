#include "stm32f10x.h"
#include "usart.h"
#include "general_tim.h"

int main(void)
{	
	uint32_t time;
	uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
	
	USART_Config();
	GENERAL_TIM_Init();
	
	printf("��ʼ���ԣ�����\n");
	
	while(1)
	{
		if(TIM_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// �ߵ�ƽʱ��ļ�������ֵ = ��ʱ������ * 65535 + ������ģ�����һ����ʱ�����ڵģ�ʱ�䣨������Ĵ�����ֵ��
			// ��λΪ us�������Ҫ����һ����Ƶ���ӵõ���λΪ s �Ľ��
			time = TIM_ICUserValueStructure.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure.Capture_CcrValue+1);
			
			// ��ӡ�ߵ�ƽ����ʱ��
			printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n", time / TIM_PscCLK, time % TIM_PscCLK );
			
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;			
		}		
	}
 }
