#ifndef  __BSP_INIT_H__
#define  __BSP_INIT_H__
/* Includes-----------------------------------------------------------------------------------*/
#include "includes.h"
/***********************************************************************************************
* Function		: uart1Init(void)
* Description	: uart1控制引脚初始化函数
* Input			  : None
* Output		  : None
* Note(s)		  : None
* Contributor	: 15/6/2018	
***********************************************************************************************/
void uart1Init(void);
/***********************************************************************************************
* Function		: USART1_send(void * buf,uint8_t size);
* Description	: USART1发送函数
* Input			  : buf-->数据指针；size-->数据大小
* Output		  : None
* Note(s)		  : None
* Contributor	: 15/6/2018	
***********************************************************************************************/
void USART1_send(void * buf,uint8_t size);

#endif
