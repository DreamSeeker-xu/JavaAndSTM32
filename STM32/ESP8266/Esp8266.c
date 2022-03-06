#include "Esp8266.h"
#include "string.h"
#include "led.h"
#include "General_Tim.h"
							//startfalg   	id    	len  	temp_h  temp_l   hum_h   hum_l    led		endflag
uint8_t updata[9] = {0XFD,  	0X01,  	0X05, 	0X00, 	0X00, 	0X00, 	0X00, 	0X00,	0XDF};

struct ESP8266_RECEIVE Esp8266_Receive = {{0},0,0};
uint8_t led_light = 0;

void ESP8266_GPIO_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		ESP8266_GPIO_APBxClkCmd(ESP8266_GPIO_CLK,ENABLE);
		GPIO_InitStructure.GPIO_Pin = ESP8266_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ESP8266_EN_PORT,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = ESP8266_RST_PIN;
		GPIO_Init(ESP8266_RST_PORT,&GPIO_InitStructure);
}
static bool ESP8266_Test(void)
{
		bool Esp8266_Test_Flag;
		uint8_t count = 0;
		while(count < 10)
		{
			if(Esp8266_Cmd((uint8_t*)ESP8266_Test_CMD,"OK",NULL,500))
			{
				printf("ESP8266ͨ������\r\n");
				return true;
			}
			count++;
		}
		if(count == 10)
		{
			printf("ESP8266ͨѶ�쳣\r\n");
			Esp8266_Test_Flag = false;
		}
		return Esp8266_Test_Flag;
}
static bool ESP8266_WIFI_Set()
{
		char WIFI_Set[120];
		sprintf(WIFI_Set,ESP8266_WIFI,WIFI_Name,WIFI_PassWord);
		return Esp8266_Cmd((uint8_t*)WIFI_Set,"OK",NULL,5000);
} 
static bool ESP8266_TCP_Connect()
{
		char TCP_Connect[120];
		sprintf(TCP_Connect,ESP8266_TCPContNect,TCP_IP,TCP_PORT);
		return Esp8266_Cmd((uint8_t*)TCP_Connect,"OK","ALREAY CONNECT",1000);
}
/*����ESP8266ģʽ*/
static void ESP8266_Mode_Set(ESP8266_MODE_CHOOSE Esp8266_Mode_Set)
{
	  bool Esp8266_Set_Flag;
		char Esp8266_Set[120];
		switch(Esp8266_Mode_Set)
		{ 
			case ESP8266_STA:sprintf(Esp8266_Set,ESP8266_MODE,Esp8266_Mode_Set);Esp8266_Set_Flag = Esp8266_Cmd((uint8_t*)Esp8266_Set,"OK",NULL,1000);break;
			case ESP8266_AP:sprintf(Esp8266_Set,ESP8266_MODE,Esp8266_Mode_Set);Esp8266_Set_Flag = Esp8266_Cmd((uint8_t*)Esp8266_Set,"OK",NULL,1000);break;
			case ESP8266_AP_STA:sprintf(Esp8266_Set,ESP8266_MODE,Esp8266_Mode_Set);Esp8266_Set_Flag = Esp8266_Cmd((uint8_t*)Esp8266_Set,"OK",NULL,1000);break;
		}
		if(Esp8266_Set_Flag)
			printf("ESP8266ģʽ���óɹ�\r\n");	
		else
			printf("ESP8266ģʽ����ʧ��\r\n");	
}
static bool Esp8266_CDisplay(void)
{
		bool cdisplay;
		cdisplay = Esp8266_Cmd((uint8_t*)ESP8266_CD,"OK",NULL,800);
		if(cdisplay)
		{
				printf("�رջ��Գɹ�\r\n");
				return true;
		}
		else
		{
				printf("�رջ���ʧ��\r\n");
				return false;
		}
}
static void Esp8266_SetTransparent_Transmission(void)
{
	if(Esp8266_Cmd((uint8_t*)ESP8266_TT_SEND,"OK",NULL,500))
	{
			printf("����͸���ɹ�\r\n");
	}
	else
	{
			printf("����͸��ʧ��\r\n");
	}
		
}
static bool ESP8266_StartSend(void)
{
	if(!Esp8266_Cmd((uint8_t*)ESP8266_START_SEND,">",NULL,500))
	{
			printf("��ʼ��������ʧ��\r\n");
			return false;
	}else
	{
			printf("��ʼ�������ݳɹ�\r\n");
			return true;
	}
}
static bool ESP8266_SetMUX(void)
{
		if(!Esp8266_Cmd((uint8_t*)ESP8266_MUX,"OK",NULL,500))
		{
				printf("���õ�����ʧ��\r\n");
				return false;
		}else
		{
				printf("���õ����ӳɹ�\r\n");
				return true;
		}
}
bool ESP8266_Init()
{
		bool Esp8266_Init_Flag;
		uint8_t i;
		for(i = 0;i < 5;i++)
		{
				//�˳�͸��
				Esp8266_Cmd((uint8_t*)"+++","OK",NULL,500);
				if(Esp8266_Cmd((uint8_t*)ESP8266_Test_CMD,"OK",NULL,500))
				{
						i = 0;
						printf("�˳�͸��ģʽ�ɹ�\r\n");
						break;
				}
		}
		if(i == 5)
		{
				printf("�˳�͸��ģʽʧ��\r\n");
				return false;
		}
		printf("���Ͳ�������\r\n");
		Esp8266_Init_Flag = Esp8266_Cmd((uint8_t*)ESP8266_Test_CMD,"OK",NULL,500);
		if(!Esp8266_Init_Flag)
		{
				printf("���Ͳ�������ʧ��\r\n");
				return false;
		}
		if(Esp8266_Init_Flag)
		{
				Esp8266_CDisplay();
				ESP8266_Mode_Set(ESP8266_AP_STA);
				printf("���͸�λ����\r\n");
				if(!Esp8266_Cmd((uint8_t*)ESP8266_RST,"OK",NULL,5000))
				{
						printf("���͸�λ����ʧ��\r\n");
						return false;
				}
				Esp8266_CDisplay();
				while(!ESP8266_WIFI_Set());	
				uint8_t send_data[18] = {0xFD,0x00,0x0F,0x01,0x01,0xCD,0xF8,0xC2,0xE7,0xC1,0xAC,0xBD,0xD3,0xB3,0xC9,0xB9,0xA6,0x84};
				Usart_SendArray(USART1,send_data,18);
				ESP8266_SetMUX();
				while(!ESP8266_TCP_Connect());
				uint8_t send_data1[20] = {0xFD,0x00,0x11,0x01,0x01,0xC1,0xAC,0xBD,0xD3,0xB7,0xFE,0xCE,0xF1,0xC6,0xF7,0xB3,0xC9,0xB9,0xA6,0xCD};
				Usart_SendArray(USART1,send_data1,20);
				Esp8266_SetTransparent_Transmission();
				ESP8266_StartSend();
				Esp8266_Init_Flag = true;
		}
		else
			Esp8266_Init_Flag = false;
		return Esp8266_Init_Flag;
}

