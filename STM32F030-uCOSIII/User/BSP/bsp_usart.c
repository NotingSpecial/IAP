#include "includes.h"


/***********************************************************************************************
* Function Name  : uart1Init()
* Description    : ��ʼ��USART1�����ò�����
* Input          : None
* Output         : None 
* Return         : None 
* Contributor	: 2018-6-15
***********************************************************************************************/
void uart1Init()
{
    //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  //��ϵͳ����ʱ��  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
 	USART_DeInit(USART1);  //��λ����1
	
	//USART1���Ÿ���
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);    
  
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//NVIC�жϳ�ʼ��
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
 USART_Cmd(USART1, ENABLE); //ʹ�ܴ��� 
	USART_ClearFlag(USART1, USART_FLAG_TC);  //����жϱ�־
	 
}
/***********************************************************************************************
* Function Name  : USART1_IRQHandler (void) 
* Description    : USART1���ڽ����ж�
* Input          : None
* Output         : None 
* Return         : None 
* Contributor	: 2018-6-15
***********************************************************************************************/
void USART1_IRQHandler (void)
{
	uint16_t temp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)   //Receive Data register not empty interrupt.�������ݼĴ��������жϡ�
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		temp = USART_ReceiveData(USART1);   
		USART_SendData(USART1,temp);
	}
}
/***********************************************************************************************
* Function Name  : USART1_send(void * buf,uint8_t size) 
* Description    : ���ڷ���
* Input          : buf-->����ָ�룻size-->���ݳ���
* Output         : None 
* Return         : None 
* Contributor	: 2018-6-15
***********************************************************************************************/
void USART1_send(void * buf,uint8_t size)
{
	uint8_t* temp = (uint8_t*)buf;
	while(size>0)
	{
		USART_SendData(USART1, *temp);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
		temp++;
		size--;				
  }
}

/***********************************************************************************************
* Function Name  : fputc(int ch, FILE *f) 
* Description    : printf����ض���
* Input          : int ch, FILE *f
* Output         : ch 
* Return         : None 
* Contributor	: 2018-6-15
***********************************************************************************************/  
int fputc(int ch, FILE *f)
{
     while (!(USART1->ISR & USART_FLAG_TXE));
     USART1->TDR = ch;
  
     return (ch);
}


/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void usart2_init(uint32_t bound,uint32_t Parity) //uart ��ʼ��
{
	//USART2 �˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//485����ģʽ,����ѡ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);    
  
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//NVIC��ʼ��
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_9b;
	USART_InitStructure.USART_Parity = Parity;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //�����ж�
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ��� 
	USART_ClearFlag(USART2, USART_FLAG_TC);  //����жϱ�־
}

/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void USART3_Initial(uint32_t bound,uint32_t Parity)
{
    //USART3 �˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//USART3
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_4);    
  
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//NVIC��ʼ��
	NVIC_InitStructure.NVIC_IRQChannel=USART3_6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART3 configuration
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_Parity=Parity;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	USART_Init(USART3, &USART_InitStructure);
	
 	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
	USART_ClearFlag(USART3, USART_FLAG_TC); //����жϱ�־
}

/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void USART4_Initial(uint32_t bound,uint32_t Parity)
{
	//USART4 �˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//USART4
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_0);    
  
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//NVIC��ʼ��
	NVIC_InitStructure.NVIC_IRQChannel=USART3_6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART4 configuration
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_Parity=Parity;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	USART_Init(USART4, &USART_InitStructure);
    
	USART_ClockInitStructure.USART_Clock           = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL            = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA            = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit         = USART_LastBit_Disable;
	USART_ClockInit(USART4, &USART_ClockInitStructure);

	USART_ITConfig(USART4, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART4, ENABLE);
	USART_ClearFlag(USART4, USART_FLAG_TC); //����жϱ�־
}

/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void USART5_Initial(uint32_t bound,uint32_t Parity)
{
	//USART5 �˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Connect pin to Periph */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_2);    
  
	//USART5_TX   PC12
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//USART5_RX   PD2
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//NVIC��ʼ��
	NVIC_InitStructure.NVIC_IRQChannel=USART3_6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART5 configuration
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_Parity=Parity;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART5, &USART_InitStructure);
	
 	USART_ITConfig(USART5, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART5, ENABLE);
	//USART_ClearFlag(USART5, USART_FLAG_TC); //����жϱ�־
}
