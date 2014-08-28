#include "stm32f10x.h"
#include"spi.h"
	
#define CS_ADC_L    GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//片选
#define CS_ADC_H    GPIO_SetBits(GPIOA,GPIO_Pin_4)	//片选	
/*******************************************************************
*说明：SPI读写一个字节
*输入：
*输出：
*返回：
********************************************************************/
u8 SPI1_ReadWriteByte(u8 TxDat)
{		
    CS_ADC_L ;			 
/*===================写一个字节=========================*/
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET); //检查指定的SPI标志位设置与否:发送缓存空标志位	  
    SPI_I2S_SendData(SPI1, TxDat); //通过外设SPIx发送一个数据

/*===================读一个字节=========================*/
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET); //检查指定的SPI标志位设置与否:接受缓存非空标志位
    CS_ADC_H ;	  						    
    return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据					    
}

/*******************************************************************
*说明：SPI1初始化
*输入：
*输出：
*返回：
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);		
/*=================TM7705 PA5-CLK  PA6-DOUT PA7-DIN==============*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;     //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
/*======================SPI1设置=================================*/
    SPI_Cmd(SPI1, DISABLE); //失能能SPI外设
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		        //设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		       //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		              //选择了串行时钟的稳态:时钟悬空高
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	              //数据捕获于第二个时钟
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		           //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//定义波特率预分频的值:波特率预分频值为256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;	                        //CRC值计算的多项式
    SPI_Init(SPI1, &SPI_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
  													 
    SPI_Cmd(SPI1, ENABLE);   //使能SPI外设
    CS_ADC_L;	
    SPI1_ReadWriteByte(0xff);//启动传输		 
    CS_ADC_H;

}
