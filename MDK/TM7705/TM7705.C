#include "stm32f10x.h"
#include"delay.h"	
#include"SPI.h"
#include"TM7705.h"

#define CS_ADC_L    GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//片选
#define CS_ADC_H    GPIO_SetBits(GPIOA,GPIO_Pin_4)	//片选
/*******************************************************************
*说明：TM7705初始化函数
*输入：
*输出：
*返回：
********************************************************************/
void TM7705_Init() 
{
    u8 i;
    for(i=0;i<40;i++)/* 多于连续32个 DIN=1 使串口复位 */ 
     {
        SPI1_ReadWriteByte(0xff);//持续DIN高电平写操作，恢复AD7705接口
     }  
    SPI1_ReadWriteByte(0x20); // 选择时钟寄存器，写操作，正常模式，
    delay_ms(1);
    SPI1_ReadWriteByte(0x04); //4.9152MHz时钟，50Hz数据更新速率  
    delay_ms(1);
    SPI1_ReadWriteByte(0x10); //选择设置寄存器,使用CH1
    delay_ms(1);
    SPI1_ReadWriteByte(0x44); //写设置寄存器 ,设置成单极性、无缓冲、增益为1、滤波器工作、自校准
    delay_ms(50);
}


/*******************************************************************
*说明：读TM7705 16位数据
*输入：
*输出：
*返回：
********************************************************************/
u16 Read7705_16Bit()
{
    u16 temp1 = 0;
    u16 DataL = 0;
    u16 DataH = 0;
    TM7705_Init();
    SPI1_ReadWriteByte(0x38);
    while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0 )==1); 
    CS_ADC_L;
    delay_us(20);
    DataH=SPI1_ReadWriteByte(0xff);
    DataL=SPI1_ReadWriteByte(0xff); 
    delay_us(100);
    CS_ADC_H;   //取消片选 	
    DataH=DataH << 8; 
    temp1=DataH | DataL; 
    return temp1; 

}
