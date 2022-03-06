#include "Buzzer.h"


void Buzzer_Init()
{
		GPIO_InitTypeDef Buzzer_GPIO_InitStructure;
		Buzzer_CLK_Cmd(Buzzer_CLK,ENABLE);
		Buzzer_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		Buzzer_GPIO_InitStructure.GPIO_Pin = Buzzer_Pin;
		Buzzer_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(Buzzer_Port,&Buzzer_GPIO_InitStructure);
		Buzzer_Low;
}
void Buzzer_Tick()
{
		Buzzer_High;
		SysTick_Delay_ms(25);
		Buzzer_Low;
}
