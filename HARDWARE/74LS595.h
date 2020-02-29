#ifndef _74LS595_H
#define _74LS595_H
#include "pbdata.h"

#define SCK_595_PIN           	GPIO_Pin_3 
#define SCK_595_GPIO          	GPIOB 
#define SCK_595_GPIO_CLK      	RCC_AHB1Periph_GPIOB 
#define SCK_595_H()           	GPIO_SetBits(SCK_595_GPIO,SCK_595_PIN);
#define SCK_595_L()           	GPIO_ResetBits(SCK_595_GPIO,SCK_595_PIN);
 
#define RCK_595_PIN          	GPIO_Pin_6 
#define RCK_595_GPIO            GPIOC 
#define RCK_595_GPIO_CLK        RCC_AHB1Periph_GPIOC 
#define RCK_595_H()             GPIO_SetBits(RCK_595_GPIO,RCK_595_PIN);
#define RCK_595_L()         	GPIO_ResetBits(RCK_595_GPIO,RCK_595_PIN);
 
#define SI_595_PIN        		GPIO_Pin_3 
#define SI_595_GPIO         	GPIOI 
#define SI_595_GPIO_CLK    	 	RCC_AHB1Periph_GPIOI 
#define SI_595_H()          	GPIO_SetBits(SI_595_GPIO,SI_595_PIN);
#define SI_595_L()         	 	GPIO_ResetBits(SI_595_GPIO,SI_595_PIN);


#define SH_CP_H  GPIO_SetBits(GPIOB,GPIO_Pin_3);
#define SH_CP_L  GPIO_ResetBits(GPIOB,GPIO_Pin_3);

#define DS_H  GPIO_SetBits(GPIOI,GPIO_Pin_3);
#define DS_L  GPIO_ResetBits(GPIOI,GPIO_Pin_3);

#define ST_CP_H  GPIO_SetBits(GPIOC,GPIO_Pin_6);
#define ST_CP_L  GPIO_ResetBits(GPIOC,GPIO_Pin_6);

void In_595();
void LED595SendData(void);
#endif