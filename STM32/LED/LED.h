#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"


#define LED_GPIO_RCC			RCC_APB2Periph_GPIOC
#define LED_GPIO_PORT			GPIOC
#define LED_GPIO_PIN			GPIO_Pin_13	

//PWM模式下
//PWM频率 = (SYSTclk / DIV / (PSC + 1) / (ARR + 1))
//(PSC + 1) * (ARR + 1) = (SYSTclk / DIV) / PWM频率
//占空比 = (ARR + 1) / 2 - 1
#define LED_TIMX							TIM2
#define LED_TIMX_RCC					RCC_APB1Periph_TIM2
#define LED_TIM_PERIOD				(100-1)
#define LED_TIM_PRESCALER			(144-1)


#define LED_TIMOUT_PROLARITY	TIM_OCPolarity_High
#define	LED_TIM_PULSE					(10-1)



void LED_Init(void);
void LED_Open(void);
void LED_Close(void);



#endif
