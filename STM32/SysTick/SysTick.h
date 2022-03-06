#ifndef _SYSTICK_H
#define _SYSTICK_H
#include "stm32f10x.h"

void SysTick_Init(void);
void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);






#endif
