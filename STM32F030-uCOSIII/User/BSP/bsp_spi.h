#ifndef  __BSP_INIT_H__
#define  __BSP_INIT_H__

#include "includes.h"

#define SPI_CS_L()   GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SPI_CS_H()   GPIO_SetBits(GPIOB,GPIO_Pin_12)
extern int MeasureInit(void);
extern uint32_t MeasureReadVoltage(void);

//extern void Spi_SendToAtt7053(uint8_t Address ,uint32_t Data) ;
//extern int Spi_Init(void);
//extern uint32_t Spi_Read(uint8_t Address);


/***********************************************************************************************
* Function Name  : Spi_ReadWrite()
* Description    : Spi ��д����
* Input          : Data��Ҫ���͵��ֽ�
* Output         : None 
* Return         : ���յ����ֽ�
* Contributor	: 2018-6-21
***********************************************************************************************/
uint8_t Spi_ReadWrite(uint8_t Data);

/***********************************************************************************************
* Function Name  : Spi_SendToAtt7053()
* Description    : Spi ��ATT7053�������ݽӿ�
* Input          : Adress��ATT7053��ַ  Data��Ҫ���͵�����
* Output         : None 
* Return         : None
* Contributor	: 2018-6-21
***********************************************************************************************/
void Spi_SendToAtt7053(uint8_t Address ,uint32_t Data);

/***********************************************************************************************
* Function Name  : SpiRead()
* Description    : Spi ��ATT7053�������ݽӿ�
* Input          : Adress��ATT7053��ַ 
* Output         : None 
* Return         : ���ܵ�������
* Contributor	: 2018-6-21
***********************************************************************************************/
uint32_t Spi_Read(uint8_t Address);


/***********************************************************************************************
* Function Name  : Spi_Init()
* Description    : ��ʼ��Spi 
* Input          : None
* Output         : None 
* Return         : ��ʼ���ɹ���־
* Contributor	: 2018-6-20
***********************************************************************************************/
int Spi_Init(void);

/***********************************************************************************************
* Function Name  : MeasureInit()
* Description    : ��ʼ��Spi�ӿ�
* Input          : None
* Output         : None 
* Return         : ��ʼ���ɹ���־ 
* Contributor	: 2018-6-20
***********************************************************************************************/
int MeasureInit(void);

/***********************************************************************************************
* Function Name  : MeasureReadCurrent()
* Description    : ��ȡ��ǰ����
* Input          : ��������ͨ�����
* Output         : None 
* Return         : ��ǰ����
* Contributor	: 2018-6-25
***********************************************************************************************/
uint32_t MeasureReadCurrent(uint8_t channel);

/***********************************************************************************************
* Function Name  : MeasureInit()
* Description    : ��ȡ��ǰ��ѹ
* Input          : None
* Output         : None 
* Return         : ��ǰ��ѹ
* Contributor	: 2018-6-25
***********************************************************************************************/
uint32_t MeasureReadVoltage(void);
#endif
