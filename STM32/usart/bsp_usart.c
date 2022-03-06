#include "bsp_usart.h"

static void NVIC_Config(void)//NVIC(中断控制)初始化
{
		NVIC_InitTypeDef NVIC_InitStructure;//结构体定义
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//定义NVIC优先级组1
		
		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART3_IRQ;//配置中断源
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//配置抢占优先级为1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//配置子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
		NVIC_Init(&NVIC_InitStructure);//中断初始化
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//定义NVIC优先级组1
		
		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;//配置中断源
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//配置抢占优先级为1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//配置子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
		NVIC_Init(&NVIC_InitStructure);//中断初始化
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//定义NVIC优先级组1
		
		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;//配置中断源
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//配置抢占优先级为1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//配置子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
		NVIC_Init(&NVIC_InitStructure);//中断初始化
}
void USART_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		USART_InitTypeDef  USART_InitStructure;
		
		//打开串口1,3GPIO的时钟
		DEBUG_USART1_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK,ENABLE);
		DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK,ENABLE);
		//DEBUG_USART3_GPIO_APBxClkCmd(DEBUG_USART3_GPIO_CLK,ENABLE);
		
		DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK ,ENABLE);//打开串口1总线时钟
		DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK,ENABLE); 
		//DEBUG_USART3_APBxClkCmd(DEBUG_USART3_CLK ,ENABLE);//打开串口3总线时钟
		//串口1TX设置为推挽复用模式
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(DEBUG_USART1_TX_GPIO_PORT,&GPIO_InitStructure);
		//串口2TX设置为推挽复用模式
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
		GPIO_Init(DEBUG_USART2_TX_GPIO_PORT,&GPIO_InitStructure);
		//串口3TX设置为推挽复用模式
		//GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_TX_GPIO_PIN;
		//GPIO_Init(DEBUG_USART3_TX_GPIO_PORT,&GPIO_InitStructure);
		
		//串口1RX设置为浮空输入模式
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(DEBUG_USART1_RX_GPIO_PORT,&GPIO_InitStructure);
		//串口2RX设置为浮空输入模式
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
		GPIO_Init(DEBUG_USART2_RX_GPIO_PORT,&GPIO_InitStructure);
		//串口3RX设置为浮空输入模式
		//GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_RX_GPIO_PIN;
		//GPIO_Init(DEBUG_USART3_RX_GPIO_PORT,&GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAURATE;//设置串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//配置帧数据长度
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//配置停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//配置校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//配置硬件流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//配置串口模式(收发)
		USART_Init(DEBUG_USART1x , &USART_InitStructure);//完成串口初始化配置
	
		USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAURATE;//设置串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//配置帧数据长度
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//配置停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//配置校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//配置硬件流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//配置串口模式(收发)
		USART_Init(DEBUG_USART2x , &USART_InitStructure);//完成串口初始化配置
	
//		USART_InitStructure.USART_BaudRate = DEBUG_USART3_BAURATE;//设置串口3波特率
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//配置帧数据长度
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;//配置停止位
//		USART_InitStructure.USART_Parity = USART_Parity_No;//配置校验位
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//配置硬件流控制
//		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//配置串口模式(收发)
//		USART_Init(DEBUG_USART3x , &USART_InitStructure);//完成串口3初始化配置
		 NVIC_Config();//配置中断优先
	 
	 
	 USART_ITConfig(DEBUG_USART2x,USART_IT_RXNE,ENABLE);//使能串口2接收中断
	 USART_ITConfig(DEBUG_USART2x,USART_IT_IDLE,ENABLE);//使能串口2空闲中断
	 //USART_ITConfig(DEBUG_USART1x,USART_IT_RXNE,ENABLE);//使能串口1接收中断
	 
	 
	 USART_Cmd(DEBUG_USART1x,ENABLE);//使能串口1	
	 USART_Cmd(DEBUG_USART2x,ENABLE);//使能串口2	
	// USART_Cmd(DEBUG_USART3x,ENABLE);//使能串口3	
}
/*发送一个字节*/
void Usart_SendByte(USART_TypeDef* pUSARTx,uint8_t data)//串口数据发送
{
		USART_SendData(pUSARTx, data);
		while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);//等待发送完毕
}
/*发送连个字节*/
void Usart_SendHalfWord(USART_TypeDef* pUSARTx,uint16_t data)
{
	uint8_t temp_h,temp_l; 
	temp_h = (data&0xff00) >> 8;
	temp_l = data&0xff;
	USART_SendData(pUSARTx,temp_h );
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);
	USART_SendData(pUSARTx,temp_l );
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);
	
}
/*发送八位数据的数组*/
void Usart_SendArray(USART_TypeDef* pUSARTx,uint8_t *array,uint8_t num)
{
		uint8_t i;
	for(i = 0;i < num; i++)
	{
		Usart_SendByte(pUSARTx,array[i]);	
	}
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET);
}

/*发送字符串*/
void Usart_SendStr(USART_TypeDef* pUSARTx,uint8_t *str)
{
	uint8_t i = 0;
	do
	{
			Usart_SendByte(pUSARTx,*(str+i));
			i++;
	}while(*(str+i) != '\0');
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET);
	
}
//重定向c库函数printf到串口，重定向后可使用
int fputc(int ch, FILE *f)
{
		USART_SendData(DEBUG_USART1x,(uint8_t) ch);
		
		/*等待发送完毕*/
		while(USART_GetFlagStatus(DEBUG_USART1x,USART_FLAG_TXE) == RESET);
		return (ch);
}
///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数

