#include "includes.h"


/***********************************************************************************************
* Function Name  : uart1Init()
* Description    : 初始化USART1，设置波特率
* Input          : None
* Output         : None 
* Return         : None 
* Contributor	: 2018-6-15
***********************************************************************************************/
void uart1Init()
{
    //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  //打开系统外设时钟  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
 	USART_DeInit(USART1);  //复位串口1
	
	//USART1引脚复用
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);    
  
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//NVIC中断初始化
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
 USART_Cmd(USART1, ENABLE); //使能串口 
	USART_ClearFlag(USART1, USART_FLAG_TC);  //清除中断标志
	 
}
/***********************************************************************************************
* Function Name  : USART1_IRQHandler (void) 
* Description    : USART1串口接收中断
* Input          : None
* Output         : None 
* Return         : None 
* Contributor	: 2018-6-15
***********************************************************************************************/
void USART1_IRQHandler (void)
{
	uint16_t temp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)   //Receive Data register not empty interrupt.接收数据寄存器不空中断。
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		temp = USART_ReceiveData(USART1);   
		USART_SendData(USART1,temp);
	}
}
/***********************************************************************************************
* Function Name  : USART1_send(void * buf,uint8_t size) 
* Description    : 串口发送
* Input          : buf-->数据指针；size-->数据长度
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
* Description    : printf输出重定向
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
void usart2_init(uint32_t bound,uint32_t Parity) //uart 初始化
{
	//USART2 端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//485控制模式,方向选择
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
	
	//NVIC初始化
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
    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启中断
	USART_Cmd(USART2, ENABLE);  //使能串口 
	USART_ClearFlag(USART2, USART_FLAG_TC);  //清除中断标志
}

/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void USART3_Initial(uint32_t bound,uint32_t Parity)
{
    //USART3 端口设置
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
	
	//NVIC初始化
	NVIC_InitStructure.NVIC_IRQChannel=USART3_6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART3 configuration
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_Parity=Parity;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	USART_Init(USART3, &USART_InitStructure);
	
 	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
	USART_ClearFlag(USART3, USART_FLAG_TC); //清除中断标志
}

/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void USART4_Initial(uint32_t bound,uint32_t Parity)
{
	//USART4 端口设置
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
	
	//NVIC初始化
	NVIC_InitStructure.NVIC_IRQChannel=USART3_6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART4 configuration
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_Parity=Parity;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
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
	USART_ClearFlag(USART4, USART_FLAG_TC); //清除中断标志
}

/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
*******************************************************************************/
void USART5_Initial(uint32_t bound,uint32_t Parity)
{
	//USART5 端口设置
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
	
	//NVIC初始化
	NVIC_InitStructure.NVIC_IRQChannel=USART3_6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART5 configuration
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_Parity=Parity;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART5, &USART_InitStructure);
	
 	USART_ITConfig(USART5, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART5, ENABLE);
	//USART_ClearFlag(USART5, USART_FLAG_TC); //清除中断标志
}
