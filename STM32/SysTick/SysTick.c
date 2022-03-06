#include "SysTick.h"


void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0��汾
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
}
void SysTick_Delay_us(uint32_t us)//1us��ʱ����
{
		uint32_t i;
		SysTick_Config(SystemCoreClock / 1000000);//������װ�ؼĴ�����ֵ
		
	for(i = 0;i < us;i++)//
	{
			while(!((SysTick->CTRL) & (1 << 16)));//�ȴ�CTRL�Ĵ�����16λ��1(1us��)
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//�ر�SysTick��ʱ��
}
void SysTick_Delay_ms(uint32_t ms)//1ms��ʱ����
{
		uint32_t i;
		SysTick_Config(SystemCoreClock/1000);
		
		for(i = 0;i < ms;i++)
	{
			while(!((SysTick->CTRL) & (1 << 16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

