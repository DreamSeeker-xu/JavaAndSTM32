#include "SysTick.h"


void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
}
void SysTick_Delay_us(uint32_t us)//1us延时程序
{
		uint32_t i;
		SysTick_Config(SystemCoreClock / 1000000);//设置重装载寄存器的值
		
	for(i = 0;i < us;i++)//
	{
			while(!((SysTick->CTRL) & (1 << 16)));//等待CTRL寄存器第16位置1(1us到)
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//关闭SysTick定时器
}
void SysTick_Delay_ms(uint32_t ms)//1ms延时程序
{
		uint32_t i;
		SysTick_Config(SystemCoreClock/1000);
		
		for(i = 0;i < ms;i++)
	{
			while(!((SysTick->CTRL) & (1 << 16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

