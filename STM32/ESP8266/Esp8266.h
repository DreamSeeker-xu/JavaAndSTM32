#ifndef _ESP8266_H
#define	_ESP8266_H
#include "stm32f10x.h"
#include "stdbool.h"
#include "bsp_usart.h"
#include "SysTick.h"
#include "buzzer.h"
/*ESP8266模式设置
1.STA模式:ESP8266_STA
2.AP模式:ESP8266_AP
3.STA+AP模式:ESP8266_AP_STA
*/
#define Esp8266_ModeSet               ESP8266_AP_STA

/*ESP8266连接WIFI设置*/
#define WIFI_Name											"WIFI名"
#define WIFI_PassWord									"WIFI密码"
/*ESP8266建立TCP连接*/
#define TCP_IP												"服务端IP"
//服务端端口
#define TCP_PORT											


/*接收缓冲区大小*/
#define  RECEIVE_MAX_Length              100

#define  WaitCount                    5

#define  ESP8266_GPIO_CLK						  (RCC_APB2Periph_GPIOB)
#define  ESP8266_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd
#define  ESP8266_EN_PORT							GPIOB
#define  ESP8266_EN_PIN								GPIO_Pin_8
#define  ESP8266_EN_HIHG							GPIO_SetBits(ESP8266_EN_PORT,ESP8266_EN_PIN)
#define  ESP8266_EN_LOW								GPIO_ResetBits(ESP8266_EN_PORT,ESP8266_EN_PIN)


#define  ESP8266_RST_PORT							GPIOB
#define  ESP8266_RST_PIN							GPIO_Pin_9
#define  ESP8266_RST_HIHG							GPIO_SetBits(ESP8266_RST_PORT,ESP8266_RST_PIN)
#define  ESP8266_RST_LOW							GPIO_ResetBits(ESP8266_RST_PORT,ESP8266_RST_PIN)

#define  OPEN_LED								"openled"

#define  ESP8266_Test_CMD				"AT\r\n"
#define  ESP8266_MODE 					"AT+CWMODE=%d\r\n"
#define  ESP8266_WIFI						"AT+CWJAP=\"%s\",\"%s\"\r\n"
#define  ESP8266_MUX						"AT+CIPMUX=0\r\n"
#define  ESP8266_RST						"AT+RST\r\n"
#define	 ESP8266_TCPContNect		"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n"
#define	 ESP8266_START_SEND			"AT+CIPSEND\r\n"
#define	 ESP8266_SEND						"AT+CIPSEND=%d\r\n"
#define  ESP8266_TT_SEND				"AT+CIPMODE=1\r\n"
#define  ESP8266_CD							"ATE0\r\n"
/*ESP8266模式设置*/
typedef enum {
	ESP8266_STA = 1,
	ESP8266_AP = 2,
	ESP8266_AP_STA = 3
}ESP8266_MODE_CHOOSE;
extern struct ESP8266_RECEIVE{
		uint8_t Receive_Data[RECEIVE_MAX_Length];
		uint16_t Receive_Length;
		uint16_t Receive_FinshFlag;
} Esp8266_Receive;

extern uint8_t time_10ms,time_1s;
extern uint8_t updata[9];
extern uint8_t led_light; 
void ESP8266_GPIO_Config(void);
void ESP8266(void);
bool ESP8266_Init(void);
bool ESP8266_SendData(uint8_t *str);
bool Esp8266_Cmd(uint8_t *cmd,char *reply1,char *reply2,uint16_t waittime);
void ESP8266_Receive(void);
bool ESP8266_SendArray(uint8_t *array,uint8_t num);
bool ESP8266_TTSendData(uint8_t *str);
bool ESP8266_TTSendArray(uint8_t *array,uint8_t num);
#endif
