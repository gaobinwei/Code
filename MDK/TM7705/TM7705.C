#include "stm32f10x.h"
#include"delay.h"	
#include"SPI.h"
#include"TM7705.h"

#define CS_ADC_L    GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//Ƭѡ
#define CS_ADC_H    GPIO_SetBits(GPIOA,GPIO_Pin_4)	//Ƭѡ
/*******************************************************************
*˵����TM7705��ʼ������
*���룺
*�����
*���أ�
********************************************************************/
void TM7705_Init() 
{
    u8 i;
    for(i=0;i<40;i++)/* ��������32�� DIN=1 ʹ���ڸ�λ */ 
     {
        SPI1_ReadWriteByte(0xff);//����DIN�ߵ�ƽд�������ָ�AD7705�ӿ�
     }  
    SPI1_ReadWriteByte(0x20); // ѡ��ʱ�ӼĴ�����д����������ģʽ��
    delay_ms(1);
    SPI1_ReadWriteByte(0x04); //4.9152MHzʱ�ӣ�50Hz���ݸ�������  
    delay_ms(1);
    SPI1_ReadWriteByte(0x10); //ѡ�����üĴ���,ʹ��CH1
    delay_ms(1);
    SPI1_ReadWriteByte(0x44); //д���üĴ��� ,���óɵ����ԡ��޻��塢����Ϊ1���˲�����������У׼
    delay_ms(50);
}


/*******************************************************************
*˵������TM7705 16λ����
*���룺
*�����
*���أ�
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
    CS_ADC_H;   //ȡ��Ƭѡ 	
    DataH=DataH << 8; 
    temp1=DataH | DataL; 
    return temp1; 

}