//bool ESP8266_SendData(uint8_t *str)
//{
//		bool Send_Data_Flag = false;
//		uint8_t len = strlen((char*)str);
//		char Start_Send[len];
//		sprintf(Start_Send,ESP8266_SEND,len);
//		if(Esp8266_Cmd((uint8_t*)Start_Send,">","",400))
//		{
//				Send_Data_Flag = Esp8266_Cmd(str,">","SEND OK",400);
//				printf("���ͳɹ�");
//		}
//		return Send_Data_Flag;
//}
bool ESP8266_TTSendData(uint8_t *str)
{
		Usart_SendStr(USART2,str);
		printf("���ͳɹ�");
		return true;
}
bool ESP8266_TTSendArray(uint8_t *array,uint8_t num)
{
		Usart_SendArray(DEBUG_USART2x,array,num);
		return true;
}

bool ESP8266_SendArray(uint8_t *array,uint8_t num)
{
		char Start_Send[num];
		sprintf(Start_Send,ESP8266_SEND,num);
		Usart_SendStr(DEBUG_USART2x,(uint8_t*)Start_Send);
		SysTick_Delay_ms(100);
		Usart_SendArray(DEBUG_USART2x,array,num);
		SysTick_Delay_ms(400);
		return true;
}


/*
����Ӧ�жϵ�ESP8266�����
cmd:���͵�����
reply1:�ȴ��ĵ�һ����Ӧ

reply2:�ȴ��ĵڶ�����Ӧ
waittime:�ȴ�ʱ��(ms)
*/
bool Esp8266_Cmd(uint8_t *cmd,char *reply1,char *reply2,uint16_t waittime)
{
		//Esp8266_Receive.Receive_Length = 0;//����������ݳ���,׼����������
		USART_ITConfig(DEBUG_USART2x,USART_IT_RXNE,DISABLE);//�رմ���2�����ж�
		//while(USART_GetITStatus( DEBUG_USART2x, USART_IT_IDLE ) != SET);
		Usart_SendStr(DEBUG_USART2x,cmd);//��ESP8266��������
		USART_ITConfig(DEBUG_USART2x,USART_IT_RXNE,ENABLE);//ʹ�ܴ���2�����ж�
		if((reply1 == 0) && (reply2 == 0))//����Ҫ�ȴ�ESP8266��Ӧ
			return true;
		else
		{
				SysTick_Delay_ms(waittime);//�ȴ�ESP8266��Ӧ
				Esp8266_Receive.Receive_Data[Esp8266_Receive.Receive_Length] = '\0';//��ӽ�����
				Esp8266_Receive.Receive_FinshFlag = 0;
				//printf("%s",(uint8_t*)Esp8266_Receive.Receive_Data);//��������
				Esp8266_Receive.Receive_Length = 0;//����������ݳ���
				if((reply1 != 0) && (reply2 != 0))//��������Ӧ
					return ((bool)strstr((char*)Esp8266_Receive.Receive_Data,reply1) || (bool)strstr((char*)Esp8266_Receive.Receive_Data,reply2));
				else if(reply1 != 0)//ֻ��ȴ���һ����Ӧ
					return (bool)(strstr((char*)Esp8266_Receive.Receive_Data,reply1));
				else//ֻ��ȴ��ڶ�����Ӧ
					return (bool)(strstr((char*)Esp8266_Receive.Receive_Data,reply2));
		}
}
static void ESP8266_Rst()
{
		ESP8266_RST_LOW;
		SysTick_Delay_ms(100);
		ESP8266_RST_HIHG;
}


