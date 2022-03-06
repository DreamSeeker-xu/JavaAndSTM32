#include "General_Tim.h"


void SendTim_Init(void)
{
		TIM_TimeBaseInitTypeDef SendTim_InitStructure;
	
		SENDTIM_RCC_CMD(SENDTIM_RCC,ENABLE);//ʹ�ܻ�����ʱ��ʱ��
	
		SendTim_InitStructure.TIM_Prescaler = SENDTIM_CLK;
	
		SendTim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
		SendTim_InitStructure.TIM_Period = SENDTIM_Period;
	
		TIM_TimeBaseInit(SENDTIM_X,&SendTim_InitStructure);//��ʼ��������ʱ��
		TIM_ClearFlag(SENDTIM_X,TIM_FLAG_Update);//�����ʱ���жϱ�־λ.
		TIM_ITConfig(SENDTIM_X,TIM_IT_Update,ENABLE);//ʹ�ܶ�ʱ���ж�
		TIM_Cmd(SENDTIM_X,ENABLE);//ʹ�ܶ�ʱ��
}
void SendTim_NVIC(void)
{
		NVIC_InitTypeDef SendTim_NVIC_InitStructure;//���������ʱ���ж����ȼ��ṹ��
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		SendTim_NVIC_InitStructure.NVIC_IRQChannel = SENDTIM_IRQ;//�����ж�Դ
		SendTim_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		SendTim_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		SendTim_NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�Դʹ��
		NVIC_Init(&SendTim_NVIC_InitStructure);
			
}
void Tim_Init(void)
{
		SendTim_NVIC();
		SendTim_Init();
}

