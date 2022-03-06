#include "stm32f10x.h"
#include "bsp_usart.h"
#include "LED.h"
#include "Esp8266.h"
#include "SysTick.h"
#include "string.h"
#include "General_Tim.h"
#include "Buzzer.h"
#include "Dht11.h"



void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
void delay_ms(uint32_t n)
{
	while(n--) //延时值
	{
		SysTick->CTRL=0;			//关闭滴答定时器，从最初的状态开始
		SysTick->LOAD=(720000*n)-1;   //配置计数值为(720000)-1 ~ 0(递减)
		SysTick->VAL=0;				//清除当前计数值值
		SysTick->CTRL=5;			//使能定时器时钟
		while((SysTick->CTRL & 0x10000)==0);  //等待计数值归为0
			
	}
	SysTick->CTRL=0;		//关闭滴答定时器
}

int main(void)
{
	SysTick_Init();
	LED_Init();//初始化LED灯
	DHT11_GPIO_Init();//初始化DHT11引脚
	Buzzer_Init();//初始化蜂鸣器引脚
	USART_Config();//初始化串口  
	//初始化ESP8266
	if(!ESP8266_Init()) return false;	
	Buzzer_Tick();//嘀~
	Tim_Init();//定时器初始化
	//向服务器发送说明自己是设备
	ESP8266_TTSendData((uint8_t*)"devide\r\n");   
	while(1)
	{	
		//ESP8266接收到数据
		if(Esp8266_Receive.Receive_FinshFlag == 1)
		{
				Esp8266_Receive.Receive_FinshFlag = 0;
				if(Esp8266_Receive.Receive_Data[0] == 0XFC && Esp8266_Receive.Receive_Data[(Esp8266_Receive.Receive_Data[2] + 3)] == 0XCF)
				{
						if(Esp8266_Receive.Receive_Data[3] == 0X01)
						{
								printf("开灯\r\n");
								LED_Open();
						}else if(Esp8266_Receive.Receive_Data[3] == 0X00)
						{
								printf("关灯\r\n");
								LED_Close();
						}
				}
				Esp8266_Receive.Receive_Length = 0;
				memset(Esp8266_Receive.Receive_Data,0,RECEIVE_MAX_Length);
		}
		if(time_1s)
		{
				time_1s = 0;
				if(DHT11_Read_Dat() == SUCCESS)
				{
						uint8_t ledflag = GPIO_ReadInputDataBit(LED_GPIO_PORT,LED_GPIO_PIN);
						if(ledflag)
							updata[7] = 0X00;
						else
							updata[7] = 0X01;
						updata[3] = DHT11_Data[2];
						updata[4] = DHT11_Data[3];
						updata[5] = DHT11_Data[0];
						updata[6] = DHT11_Data[1];
						ESP8266_TTSendArray(updata,9);
				}
				
		}
	}
}
	
