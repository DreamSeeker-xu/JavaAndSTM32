#ifndef _DHR11_H
#define _DHR11_H
#include "stm32f10x.h"
#include "SysTick.h"

extern uint8_t DHT11_Data[5];
#define DHT11_CLK_CMD						RCC_APB2PeriphClockCmd
#define	DHT11_DATA_RCC					RCC_APB2Periph_GPIOB
#define	DHT11_DATA_Port					GPIOB	
#define	DHT11_DATA_Pin					GPIO_Pin_1


#define DHT11_DATA_Read  				GPIO_ReadInputDataBit(DHT11_DATA_Port,DHT11_DATA_Pin)
#define DHT11_DATA_High					GPIO_SetBits(DHT11_DATA_Port,DHT11_DATA_Pin)
#define DHT11_DATA_Low					GPIO_ResetBits(DHT11_DATA_Port,DHT11_DATA_Pin)

void DHT11_GPIO_Init(void);
u8 DHT11_Read_Dat(void);

#endif
