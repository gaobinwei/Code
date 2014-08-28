#ifndef __USART_H
#define __USART_H

#include "platform_config.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define TX_485  GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define RX_485  GPIO_ResetBits(GPIOB,GPIO_Pin_11)
void USART1_Config(void);


#endif /* __USART_H */

