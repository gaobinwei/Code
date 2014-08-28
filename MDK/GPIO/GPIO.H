#ifndef __GPIO_H
#define __GPIO_H 			   
#include "stm32f10x.h"

void GPIO_Config(void);
#define Address1  GPIO_ReadInputDataBit(GPIOB  ,GPIO_Pin_15)
#define Address2  GPIO_ReadInputDataBit(GPIOB  ,GPIO_Pin_14)
#define Address3  GPIO_ReadInputDataBit(GPIOB  ,GPIO_Pin_13)
#define Address4  GPIO_ReadInputDataBit(GPIOB  ,GPIO_Pin_12)
u8 Read_address(void);

#endif
