#include "includes.h"
#define SPI_CS_L()   GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SPI_CS_H()   GPIO_SetBits(GPIOB,GPIO_Pin_12)

/***********************************************************************************************
* Function Name  : Spi_ReadWrite()
* Description    : Spi ��д����
* Input          : Data��Ҫ���͵��ֽ�
* Output         : None 
* Return         : ���յ����ֽ�
* Contributor	: 2018-6-21
***********************************************************************************************/
uint8_t Spi_ReadWrite(uint8_t Data)
{

		while((SPI2->SR&SPI_I2S_FLAG_TXE)==(uint16_t)RESET);
		SPI_SendData8(SPI2,Data);

		while((SPI2->SR&SPI_I2S_FLAG_RXNE)==(uint16_t)RESET);
		return SPI_ReceiveData8(SPI2);
 
}

/***********************************************************************************************
* Function Name  : Spi_SendToAtt7053()
* Description    : Spi ��ATT7053�������ݽӿ�
* Input          : Adress��ATT7053��ַ  Data��Ҫ���͵�����
* Output         : None 
* Return         : None
* Contributor	: 2018-6-21
***********************************************************************************************/
void Spi_SendToAtt7053(uint8_t Address ,uint32_t Data)
{
	
		SPI_CS_L();	//Enable CS 
		
		Spi_ReadWrite(Address);
		
		Spi_ReadWrite((uint8_t)((Data)>>16));
		Spi_ReadWrite((uint8_t)((Data)>>8));
		Spi_ReadWrite((uint8_t)Data);
		
		SPI_CS_H();//Dissable
}

/***********************************************************************************************
* Function Name  : SpiRead()
* Description    : Spi ��ATT7053�������ݽӿ�
* Input          : Adress��ATT7053��ַ 
* Output         : None 
* Return         : ���ܵ�������
* Contributor	: 2018-6-21
***********************************************************************************************/
uint32_t Spi_Read(uint8_t Address)
{
		uint32_t Spi_Data = 0x00000000;
		SPI_CS_H();
		SPI_CS_L();//Enable cs
	
		Spi_ReadWrite(Address);
		Spi_Data |= (((uint32_t)Spi_ReadWrite(0xff))<<16);
		Spi_Data |= (((uint32_t)Spi_ReadWrite(0xff))<<8);
		Spi_Data |= ((uint32_t)Spi_ReadWrite(0xff));
	
		SPI_CS_H();//Dissable
	
		return Spi_Data;
}

/***********************************************************************************************
* Function Name  : Spi_Init()
* Description    : ��ʼ��Spi 
* Input          : None
* Output         : None 
* Return         : ��ʼ����־ 
* Contributor	: 2018-6-20
***********************************************************************************************/
int Spi_Init()
{
		uint32_t result ; 
		GPIO_InitTypeDef GPIO_InitStructure;
		SPI_InitTypeDef SPI_InitStructure; 

		//��ʱ��
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
			
		//GPIO����(MISO��MOSI��SCK)
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
		//GPIO����(CS)
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		//GPIO����
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_0);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_0);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_0);

		//spi�ӿ�����
		SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_256;
		SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial=7;

		SPI_Init(SPI2,&SPI_InitStructure);
		SPI_RxFIFOThresholdConfig(SPI2 ,SPI_RxFIFOThreshold_QF );
		SPI_Cmd(SPI2,ENABLE);
		
		
		result = Spi_Read(0x1c);
		Spi_SendToAtt7053(0x32,0xa6);//д������ֻ�ܲ����Ĵ���50h~7ch
		Spi_SendToAtt7053(0x61,0x012c);
		Spi_SendToAtt7053(0x50,0xffcc);
		Spi_SendToAtt7053(0x51,0xffcc);
		Spi_SendToAtt7053(0x52,0xffcc);
		if ( result == 0x7053B0 )
		return 0;
		else 
		return  -1;

}

/***********************************************************************************************
* Function Name  : Spi_Init()
* Description    : ��ʼ��Spi�ӿ�
* Input          : None
* Output         : None 
* Return         : flag :��ʼ���ɹ���־
* Contributor	: 2018-6-20
***********************************************************************************************/
int MeasureInit(void)
{
	int Flag = Spi_Init();
	return Flag ;
}

/***********************************************************************************************
* Function Name  : MeasureReadCurrent()
* Description    : ��ȡ��ǰ����
* Input          : ��������ͨ�����
* Output         : None 
* Return         : ��ǰ����
* Contributor	: 2018-6-25
***********************************************************************************************/
uint32_t MeasureReadCurrent(uint8_t channel)
{	
	uint32_t Cur ;
	if(channel  == 1)Cur = Spi_Read(0x06)/89395.7;//ͨ��1��������
	else if (channel == 2) Cur = Spi_Read(0x07)/89395.7;//ͨ��2��������
	return Cur;
}

/***********************************************************************************************
* Function Name  : MeasureInit()
* Description    : ��ȡ��ǰ��ѹ
* Input          : None
* Output         : None 
* Return         : ��ǰ��ѹ
* Contributor	: 2018-6-25
***********************************************************************************************/
uint32_t MeasureReadVoltage(void)
{
	uint32_t vol ;
	vol = Spi_Read(0x08)/6759.6;//���㵱ǰ��ѹ
	if(vol<1)vol = 0;
	return vol ;
}
