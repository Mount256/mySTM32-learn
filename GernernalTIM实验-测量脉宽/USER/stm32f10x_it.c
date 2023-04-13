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


// 原理：捕获了边沿信号或产生更新事件即会触发中断，跳转至该中断服务函数
// 至于边沿触发是上升沿触发中断还是下降沿触发中断要看用户的配置
// 按键按下去的时候，触发上升沿捕获中断，同时定时器在记录过去了几个周期，并且将触发中断模式设置为下降沿触发
// 那么在按键松开的时候，即会触发下降沿捕获中断，此时一次脉冲测量完成，并且将触发中断模式重新设置为上升沿触发
void TIM5_IRQHandler(void)
{
	/******* 1. 判断是否为更新事件触发了中断 *******/
	// 如果被捕获的输入信号时间大于定时器的最大计数范围（65535）时，定时器就会溢出，产生更新中断，说明已经过去了一个定时器周期
	// 一般来说，我们按下按键的时长相对于单片机来说比较长，因此肯定会出现溢出
	// 每次溢出使得判断为真，下面的代码就会运行一次
	if ( TIM_GetITStatus(GENERAL_TIM, TIM_IT_Update) != RESET )               
	{	
		TIM_ICUserValueStructure.Capture_Period++; // 周期加1	
		TIM_ClearITPendingBit(GENERAL_TIM, TIM_IT_Update); // 清除更新中断标志 		
	}
	
	/******* 2. 判断是上升沿还是下降沿捕获触发了中断 *******/
	// 用户每一次按键按下又松开的期间，下面的代码只会运行两次，自己想想为什么（其实上面已经说得很明显了）
	if( TIM_GetITStatus(GENERAL_TIM, TIM_IT_CC1) != RESET ) 
	{
		/* 如果发生第一次捕获（即捕获上升沿） */
		if( TIM_ICUserValueStructure.Capture_StartFlag == 0 )
		{
			TIM_SetCounter(GENERAL_TIM, 0); // 开始计数
			TIM_ICUserValueStructure.Capture_Period = 0; // 初始化记录周期的值
			TIM_ICUserValueStructure.Capture_CcrValue = 0; // 初始化记录捕获寄存器的值
			// 配置发生中断的模式为下降沿触发，那么下一次发生中断时即为捕获了下降沿，为待会儿的下降沿捕获做准备
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling); 
			TIM_ICUserValueStructure.Capture_StartFlag = 1; // 标记上升沿已经触发过了
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;
		}
		/* 否则即为第二次捕获（即捕获下降沿） */
		else
		{
			TIM_ICUserValueStructure.Capture_CcrValue = TIM_GetCapture1(GENERAL_TIM); // 记录此时捕获寄存器的值
			// 配置发生中断的模式为上升沿触发，那么下一次发生中断时即为捕获了上升沿，为下一次上升沿捕获做准备
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Rising); 
			TIM_ICUserValueStructure.Capture_StartFlag = 0; // 重置标志位，为下一次上升沿捕获做准备
			TIM_ICUserValueStructure.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit(GENERAL_TIM, TIM_IT_CC1); // 清除捕获中断标志
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
