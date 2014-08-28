#include "delay.h" 
void delay_ms(u32 t )
{
  //u32 t;
  SysTick->LOAD=9000*t;
  SysTick->VAL=0X00; //清空计数器
  SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
  do
  {
    t=SysTick->CTRL; //读取当前倒计数值
  }
  while((t&0X01)&&(!(t&(1<<16)))); //等待时间到达
  SysTick->CTRL=0X00;//关闭计数器
  SysTick->VAL=0X00; //清空计数器
} 

void delay_us(u32 t)
{
  //u32 t;
  SysTick->LOAD=9*t;
  SysTick->VAL=0X00; //清空计数器
  SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
  do
  {
    t=SysTick->CTRL; //读取当前倒计数值
  }
  while((t&0X01)&&(!(t&(1<<16)))); //等待时间到达
  SysTick->CTRL=0X00;//关闭计数器
  SysTick->VAL=0X00; //清空计数器
}
