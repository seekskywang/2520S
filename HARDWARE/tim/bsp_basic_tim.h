#ifndef __BASIC_TIM_H
#define	__BASIC_TIM_H

#include "stm32f4xx.h"

#define BASIC_TIM           		TIM6
#define BASIC_TIM_CLK       		RCC_APB1Periph_TIM6

#define BASIC_TIM_IRQn					TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler    TIM6_DAC_IRQHandler

#define S_RX_BUF_SIZE		30
#define S_TX_BUF_SIZE		128

#define RSP_OK				0		/* ?? */
#define RSP_ERR_CMD			0x01	/* ??????? */
#define RSP_ERR_REG_ADDR	0x02	/* ??????? */
#define RSP_ERR_VALUE		0x03	/* ?????? */
#define RSP_ERR_WRITE		0x04	/* §Õ??? */

#define SLAVE_REG_P00		0x0000       //R_VOLU
#define SLAVE_REG_P01		0x0001      //Load_Voltage
#define SLAVE_REG_P02		0x0002      //Load_Current
#define SLAVE_REG_P03		0x0003		//Change_Voltage
#define SLAVE_REG_P04		0x0004		//Change_Current
#define SLAVE_REG_P05		0x0005		//Load_OCP
#define SLAVE_REG_P06		0x0006		//Change_OCP
#define SLAVE_REG_P07		0x0007		//Short_Time
#define SLAVE_REG_P08		0x0008		//Leak_Current
#define SLAVE_REG_P09		0x0009		//R1_Volu
#define SLAVE_REG_P10		0x000A		//R2_Volu
#define SLAVE_REG_P11		0x000B		//Temper
#define SLAVE_REG_P12		0x000C		//DHQ_Voltage
#define SLAVE_REG_P13		0x000D		//MODE
#define SLAVE_REG_P14		0x000E		//Load_Mode
#define SLAVE_REG_P15		0x000F		//Load_SET_Voltage
#define SLAVE_REG_P16		0x0010		//Load_SET_Current
#define SLAVE_REG_P17		0x0011		//Change_SET_Voltage
#define SLAVE_REG_P18		0x0012		//Change_SET_Current
#define SLAVE_REG_P19		0x0013		//Change_SET_Current
#define SLAVE_REG_P20		0x0014		//Change_SET_Current
#define SLAVE_REG_P21		0x0015		//Change_SET_Current
#define SLAVE_REG_P22		0x0016		//Change_SET_Current
#define SLAVE_REG_P23		0x0017		//Change_SET_Current
#define SLAVE_REG_P24		0x0018		//Change_SET_Current
#define SLAVE_REG_P25		0x0019		//Change_SET_Current
#define SLAVE_REG_P26		0x001A		//Change_SET_Current
#define SLAVE_REG_P27		0x001B		//Change_SET_Current
#define SLAVE_REG_P28		0x001C		//Change_SET_Current
#define SLAVE_REG_P29		0x001D		//Change_SET_Current
#define SLAVE_REG_P30		0x001E       //R_VOLU
#define SLAVE_REG_P31		0x001F      //Load_Voltage
#define SLAVE_REG_P32		0x0020      //Load_Current
#define SLAVE_REG_P33		0x0021		//Change_Voltage
#define SLAVE_REG_P34		0x0022		//Change_Current
#define SLAVE_REG_P35		0x0023		//Load_OCP
#define SLAVE_REG_P36		0x0024		//Change_OCP
#define SLAVE_REG_P37		0x0025		//Short_Time
#define SLAVE_REG_P38		0x0026		//Leak_Current
#define SLAVE_REG_P39		0x0027		//R1_Volu
#define SLAVE_REG_P40		0x0028		//R2_Volu
#define SLAVE_REG_P41		0x0029		//Temper
#define SLAVE_REG_P42		0x002A		//DHQ_Voltage
#define SLAVE_REG_P43		0x002B		//MODE
#define SLAVE_REG_P44		0x002C		//Load_Mode
#define SLAVE_REG_P45		0x002D		//Load_SET_Voltage
#define SLAVE_REG_P46		0x002E		//Load_SET_Current
#define SLAVE_REG_P47		0x002F		//Change_SET_Voltage
#define SLAVE_REG_P48		0x0030		//Change_SET_Current
#define SLAVE_REG_P49		0x0031		//Change_SET_Current
#define SLAVE_REG_P50		0x0032		//Change_SET_Current
#define SLAVE_REG_P51		0x0033		//Change_SET_Current
#define SLAVE_REG_P52		0x0034		//Change_SET_Current
#define SLAVE_REG_P53		0x0035		//Change_SET_Current
#define SLAVE_REG_P54		0x0036		//Change_SET_Current
#define SLAVE_REG_P55		0x0037		//Change_SET_Current
#define SLAVE_REG_P56		0x0038		//Change_SET_Current
#define SLAVE_REG_P57		0x0039		//Change_SET_Current
#define SLAVE_REG_P58		0x003A		//Change_SET_Current
#define SLAVE_REG_P59		0x003B		//Change_SET_Current

struct MODS_T
{
	uint8_t RxBuf[S_RX_BUF_SIZE];
	uint8_t TxBuf[S_TX_BUF_SIZE];
	uint8_t RxCount;
	uint8_t RxStatus;
	uint8_t RxNewFlag;
	uint8_t RspCode;
	
	uint8_t TxCount;
};

void TIM6_Configuration(void);

#endif /* __BASIC_TIM_H */

