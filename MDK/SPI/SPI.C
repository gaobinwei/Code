#include "stm32f10x.h"
#include"spi.h"
	
#define CS_ADC_L    GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//Ƭѡ
#define CS_ADC_H    GPIO_SetBits(GPIOA,GPIO_Pin_4)	//Ƭѡ	
/*******************************************************************
*˵����SPI��дһ���ֽ�
*���룺
*�����
*���أ�
********************************************************************/
u8 SPI1_ReadWriteByte(u8 TxDat)
{		
    CS_ADC_L ;			 
/*===================дһ���ֽ�=========================*/
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET); //���ָ����SPI��־λ�������:���ͻ���ձ�־λ	  
    SPI_I2S_SendData(SPI1, TxDat); //ͨ������SPIx����һ������

/*===================��һ���ֽ�=========================*/
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET); //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
    CS_ADC_H ;	  						    
    return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}

/*******************************************************************
*˵����SPI1��ʼ��
*���룺
*�����
*���أ�
********************************************************************/
void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA |RCC_APB2Periph_SPI1 |RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO, ENABLE );	
/*==================TM7705 PB0 DRDY===============================*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         // adDrdy
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);		
/*==================TM7705 PA4 CS===============================*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            //CS  AD7705
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);		
/*=================TM7705 PA5-CLK  PA6-DOUT PA7-DIN==============*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;     //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
/*======================SPI1����=================================*/
    SPI_Cmd(SPI1, DISABLE); //ʧ����SPI����
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		        //����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		              //ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	              //���ݲ����ڵڶ���ʱ��
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		           //NSS�ź���Ӳ����NSS�ܽţ�����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;	                        //CRCֵ����Ķ���ʽ
    SPI_Init(SPI1, &SPI_InitStructure);                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
  													 
    SPI_Cmd(SPI1, ENABLE);   //ʹ��SPI����
    CS_ADC_L;	
    SPI1_ReadWriteByte(0xff);//��������		 
    CS_ADC_H;

}
