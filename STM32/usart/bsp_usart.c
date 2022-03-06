#include "bsp_usart.h"

static void NVIC_Config(void)//NVIC(�жϿ���)��ʼ��
{
		NVIC_InitTypeDef NVIC_InitStructure;//�ṹ�嶨��
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����NVIC���ȼ���1
		
		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART3_IRQ;//�����ж�Դ
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//������ռ���ȼ�Ϊ1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//���������ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
		NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����NVIC���ȼ���1
		
		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;//�����ж�Դ
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//������ռ���ȼ�Ϊ1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//���������ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
		NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����NVIC���ȼ���1
		
		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;//�����ж�Դ
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//������ռ���ȼ�Ϊ1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//���������ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
		NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
}
void USART_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		USART_InitTypeDef  USART_InitStructure;
		
		//�򿪴���1,3GPIO��ʱ��
		DEBUG_USART1_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK,ENABLE);
		DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK,ENABLE);
		//DEBUG_USART3_GPIO_APBxClkCmd(DEBUG_USART3_GPIO_CLK,ENABLE);
		
		DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK ,ENABLE);//�򿪴���1����ʱ��
		DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK,ENABLE); 
		//DEBUG_USART3_APBxClkCmd(DEBUG_USART3_CLK ,ENABLE);//�򿪴���3����ʱ��
		//����1TX����Ϊ���츴��ģʽ
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(DEBUG_USART1_TX_GPIO_PORT,&GPIO_InitStructure);
		//����2TX����Ϊ���츴��ģʽ
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
		GPIO_Init(DEBUG_USART2_TX_GPIO_PORT,&GPIO_InitStructure);
		//����3TX����Ϊ���츴��ģʽ
		//GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_TX_GPIO_PIN;
		//GPIO_Init(DEBUG_USART3_TX_GPIO_PORT,&GPIO_InitStructure);
		
		//����1RX����Ϊ��������ģʽ
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(DEBUG_USART1_RX_GPIO_PORT,&GPIO_InitStructure);
		//����2RX����Ϊ��������ģʽ
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
		GPIO_Init(DEBUG_USART2_RX_GPIO_PORT,&GPIO_InitStructure);
		//����3RX����Ϊ��������ģʽ
		//GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_RX_GPIO_PIN;
		//GPIO_Init(DEBUG_USART3_RX_GPIO_PORT,&GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAURATE;//���ô��ڲ�����
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����֡���ݳ���
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����У��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����Ӳ��������
		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//���ô���ģʽ(�շ�)
		USART_Init(DEBUG_USART1x , &USART_InitStructure);//��ɴ��ڳ�ʼ������
	
		USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAURATE;//���ô��ڲ�����
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����֡���ݳ���
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����У��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����Ӳ��������
		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//���ô���ģʽ(�շ�)
		USART_Init(DEBUG_USART2x , &USART_InitStructure);//��ɴ��ڳ�ʼ������
	
//		USART_InitStructure.USART_BaudRate = DEBUG_USART3_BAURATE;//���ô���3������
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����֡���ݳ���
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
//		USART_InitStructure.USART_Parity = USART_Parity_No;//����У��λ
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����Ӳ��������
//		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//���ô���ģʽ(�շ�)
//		USART_Init(DEBUG_USART3x , &USART_InitStructure);//��ɴ���3��ʼ������
		 NVIC_Config();//�����ж�����
	 
	 
	 USART_ITConfig(DEBUG_USART2x,USART_IT_RXNE,ENABLE);//ʹ�ܴ���2�����ж�
	 USART_ITConfig(DEBUG_USART2x,USART_IT_IDLE,ENABLE);//ʹ�ܴ���2�����ж�
	 //USART_ITConfig(DEBUG_USART1x,USART_IT_RXNE,ENABLE);//ʹ�ܴ���1�����ж�
	 
	 
	 USART_Cmd(DEBUG_USART1x,ENABLE);//ʹ�ܴ���1	
	 USART_Cmd(DEBUG_USART2x,ENABLE);//ʹ�ܴ���2	
	// USART_Cmd(DEBUG_USART3x,ENABLE);//ʹ�ܴ���3	
}
/*����һ���ֽ�*/
void Usart_SendByte(USART_TypeDef* pUSARTx,uint8_t data)//�������ݷ���
{
		USART_SendData(pUSARTx, data);
		while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);//�ȴ��������
}
/*���������ֽ�*/
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
/*���Ͱ�λ���ݵ�����*/
void Usart_SendArray(USART_TypeDef* pUSARTx,uint8_t *array,uint8_t num)
{
		uint8_t i;
	for(i = 0;i < num; i++)
	{
		Usart_SendByte(pUSARTx,array[i]);	
	}
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET);
}

/*�����ַ���*/
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
//�ض���c�⺯��printf�����ڣ��ض�����ʹ��
int fputc(int ch, FILE *f)
{
		USART_SendData(DEBUG_USART1x,(uint8_t) ch);
		
		/*�ȴ��������*/
		while(USART_GetFlagStatus(DEBUG_USART1x,USART_FLAG_TXE) == RESET);
		return (ch);
}
///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���

