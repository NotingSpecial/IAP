#ifndef  __BSP_INIT_H__
#define  __BSP_INIT_H__


/* Includes-----------------------------------------------------------------------------------*/
#include "includes.h"


/**********************************LED变色操作类型*********************************************/
#define LED_GRE_ON_CH2() 		{ GPIO_SetBits(GPIOA,GPIO_Pin_15); GPIO_ResetBits(GPIOB,GPIO_Pin_13); GPIO_ResetBits(GPIOB,GPIO_Pin_14);}
#define LED_RED_ON_CH2() 		{ GPIO_ResetBits(GPIOA,GPIO_Pin_15); GPIO_SetBits(GPIOB,GPIO_Pin_13); GPIO_ResetBits(GPIOB,GPIO_Pin_14);}
#define LED_YEL_ON_CH2()		{ GPIO_ResetBits(GPIOA,GPIO_Pin_15); GPIO_ResetBits(GPIOB,GPIO_Pin_13); GPIO_SetBits(GPIOB,GPIO_Pin_14);}
#define LED_GRE_ON_CH1() 		{ GPIO_SetBits(GPIOA,GPIO_Pin_7); GPIO_ResetBits(GPIOB,GPIO_Pin_0); GPIO_ResetBits(GPIOB,GPIO_Pin_1);}
#define LED_RED_ON_CH1() 		{ GPIO_ResetBits(GPIOA,GPIO_Pin_7); GPIO_SetBits(GPIOB,GPIO_Pin_0); GPIO_ResetBits(GPIOB,GPIO_Pin_1);}
#define LED_YEL_ON_CH1()		{ GPIO_ResetBits(GPIOA,GPIO_Pin_7); GPIO_ResetBits(GPIOB,GPIO_Pin_0); GPIO_SetBits(GPIOB,GPIO_Pin_1);}

/***********************************************************************************************
* Function		: ledInit(void)
* Description	: LED控制引脚初始化函数
* Input			  : None
* Output		  : None
* Note(s)		  : None
* Contributor	: 15/6/2018	
***********************************************************************************************/
void ledInit(void);

#endif
