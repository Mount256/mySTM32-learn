#include "stm32f10x.h"
#include "usart.h"
#include "general_tim.h"

int main(void)
{	
	uint32_t time;
	uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
	
	USART_Config();
	GENERAL_TIM_Init();
	
	printf("开始测试！来！\n");
	
	while(1)
	{
		if(TIM_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// 高电平时间的计数器的值 = 定时器周期 * 65535 + 多出来的（不够一个定时器周期的）时间（即捕获寄存器的值）
			// 单位为 us，因此需要除于一个分频因子得到单位为 s 的结果
			time = TIM_ICUserValueStructure.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure.Capture_CcrValue+1);
			
			// 打印高电平脉宽时间
			printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n", time / TIM_PscCLK, time % TIM_PscCLK );
			
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;			
		}		
	}
 }
