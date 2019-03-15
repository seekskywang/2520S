#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


#define DEBUG_USART                             USART3
#define DEBUG_USART_CLK                         RCC_APB1Periph_USART3
#define DEBUG_USART_BAUDRATE                    9600

#define DEBUG_USART_RX_GPIO_PORT                GPIOB
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define DEBUG_USART_RX_PIN                      GPIO_Pin_11
#define DEBUG_USART_RX_AF                       GPIO_AF_USART3
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource11

#define DEBUG_USART_TX_GPIO_PORT                GPIOB
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define DEBUG_USART_TX_PIN                      GPIO_Pin_10
#define DEBUG_USART_TX_AF                       GPIO_AF_USART3
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource10


#define __DEBUG 	//¿ªÆô´®¿Úµ÷ÊÔ

#ifdef  __DEBUG
#define DEBUG(format,...)	printf("File:"__FILE__",Line:%03d:"format"\n",__LINE__,##__VA_ARGS__) 
#else

#define DEBUG(format,...)

#endif


void Debug_USART_Config(void);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Send_Uart3str(char *str);





#endif /* __USART1_H */
