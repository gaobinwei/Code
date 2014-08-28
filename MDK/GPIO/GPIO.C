#include "stm32f10x.h"
#include "GPIO.h"

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO , ENABLE);
    
	/*================USART_485 TX-PA9  RX-PA10 DE-PB11=================*/	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	  //USART_485_TX       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);		   

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	  //USART_485_RX       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_Init(GPIOA, &GPIO_InitStructure);		       
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	  //USART_485_DE    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*================ID1-PB12  ID2-PB13 ID3-PB14 ID4-PB15 =================*/	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	              
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
u8 Read_address(void)	   //读取STM32管脚电平，计算成485从机ID地址
{
    u8 Addrsss_value=0;
	
	if(Address1)	 //=0
	  {
	    Addrsss_value|=0x01;   //0|1=1
	  }
	if(Address2)	 //1x
	  {
	    Addrsss_value|=0x02; //	1x|1=11
	  }
	if(Address3)	 //1xx
	  {
	    Addrsss_value|=0x04; // 1xx|11=111
	  }
	if(Address4)	 //1xxx
	  {
	    Addrsss_value|=0x08;  //1xxx|111=11111
	  }
	return  Addrsss_value;
}
