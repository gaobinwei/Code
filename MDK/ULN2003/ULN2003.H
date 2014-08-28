#ifndef __ULN2003_H
#define __ULN2003_H 			   
#include "stm32f10x.h"

#define CH1_H  GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define CH1_L  GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define CH2_H  GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define CH2_L  GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define CH3_H  GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define CH3_L  GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define CH4_H  GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define CH4_L  GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define CH5_H  GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define CH5_L  GPIO_ResetBits(GPIOB,GPIO_Pin_3)

void Channel_Config(void);

#endif
