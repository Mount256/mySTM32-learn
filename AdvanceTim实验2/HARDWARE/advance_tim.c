#include "advance_tim.h"

static void ADVANCE_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStrutcure;
	
	/* ���벶��ͨ����ʼ��(PA8) */
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_PORT_CLK, ENABLE);
	GPIO_InitStrutcure.GPIO_Pin 	= ADVANCE_TIM_CH1_PIN;
	GPIO_InitStrutcure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStrutcure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(ADVANCE_TIM_CH1_PORT ,&GPIO_InitStrutcure);
}

static void ADVANCE_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
    NVIC_InitStructure.NVIC_IRQChannel 					 = ADVANCE_TIM_IRQ; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void ADVANCE_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef 		TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE);
	
	/* ʱ����Ԫ��ʼ�� */
	TIM_TimeBaseStructure.TIM_Prescaler 		= ADVANCE_TIM_PSC; 	   	// ������ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up; 	// ����ģʽ
	TIM_TimeBaseStructure.TIM_Period 			= ADVANCE_TIM_PERIOD; 	// �Զ���װ�ؼĴ���
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1; 		// ʱ�ӷ�Ƶ����
	TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVANCE_TIM_RECNT; 	// �ظ�������
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
	/* ���벶��IC1��ʼ�����������ڣ� */
	TIM_ICInitStructure.TIM_Channel 	= TIM_Channel_1;			// ѡ�񲶻�ͨ��1
	TIM_ICInitStructure.TIM_ICPolarity 	= TIM_ICPolarity_Rising;	// �����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // ֱ������
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			// �����Ƶ����Ϊ1��������Ƶ
	TIM_ICInitStructure.TIM_ICFilter 	= 0;						// �˲�ϵ�������ﲻ�����˲�
	TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* ���ó�ʼ��IC2 */

	/* ѡ�����벶��Ĵ����ź� */
	TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);	
	/* ʹ������ģʽ */
	TIM_SelectMasterSlaveMode(ADVANCE_TIM, TIM_MasterSlaveMode_Enable); 	
	/* ѡ���ģʽ: ��λģʽ */
	TIM_SelectSlaveMode(ADVANCE_TIM, TIM_SlaveMode_Reset); 
	// ������ģʽ��PWM1����ģʽ���빤���ڸ�λģʽ��������ʼʱ��������CNT�ᱻ��λ
	
	/* ʹ�ܲ����ж� */
	TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);	
	/* ����жϱ�־λ */
	TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);
	/* ʹ�ܶ�ʱ�� */
	TIM_Cmd(ADVANCE_TIM, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
	ADVANCE_TIM_Mode_Config();
}
