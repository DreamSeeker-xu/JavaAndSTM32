#ifndef BSP_USART_H
#define BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>

//串口1-USART	
#define		DEBUG_USART1x										USART1
#define		DEBUG_USART1_CLK							  RCC_APB2Periph_USART1
#define		DEBUG_USART1_APBxClkCmd 				RCC_APB2PeriphClockCmd
#define		DEBUG_USART1_BAURATE						9600

//USART1-GPIO 引脚宏定义
#define		DEBUG_USART1_GPIO_CLK						(RCC_APB2Periph_GPIOA)//APB2总线外设定义
#define   DEBUG_USART1_GPIO_APBxClkCmd		 RCC_APB2PeriphClockCmd//APB2时钟初始化

#define  	DEBUG_USART1_TX_GPIO_PORT				GPIOA
#define 	DEBUG_USART1_TX_GPIO_PIN				GPIO_Pin_9
#define   DEBUG_USART1_RX_GPIO_PORT				GPIOA
#define   DEBUG_USART1_RX_GPIO_PIN				GPIO_Pin_10

#define		DEBUG_USART1_IRQ								USART1_IRQn
#define   DEBUG_USART1_IRQHandler					USART1_IRQHandler


//串口2-USART	
#define		DEBUG_USART2x										USART2
#define		DEBUG_USART2_CLK								RCC_APB1Periph_USART2
#define		DEBUG_USART2_APBxClkCmd 				RCC_APB1PeriphClockCmd
#define		DEBUG_USART2_BAURATE						115200

//USART2-GPIO 引脚宏定义
#define		DEBUG_USART2_GPIO_CLK						(RCC_APB2Periph_GPIOA)//APB2总线外设定义
#define   DEBUG_USART2_GPIO_APBxClkCmd		RCC_APB2PeriphClockCmd//APB2时钟初始化

#define  	DEBUG_USART2_TX_GPIO_PORT				GPIOA
#define 	DEBUG_USART2_TX_GPIO_PIN				GPIO_Pin_2
#define   DEBUG_USART2_RX_GPIO_PORT				GPIOA
#define   DEBUG_USART2_RX_GPIO_PIN				GPIO_Pin_3

#define		DEBUG_USART2_IRQ								USART2_IRQn
#define   DEBUG_USART2_IRQHandler					USART2_IRQHandler


//串口3-USART	
#define		DEBUG_USART3x									USART3
#define		DEBUG_USART3_CLK							RCC_APB1Periph_USART3
#define		DEBUG_USART3_APBxClkCmd 			RCC_APB1PeriphClockCmd
#define		DEBUG_USART3_BAURATE					115200

//USART3-GPIO 引脚宏定义
#define		DEBUG_USART3_GPIO_CLK						(RCC_APB2Periph_GPIOB)//APB1总线外设定义
#define   DEBUG_USART3_GPIO_APBxClkCmd		RCC_APB2PeriphClockCmd//APB1时钟初始化

#define  	DEBUG_USART3_TX_GPIO_PORT				GPIOB
#define 	DEBUG_USART3_TX_GPIO_PIN				GPIO_Pin_10
#define   DEBUG_USART3_RX_GPIO_PORT				GPIOB
#define   DEBUG_USART3_RX_GPIO_PIN				GPIO_Pin_11

#define		DEBUG_USART3_IRQ								USART3_IRQn
#define   DEBUG_USART3_IRQHandler					USART3_IRQHandler


void USART_Config(void);
void Usart_SendByte(USART_TypeDef* pUSARTx,uint8_t data);
void Usart_SendHalfWord(USART_TypeDef* pUSARTx,uint16_t data);
void Usart_SendArray(USART_TypeDef* pUSARTx,uint8_t *array,uint8_t num);
void Usart_SendStr(USART_TypeDef* pUSARTx,uint8_t *str);
#endif /* BSP_USART_H*/

