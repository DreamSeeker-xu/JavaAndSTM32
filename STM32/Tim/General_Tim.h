#ifndef _GENERAL_H
#define _GENERAL_H

#include "stm32f10x.h"

/*基本定时器时钟*/
#define BASICTIM_RCC_CMD 						RCC_APB1PeriphClockCmd
#define BASICTIM_RCC								RCC_APB1Periph_TIM2

#define TIM_X												TIM2
#define BASICTIM_CLK								(72-1)
#define BASICTIM_Period							(10000-1)

#define BASICTIM_IRQ								TIM2_IRQn
#define BASICTIM_IRQ_FUN						TIM2_IRQHandler


#define SENDTIM_RCC_CMD							RCC_APB1PeriphClockCmd
#define SENDTIM_RCC									RCC_APB1Periph_TIM3

#define SENDTIM_X										TIM3


#define SENDTIM_CLK									(7200-1)
#define SENDTIM_Period							(10000-1)

#define SENDTIM_IRQ									TIM3_IRQn
#define SENDTIM_IRQ_FUN							TIM3_IRQHandler


void BasicTim_Init(void);
void Tim_Init(void);


#endif
