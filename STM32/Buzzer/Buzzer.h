#ifndef _BUZZER_H
#define _BUZZER_H
#include "stm32f10x.h"
#include "SysTick.h"

#define 		Buzzer_CLK_Cmd		RCC_APB2PeriphClockCmd
#define 		Buzzer_CLK    		RCC_APB2Periph_GPIOB
#define 		Buzzer_Port    		GPIOB
#define 		Buzzer_Pin    		GPIO_Pin_8

#define 		Buzzer_High				GPIO_SetBits(Buzzer_Port,Buzzer_Pin)
#define     Buzzer_Low        GPIO_ResetBits(Buzzer_Port,Buzzer_Pin)

void Buzzer_Init(void);
void Buzzer_Tick(void);
#endif

