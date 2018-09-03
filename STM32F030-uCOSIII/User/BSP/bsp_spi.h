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
* Description    : Spi 读写函数
* Input          : Data：要发送的字节
* Output         : None 
* Return         : 接收到的字节
* Contributor	: 2018-6-21
***********************************************************************************************/
uint8_t Spi_ReadWrite(uint8_t Data);

/***********************************************************************************************
* Function Name  : Spi_SendToAtt7053()
* Description    : Spi 向ATT7053发送数据接口
* Input          : Adress：ATT7053地址  Data：要发送的数据
* Output         : None 
* Return         : None
* Contributor	: 2018-6-21
***********************************************************************************************/
void Spi_SendToAtt7053(uint8_t Address ,uint32_t Data);

/***********************************************************************************************
* Function Name  : SpiRead()
* Description    : Spi 从ATT7053发送数据接口
* Input          : Adress：ATT7053地址 
* Output         : None 
* Return         : 接受到的数据
* Contributor	: 2018-6-21
***********************************************************************************************/
uint32_t Spi_Read(uint8_t Address);


/***********************************************************************************************
* Function Name  : Spi_Init()
* Description    : 初始化Spi 
* Input          : None
* Output         : None 
* Return         : 初始化成功标志
* Contributor	: 2018-6-20
***********************************************************************************************/
int Spi_Init(void);

/***********************************************************************************************
* Function Name  : MeasureInit()
* Description    : 初始化Spi接口
* Input          : None
* Output         : None 
* Return         : 初始化成功标志 
* Contributor	: 2018-6-20
***********************************************************************************************/
int MeasureInit(void);

/***********************************************************************************************
* Function Name  : MeasureReadCurrent()
* Description    : 获取当前电流
* Input          : 电流采样通道编号
* Output         : None 
* Return         : 当前电流
* Contributor	: 2018-6-25
***********************************************************************************************/
uint32_t MeasureReadCurrent(uint8_t channel);

/***********************************************************************************************
* Function Name  : MeasureInit()
* Description    : 获取当前电压
* Input          : None
* Output         : None 
* Return         : 当前电压
* Contributor	: 2018-6-25
***********************************************************************************************/
uint32_t MeasureReadVoltage(void);
#endif
