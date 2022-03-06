#include "General_Tim.h"


void SendTim_Init(void)
{
		TIM_TimeBaseInitTypeDef SendTim_InitStructure;
	
		SENDTIM_RCC_CMD(SENDTIM_RCC,ENABLE);//使能基本定时器时钟
	
		SendTim_InitStructure.TIM_Prescaler = SENDTIM_CLK;
	
		SendTim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
		SendTim_InitStructure.TIM_Period = SENDTIM_Period;
	
		TIM_TimeBaseInit(SENDTIM_X,&SendTim_InitStructure);//初始化基本定时器
		TIM_ClearFlag(SENDTIM_X,TIM_FLAG_Update);//清除定时器中断标志位.
		TIM_ITConfig(SENDTIM_X,TIM_IT_Update,ENABLE);//使能定时器中断
		TIM_Cmd(SENDTIM_X,ENABLE);//使能定时器
}
void SendTim_NVIC(void)
{
		NVIC_InitTypeDef SendTim_NVIC_InitStructure;//定义基本定时器中断优先级结构体
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		SendTim_NVIC_InitStructure.NVIC_IRQChannel = SENDTIM_IRQ;//设置中断源
		SendTim_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		SendTim_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		SendTim_NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断源使能
		NVIC_Init(&SendTim_NVIC_InitStructure);
			
}
void Tim_Init(void)
{
		SendTim_NVIC();
		SendTim_Init();
}

