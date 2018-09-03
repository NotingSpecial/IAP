#ifndef  __BSP_INIT_H__
#define  __BSP_INIT_H__
/* Includes-----------------------------------------------------------------------------------*/
#include "includes.h"
/***********************************************************************************************
* Function		: uart1Init(void)
* Description	: uart1�������ų�ʼ������
* Input			  : None
* Output		  : None
* Note(s)		  : None
* Contributor	: 15/6/2018	
***********************************************************************************************/
void uart1Init(void);
/***********************************************************************************************
* Function		: USART1_send(void * buf,uint8_t size);
* Description	: USART1���ͺ���
* Input			  : buf-->����ָ�룻size-->���ݴ�С
* Output		  : None
* Note(s)		  : None
* Contributor	: 15/6/2018	
***********************************************************************************************/
void USART1_send(void * buf,uint8_t size);

#endif
