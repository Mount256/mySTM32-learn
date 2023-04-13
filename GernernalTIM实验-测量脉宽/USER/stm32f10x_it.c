/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "general_tim.h"

 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}


// ԭ�������˱����źŻ���������¼����ᴥ���жϣ���ת�����жϷ�����
// ���ڱ��ش����������ش����жϻ����½��ش����ж�Ҫ���û�������
// ��������ȥ��ʱ�򣬴��������ز����жϣ�ͬʱ��ʱ���ڼ�¼��ȥ�˼������ڣ����ҽ������ж�ģʽ����Ϊ�½��ش���
// ��ô�ڰ����ɿ���ʱ�򣬼��ᴥ���½��ز����жϣ���ʱһ�����������ɣ����ҽ������ж�ģʽ��������Ϊ�����ش���
void TIM5_IRQHandler(void)
{
	/******* 1. �ж��Ƿ�Ϊ�����¼��������ж� *******/
	// ���������������ź�ʱ����ڶ�ʱ������������Χ��65535��ʱ����ʱ���ͻ���������������жϣ�˵���Ѿ���ȥ��һ����ʱ������
	// һ����˵�����ǰ��°�����ʱ������ڵ�Ƭ����˵�Ƚϳ�����˿϶���������
	// ÿ�����ʹ���ж�Ϊ�棬����Ĵ���ͻ�����һ��
	if ( TIM_GetITStatus(GENERAL_TIM, TIM_IT_Update) != RESET )               
	{	
		TIM_ICUserValueStructure.Capture_Period++; // ���ڼ�1	
		TIM_ClearITPendingBit(GENERAL_TIM, TIM_IT_Update); // ��������жϱ�־ 		
	}
	
	/******* 2. �ж��������ػ����½��ز��񴥷����ж� *******/
	// �û�ÿһ�ΰ����������ɿ����ڼ䣬����Ĵ���ֻ���������Σ��Լ�����Ϊʲô����ʵ�����Ѿ�˵�ú������ˣ�
	if( TIM_GetITStatus(GENERAL_TIM, TIM_IT_CC1) != RESET ) 
	{
		/* ���������һ�β��񣨼����������أ� */
		if( TIM_ICUserValueStructure.Capture_StartFlag == 0 )
		{
			TIM_SetCounter(GENERAL_TIM, 0); // ��ʼ����
			TIM_ICUserValueStructure.Capture_Period = 0; // ��ʼ����¼���ڵ�ֵ
			TIM_ICUserValueStructure.Capture_CcrValue = 0; // ��ʼ����¼����Ĵ�����ֵ
			// ���÷����жϵ�ģʽΪ�½��ش�������ô��һ�η����ж�ʱ��Ϊ�������½��أ�Ϊ��������½��ز�����׼��
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling); 
			TIM_ICUserValueStructure.Capture_StartFlag = 1; // ����������Ѿ���������
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;
		}
		/* ����Ϊ�ڶ��β��񣨼������½��أ� */
		else
		{
			TIM_ICUserValueStructure.Capture_CcrValue = TIM_GetCapture1(GENERAL_TIM); // ��¼��ʱ����Ĵ�����ֵ
			// ���÷����жϵ�ģʽΪ�����ش�������ô��һ�η����ж�ʱ��Ϊ�����������أ�Ϊ��һ�������ز�����׼��
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Rising); 
			TIM_ICUserValueStructure.Capture_StartFlag = 0; // ���ñ�־λ��Ϊ��һ�������ز�����׼��
			TIM_ICUserValueStructure.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit(GENERAL_TIM, TIM_IT_CC1); // ��������жϱ�־
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
