#include "Dht11.h"
uint8_t DHT11_Data[5] = {0,0,0,0,0};
void DHT11_GPIO_Init()
{
		GPIO_InitTypeDef DHT11_GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd(DHT11_DATA_RCC,ENABLE);
	
		DHT11_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		DHT11_GPIO_InitStructure.GPIO_Pin = DHT11_DATA_Pin;
		DHT11_GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	
		GPIO_Init(DHT11_DATA_Port,&DHT11_GPIO_InitStructure);
}

void DHT_GPIO_PPout()
{
		GPIO_InitTypeDef DHT11_GPIO_InitStructure;
	
		DHT11_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		DHT11_GPIO_InitStructure.GPIO_Pin = DHT11_DATA_Pin;
		DHT11_GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	
		GPIO_Init(DHT11_DATA_Port,&DHT11_GPIO_InitStructure);
}
void DHT11_GPIO_IPU()
{
		GPIO_InitTypeDef DHT11_GPIO_InitStructure;
	
		DHT11_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		DHT11_GPIO_InitStructure.GPIO_Pin = DHT11_DATA_Pin;
		DHT11_GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	
		GPIO_Init(DHT11_DATA_Port,&DHT11_GPIO_InitStructure);
}
u8 DHT11_Read_Byte()
{
		u8 temp = 0,i = 0;
		for(i = 0;i < 8;i++)
		{
			while(!DHT11_DATA_Read);//等待50us低电平时隙;
			SysTick_Delay_us(40);//跳过数据0的时间;
			temp <<= 1;
			if(DHT11_DATA_Read)
			{
				temp |= 0x01;
			}
			while(DHT11_DATA_Read);
		}
	  return temp;
}
u8 DHT11_Read_Dat()
{
		u8 i = 0;
		DHT_GPIO_PPout();
		DHT11_DATA_High;
		SysTick_Delay_us(2);
		DHT11_DATA_Low;
		SysTick_Delay_ms(18);//拉低大于18ms
		DHT11_DATA_High;
		SysTick_Delay_us(30);//拉高并延时
		DHT11_GPIO_IPU();
		if(!DHT11_DATA_Read)//从机应答
		{
			while(!DHT11_DATA_Read);//等待DHT11响应低电平结束
			while(DHT11_DATA_Read);//等待DHT11响应高电平结束
			for(i = 0;i < 5;i++)
			{
					DHT11_Data[i] = DHT11_Read_Byte();
					SysTick_Delay_us(10);
			}
			
			SysTick_Delay_us(50);
			//DATA = 1;
			if(DHT11_Data[4] == DHT11_Data[0] + DHT11_Data[1] + DHT11_Data[2] + DHT11_Data[3])
				return SUCCESS;
			else
				return ERROR;
		}
		else 
			return ERROR;
}
