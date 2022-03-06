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
	while(n--) //��ʱֵ
	{
		SysTick->CTRL=0;			//�رյδ�ʱ�����������״̬��ʼ
		SysTick->LOAD=(720000*n)-1;   //���ü���ֵΪ(720000)-1 ~ 0(�ݼ�)
		SysTick->VAL=0;				//�����ǰ����ֵֵ
		SysTick->CTRL=5;			//ʹ�ܶ�ʱ��ʱ��
		while((SysTick->CTRL & 0x10000)==0);  //�ȴ�����ֵ��Ϊ0
			
	}
	SysTick->CTRL=0;		//�رյδ�ʱ��
}

int main(void)
{
	SysTick_Init();
	LED_Init();//��ʼ��LED��
	DHT11_GPIO_Init();//��ʼ��DHT11����
	Buzzer_Init();//��ʼ������������
	USART_Config();//��ʼ������  
	//��ʼ��ESP8266
	if(!ESP8266_Init()) return false;	
	Buzzer_Tick();//��~
	Tim_Init();//��ʱ����ʼ��
	//�����������˵���Լ����豸
	ESP8266_TTSendData((uint8_t*)"devide\r\n");   
	while(1)
	{	
		//ESP8266���յ�����
		if(Esp8266_Receive.Receive_FinshFlag == 1)
		{
				Esp8266_Receive.Receive_FinshFlag = 0;
				if(Esp8266_Receive.Receive_Data[0] == 0XFC && Esp8266_Receive.Receive_Data[(Esp8266_Receive.Receive_Data[2] + 3)] == 0XCF)
				{
						if(Esp8266_Receive.Receive_Data[3] == 0X01)
						{
								printf("����\r\n");
								LED_Open();
						}else if(Esp8266_Receive.Receive_Data[3] == 0X00)
						{
								printf("�ص�\r\n");
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
	
