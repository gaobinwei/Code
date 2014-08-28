#include "delay.h" 
void delay_ms(u32 t )
{
  //u32 t;
  SysTick->LOAD=9000*t;
  SysTick->VAL=0X00; //��ռ�����
  SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
  do
  {
    t=SysTick->CTRL; //��ȡ��ǰ������ֵ
  }
  while((t&0X01)&&(!(t&(1<<16)))); //�ȴ�ʱ�䵽��
  SysTick->CTRL=0X00;//�رռ�����
  SysTick->VAL=0X00; //��ռ�����
} 

void delay_us(u32 t)
{
  //u32 t;
  SysTick->LOAD=9*t;
  SysTick->VAL=0X00; //��ռ�����
  SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
  do
  {
    t=SysTick->CTRL; //��ȡ��ǰ������ֵ
  }
  while((t&0X01)&&(!(t&(1<<16)))); //�ȴ�ʱ�䵽��
  SysTick->CTRL=0X00;//�رռ�����
  SysTick->VAL=0X00; //��ռ�����
}
