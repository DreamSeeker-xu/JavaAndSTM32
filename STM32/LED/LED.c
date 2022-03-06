#include "LED.h"



void LED_Init()
{
		GPIO_InitTypeDef LED_GPIO_InitStruct;
		RCC_APB2PeriphClockCmd(LED_GPIO_RCC,ENABLE);
	
		LED_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		LED_GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN;
		LED_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LED_GPIO_PORT,&LED_GPIO_InitStruct);
		
		GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}

void LED_Open()
{
		GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}
void LED_Close()
{
		GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}


