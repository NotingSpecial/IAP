/*****************************************Copyright(C)******************************************
*******************************************四川首充*********************************************
*------------------------------------------文件信息---------------------------------------------
* FileName			: main.c
* Author			  :      
* Version			  : V1.0
* Description		: 四川首充交流充电桩项目工程软件
*----------------------------------------历史版本信息-------------------------------------------
* History			  :
* Description		: 
*-----------------------------------------------------------------------------------------------
***********************************************************************************************/
/* Includes-----------------------------------------------------------------------------------*/
#include <includes.h>
#define FLASH_APP_ADDR  0x8003000

uint16_t time_delay;
typedef void (*Fun)(void);
Fun jumpapp ;

__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			//设置main函数入口地址
    BX r14
}


void Iap_load( uint32_t Iapaddr)
{
	if(((*(uint32_t*)Iapaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		jumpapp=(void(*)())*(uint32_t*)(Iapaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(uint32_t*)Iapaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		for(int i = 0; i < 8; i++)
		{			
			NVIC->ICER[i] = 0xFFFFFFFF;	/* 关闭中断*/
			NVIC->ICPR[i] = 0xFFFFFFFF;	/* 清除中断标志位 */
		}
		jumpapp();									//跳转到APP.
	}
}

void Delayms (uint16_t time)
{
		time_delay = time ;
		SysTick_Config(SystemCoreClock/1000);
		while(time_delay);
		SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
} 

/***********************************************************************************************
* Function		: main(void)
* Description	: 四川首充交流充电桩 工程软件主程序
* Input			  : None
* Output		  : None
* Note(s)		  : None
* Contributor	: 03/09/2018
***********************************************************************************************/
int main(void)
{
		//SysTick_Config(SystemCoreClock/1000);
    ledInit();
		
		while(1)
		{
				LED_GRE_ON_CH1();  
				Delayms(1000);
				LED_RED_ON_CH1();
//				Delayms(1000);
//				LED_YEL_ON_CH1();
				Delayms(3000);
				Iap_load(FLASH_APP_ADDR);
		}
	


}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT 2018 四川首充 ************END OF FILE************/
