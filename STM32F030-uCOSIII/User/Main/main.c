/*****************************************Copyright(C)******************************************
*******************************************�Ĵ��׳�*********************************************
*------------------------------------------�ļ���Ϣ---------------------------------------------
* FileName			: main.c
* Author			  :      
* Version			  : V1.0
* Description		: �Ĵ��׳佻�����׮��Ŀ�������
*----------------------------------------��ʷ�汾��Ϣ-------------------------------------------
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
    MSR MSP, r0 			//����main������ڵ�ַ
    BX r14
}


void Iap_load( uint32_t Iapaddr)
{
	if(((*(uint32_t*)Iapaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ 
		jumpapp=(void(*)())*(uint32_t*)(Iapaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(uint32_t*)Iapaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		for(int i = 0; i < 8; i++)
		{			
			NVIC->ICER[i] = 0xFFFFFFFF;	/* �ر��ж�*/
			NVIC->ICPR[i] = 0xFFFFFFFF;	/* ����жϱ�־λ */
		}
		jumpapp();									//��ת��APP.
	}
}

void Delayms (uint16_t time)
{
		time_delay = time ;
		SysTick_Config(SystemCoreClock/1000);
		while(time_delay);
		SysTick->CTRL=0x00; //�رռ�����
    SysTick->VAL =0X00; //��ռ�����
} 

/***********************************************************************************************
* Function		: main(void)
* Description	: �Ĵ��׳佻�����׮ �������������
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


/************************ (C) COPYRIGHT 2018 �Ĵ��׳� ************END OF FILE************/
