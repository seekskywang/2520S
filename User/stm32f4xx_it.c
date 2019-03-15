/**
  ******************************************************************************
  * @file    FMC_SDRAM/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "pbdata.h"
#include "usb_bsp.h"
#include "usb_hcd_int.h"
#include "usbh_core.h"
#include    "bsp_exti.h"
extern USB_OTG_CORE_HANDLE          USB_OTG_Core;
extern USBH_HOST                    USB_Host;
struct MODS_T g_tModS;
u8 g_mods_timeout = 0;
u32 Tick_10ms=0;
 
/* Private function prototypes -----------------------------------------------*/
extern void USB_OTG_BSP_TimerIRQ (void);
static void MODS_03H(void);
static void MODS_06H(void);
static void RemTrig(void);
//extern void Read__Convert_read(void);
/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
    
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    TimingDelay_Decrement();


}

/*
*********************************************************************************************************
*	? ? ?: MODS_SendAckErr
*	????: ??????
*	ю    ?: _ucErrCode : ????
*	? ? ?: ?
*********************************************************************************************************
*/
static void MODS_SendAckErr(uint8_t _ucErrCode)
{
	uint8_t txbuf[3];

	txbuf[0] = g_tModS.RxBuf[0];					/* 485?? */
	txbuf[1] = g_tModS.RxBuf[1] | 0x80;				/* ?????? */
	txbuf[2] = _ucErrCode;							/* ????(01,02,03,04) */

	MODS_SendWithCRC(txbuf, 3);
}


/*
*********************************************************************************************************
*	? ? ?: MODS_SendAckOk
*	????: ???????.
*	ю    ?: ?
*	? ? ?: ?
*********************************************************************************************************
*/
static void MODS_SendAckOk(void)
{
	uint8_t txbuf[6];
	uint8_t i;

	for (i = 0; i < 6; i++)
	{
		txbuf[i] = g_tModS.RxBuf[i];
	}
	MODS_SendWithCRC(txbuf, 6);
}

/*
*********************************************************************************************************
*	? ? ?: BEBufToUint16
*	????: ?2????(??Big Endian??ì?????)???16λ??
*	ю    ?: _pBuf : ??
*	? ? ?: 16λ???
*
*   ??(Big Endian)?С?(Little Endian)
*********************************************************************************************************
*/
uint16_t BEBufToUint16(uint8_t *_pBuf)
{
    return (((uint16_t)_pBuf[0] << 8) | _pBuf[1]);
}

void uart1SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { 
       USART_SendData(USART3,*(str + k));
       while (USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
       k++; 
       }   //????,??????   
    while (k < strlen); 
} 


 // CRC ?λ????
static const uint8_t s_CRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
// CRC ?λ????
const uint8_t s_CRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
	0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
	0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
	0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
	0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
	0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
	0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
	0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
	0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
	0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

uint16_t CRC16(uint8_t *_pBuf, uint16_t _usLen)
{    
    uint8_t ucCRCHi = 0xFF; /* ?CRC????? */
	uint8_t ucCRCLo = 0xFF; /* ?CRC ????? */
	uint16_t usIndex;  /* CRC?????? */

    while (_usLen--)
    {
		usIndex = ucCRCHi ^ *_pBuf++; /* ??CRC */
		ucCRCHi = ucCRCLo ^ s_CRCHi[usIndex];
		ucCRCLo = s_CRCLo[usIndex];
    }
    return ((uint16_t)ucCRCHi << 8 | ucCRCLo);
}


void MODS_SendWithCRC(uint8_t *_pBuf, uint8_t _ucLen)
{
	uint16_t crc;
	uint8_t buf[S_TX_BUF_SIZE];
	memcpy(buf, _pBuf, _ucLen);
	crc = CRC16(_pBuf, _ucLen);
	buf[_ucLen++] = crc >> 8;
	buf[_ucLen++] = crc;
//??485???
//	RS485_SendBuf(buf, _ucLen);

	uart1SendChars(buf, _ucLen);
	
// #if 1									/* ???????????,???????? */
// 	g_tPrint.Txlen = _ucLen;
// 	memcpy(g_tPrint.TxBuf, buf, _ucLen);
// #endif
}


void USART3_IRQHandler(void)
{
	u8 dat;

	if(( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET))//接收完成中断
	{
		g_mods_timeout = 2;
		if (g_tModS.RxCount < S_RX_BUF_SIZE)
		{
			g_tModS.RxBuf[g_tModS.RxCount++] = USART_ReceiveData(USART3);
		}
//		if (!ComBuf.rec.end)//接收没结束
//		{
//			SetRecTimeOut(REC_TIME_OUT);//设置接收超时周期
//			dat=USART_ReceiveData(USART3);
//			if (dat==(u8)(UART_REC_BEGIN))//帧头
//			{
//				if(ComBuf.rec.ptr!=0) //首字节
//				{
//					ComBuf.rec.ptr=0;//重新接收 
//				}
//				else
//				{
//					ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
//				}
//			}
//			else if (dat==(u8)(UART_REC_END))//帧尾
//			{
//				ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
//				ComBuf.rec.end=TRUE;//接收结束
//				ComBuf.rec.len=ComBuf.rec.ptr;//存接收数据长度
//				ComBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
//				ComBuf.rec.TimeOut=0;//接收超时清零
//			}
//			else
//			{
//				if (ComBuf.rec.ptr>=REC_LEN_MAX)//最大接收帧长度
//				{
//					ComBuf.rec.ptr=0;//重新接收
//				}
//				else
//				{
//					ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
//				}
//			}
//		}	
//        USART_ClearFlag(USART3, USART_FLAG_RXNE);
////		RI=0;//清接收标志
	}
    USART_ClearFlag(USART3, USART_FLAG_RXNE);//
    USART_ClearFlag(USART3, USART_FLAG_TXE);
    

//	if(( USART_GetFlagStatus(USART3, USART_FLAG_TXE) != RESET))//发送完成中断
//	{
//		if (ComBuf.send.begin)//发送开始
//		{
//			if (ComBuf.send.ptr<ComBuf.send.len)//没发送完继续
//			{
////				SBUF=ComBuf.send.buf[ComBuf.send.ptr++];
//                 USART_SendData(USART3, (uint8_t) ComBuf.send.buf[ComBuf.send.ptr++]); /*发送一个字符函数*/ 

//                  /* Loop until the end of transmission */
//                  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)/*等待发送完成*/
//                  {
//                  
//                  }
//			}
//			else
//			{
//				ComBuf.send.begin=FALSE;//发送结束
//				ComBuf.send.ptr=0;//指针清零
//			}
//		}
//USART_ClearFlag(USART3, USART_FLAG_TXE);//		TI=0;//清发送标志
//	}	
} 


void RecHandle(void)
{
    u8 crec[6];
    u8 *csend;
    static u8 *sendbuf;
    u8 sendlen;
    static u16 recrc;
    static u16 scrc;
    u8 i;
    
    switch(g_tModS.RxBuf[1])
    {
        case 0x03:
        {
            MODS_03H();
        }break;
        case 0x06:
        {
            MODS_06H();
        }break;
		case 0x54:
		{
			RemTrig();
		}
        default:break;
    }
}

static uint8_t MODS_ReadRegValue(uint16_t reg_addr, uint8_t *reg_value)
{
    uint16_t value;
	static u32 sendunit;
	static u32 sendrvalue;
	
//	switch(Jk510_Set.jk510_SSet.Range_set)
//	{
//		case 0:
//		{
//			sendrvalue = Test_Value.res;
//			sendunit = 0;
//		}break;
//		case 1:
//		{
//			sendrvalue = Test_Value.res * 10;
//			sendunit = 0;
//		}break;
//		case 2:
//		{
//			sendrvalue = Test_Value.res * 100;
//			sendunit = 0;
//		}break;
//		case 3:
//		{
//			sendrvalue = Test_Value.res;
//			sendunit = 1;
//		}break;
////		case 4:
////		{
////			sendrvalue = Test_Value.res * 10;
////			sendunit = 1;
////		}break;
////		case 5:
////		{
////			sendrvalue = Test_Value.res * 100;
////			sendunit = 1;
////		}break;
////		case 6:
////		{
////			sendrvalue = Test_Value.res;
////			sendunit = 2;
////		}break;
//		
//	}
//	lock = 1;
	switch (reg_addr)									/* ??????? */
	{
        case SLAVE_REG_P00:
//			value = (u16)(sendrvalue >> 16);
			value = (u16)(jk510_Disp.Disp_Res[0].res >> 16);		
			break;
		case SLAVE_REG_P01:
//            value = (u16)(sendrvalue);	
			value = (u16)(jk510_Disp.Disp_Res[0].res);
			break;

		case SLAVE_REG_P02:
			value = (u16)(jk510_Disp.Disp_V[0].res >> 16);
			break;
		case SLAVE_REG_P03: 
			value = (u16)(jk510_Disp.Disp_V[0].res);
			break;
		case SLAVE_REG_P04:
			value = jk510_Disp.Disp_Res[0].dot;				
			break;
		case SLAVE_REG_P05:
			value = jk510_Disp.Disp_Res[0].uint;
			break;
		case SLAVE_REG_P06:
			value = (u16)(jk510_Disp.Disp_Res[1].res >> 16);
			break;
		case SLAVE_REG_P07:
			value = (u16)(jk510_Disp.Disp_Res[1].res);	
			break;
		case SLAVE_REG_P08:
			value = (u16)(jk510_Disp.Disp_V[1].res >> 16);	
			break;

		case SLAVE_REG_P09:
			value = (u16)(jk510_Disp.Disp_V[1].res);
			break;
		case SLAVE_REG_P10:
			value = jk510_Disp.Disp_Res[1].dot;
			break;
		case SLAVE_REG_P11:
			value = jk510_Disp.Disp_Res[1].uint;
			break;
		case SLAVE_REG_P12:
			value = (u16)(jk510_Disp.Disp_Res[2].res >> 16);
			break;

		case SLAVE_REG_P13:
			value = (u16)(jk510_Disp.Disp_Res[2].res);
			break;
		case SLAVE_REG_P14:
			value = (u16)(jk510_Disp.Disp_V[2].res >> 16);
			break;

		case SLAVE_REG_P15:
			value = (u16)(jk510_Disp.Disp_V[2].res);
			break;
		case SLAVE_REG_P16:
			value = jk510_Disp.Disp_Res[2].dot;
			break;
		case SLAVE_REG_P17:
			value = jk510_Disp.Disp_Res[2].uint;
			break;
		case SLAVE_REG_P18:
			value = (u16)(jk510_Disp.Disp_Res[3].res >> 16);
			break;

		case SLAVE_REG_P19:
			value = (u16)(jk510_Disp.Disp_Res[3].res);
			break;
		case SLAVE_REG_P20:
			value = (u16)(jk510_Disp.Disp_V[3].res >> 16);
			break;

		case SLAVE_REG_P21:
			value = (u16)(jk510_Disp.Disp_V[3].res);
			break;
		case SLAVE_REG_P22:
			value = jk510_Disp.Disp_Res[3].dot;
			break;
		case SLAVE_REG_P23:
			value = jk510_Disp.Disp_Res[3].uint;
			break;
		case SLAVE_REG_P24:
			value = (u16)(jk510_Disp.Disp_Res[4].res >> 16);
			break;

		case SLAVE_REG_P25:
			value = (u16)(jk510_Disp.Disp_Res[4].res);
			break;
		case SLAVE_REG_P26:
			value = (u16)(jk510_Disp.Disp_V[4].res >> 16);
			break;

		case SLAVE_REG_P27:
			value = (u16)(jk510_Disp.Disp_V[4].res);
			break;
		case SLAVE_REG_P28:
			value = jk510_Disp.Disp_Res[4].dot;
			break;
		case SLAVE_REG_P29:
			value = jk510_Disp.Disp_Res[4].uint;
			break;
		case SLAVE_REG_P30:
			value = (u16)(jk510_Disp.Disp_Res[5].res >> 16);
			break;
		case SLAVE_REG_P31:
			value = (u16)(jk510_Disp.Disp_Res[5].res);
			break;
		case SLAVE_REG_P32:
			value = (u16)(jk510_Disp.Disp_V[5].res >> 16);
			break;

		case SLAVE_REG_P33:
			value = (u16)(jk510_Disp.Disp_V[5].res);
			break;
		case SLAVE_REG_P34:
			value = jk510_Disp.Disp_Res[5].dot;
			break;
		case SLAVE_REG_P35:
			value = jk510_Disp.Disp_Res[5].uint;
			break;
		case SLAVE_REG_P36:
			value = (u16)(jk510_Disp.Disp_Res[6].res >> 16);
			break;
		case SLAVE_REG_P37:
			value = (u16)(jk510_Disp.Disp_Res[6].res);
			break;
		case SLAVE_REG_P38:
			value = (u16)(jk510_Disp.Disp_V[6].res >> 16);
			break;

		case SLAVE_REG_P39:
			value = (u16)(jk510_Disp.Disp_V[6].res);
			break;
		case SLAVE_REG_P40:
			value = jk510_Disp.Disp_Res[6].dot;
			break;
		case SLAVE_REG_P41:
			value = jk510_Disp.Disp_Res[6].uint;
			break;
		case SLAVE_REG_P42:
			value = (u16)(jk510_Disp.Disp_Res[7].res >> 16);
			break;
		case SLAVE_REG_P43:
			value = (u16)(jk510_Disp.Disp_Res[7].res);
			break;
		case SLAVE_REG_P44:
			value = (u16)(jk510_Disp.Disp_V[7].res >> 16);
			break;

		case SLAVE_REG_P45:
			value = (u16)(jk510_Disp.Disp_V[7].res);
			break;
		case SLAVE_REG_P46:
			value = jk510_Disp.Disp_Res[7].dot;
			break;
		case SLAVE_REG_P47:
			value = jk510_Disp.Disp_Res[7].uint;
			break;
		case SLAVE_REG_P48:
			value = (u16)(jk510_Disp.Disp_Res[8].res >> 16);
			break;
		case SLAVE_REG_P49:
			value = (u16)(jk510_Disp.Disp_Res[8].res);
			break;
		case SLAVE_REG_P50:
			value = (u16)(jk510_Disp.Disp_V[8].res >> 16);
			break;

		case SLAVE_REG_P51:
			value = (u16)(jk510_Disp.Disp_V[8].res);
			break;
		case SLAVE_REG_P52:
			value = jk510_Disp.Disp_Res[8].dot;
			break;
		case SLAVE_REG_P53:
			value = jk510_Disp.Disp_Res[8].uint;
			break;
		case SLAVE_REG_P54:
			value = (u16)(jk510_Disp.Disp_Res[9].res >> 16);
			break;
		case SLAVE_REG_P55:
			value = (u16)(jk510_Disp.Disp_Res[9].res);
			break;
		case SLAVE_REG_P56:
			value = (u16)(jk510_Disp.Disp_V[9].res >> 16);
			break;

		case SLAVE_REG_P57:
			value = (u16)(jk510_Disp.Disp_V[9].res);
			break;
		case SLAVE_REG_P58:
			value = jk510_Disp.Disp_Res[9].dot;
			break;
		case SLAVE_REG_P59:
			value = jk510_Disp.Disp_Res[9].uint;
			break;
		default:
			return 0;
    }
	reg_value[0] = value >> 8;
	reg_value[1] = value;

	return 1;											/* ???? */
}

static void RemTrig(void)
{
	test_start = 1;
}

static void MODS_03H(void)
{
    uint16_t reg;
	uint16_t num;
	uint16_t i;
	uint8_t reg_value[150];

    
    g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)								/* 03H????ˇ8??? */
	{
		g_tModS.RspCode = RSP_ERR_VALUE;					/* ?????? */
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]); 				/* ???? */
	num = BEBufToUint16(&g_tModS.RxBuf[4])*2;					/* ????? */
	if (num > sizeof(reg_value) / 2)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;					/* ?????? */
		goto err_ret;
	}

	for (i = 0; i < num; i++)
	{
		if (MODS_ReadRegValue(reg, &reg_value[2 * i]) == 0)	/* ????????reg_value */
		{
			g_tModS.RspCode = RSP_ERR_REG_ADDR;				/* ??????? */
			break;
		}
		reg++;
	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)							/* ???? */
	{
		g_tModS.TxCount = 0;
		g_tModS.TxBuf[g_tModS.TxCount++] = g_tModS.RxBuf[0];
		g_tModS.TxBuf[g_tModS.TxCount++] = g_tModS.RxBuf[1];
		g_tModS.TxBuf[g_tModS.TxCount++] = num * 2;			/* ????? */

		for (i = 0; i < num; i++)
		{
			g_tModS.TxBuf[g_tModS.TxCount++] = reg_value[2*i];
			g_tModS.TxBuf[g_tModS.TxCount++] = reg_value[2*i+1];
		}
//         if(usartocflag == 0)
//         {
             MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);	/* ?????? */
//         }
	}
	else
	{
//		MODS_SendAckErr(g_tModS.RspCode);					/* ?????? */
	}
    
}

static void MODS_06H(void)
{
    uint16_t reg;
	uint16_t value;

	g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;		/* ?????? */
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]); 	/* ???? */
	value = BEBufToUint16(&g_tModS.RxBuf[4]);	/* ???? */
    
//    if(reg == 0x0E)
//    {
//        if(value == 00)
//        {
//            GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CC
//            flag_Load_CC = 1;
//        }else if(value == 01){
//            GPIO_SetBits(GPIOC,GPIO_Pin_10);//CV
//            flag_Load_CC = 0;
//        }
//    }
// 	if (MODS_WriteRegValue(reg, value) == 1)	/* ????ёд???????? */
// 	{
// 		;
// 	}
// 	else
// 	{
// 		g_tModS.RspCode = RSP_ERR_REG_ADDR;		/* ??????? */
// 	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)				/* ???? */
	{
//		MODS_SendAckOk();
	}
	else
	{
//		MODS_SendAckErr(g_tModS.RspCode);		/* ???????? */
	}
}


//void USART3_IRQHandler(void)
//{
//	u8 dat;

//	if(( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET))//接收完成中断
//	{
//		if (!ComBuf.rec.end)//接收没结束
//		{
//			SetRecTimeOut(REC_TIME_OUT);//设置接收超时周期
//			dat=USART_ReceiveData(USART3);
//			if (dat==(u8)(UART_REC_BEGIN))//帧头
//			{
//				if(ComBuf.rec.ptr!=0) //首字节
//				{
//					ComBuf.rec.ptr=0;//重新接收 
//				}
//				else
//				{
//					ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
//				}
//			}
//			else if (dat==(u8)(UART_REC_END))//帧尾
//			{
//				ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
//				ComBuf.rec.end=TRUE;//接收结束
//				ComBuf.rec.len=ComBuf.rec.ptr;//存接收数据长度
//				ComBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
//				ComBuf.rec.TimeOut=0;//接收超时清零
//			}
//			else
//			{
//				if (ComBuf.rec.ptr>=REC_LEN_MAX)//最大接收帧长度
//				{
//					ComBuf.rec.ptr=0;//重新接收
//				}
//				else
//				{
//					ComBuf.rec.buf[ComBuf.rec.ptr++]=dat;
//				}
//			}
//		}	
//        USART_ClearFlag(USART3, USART_FLAG_RXNE);
////		RI=0;//清接收标志
//	}
//    USART_ClearFlag(USART3, USART_FLAG_RXNE);//
//    USART_ClearFlag(USART3, USART_FLAG_TXE);
//    

////	if(( USART_GetFlagStatus(USART3, USART_FLAG_TXE) != RESET))//发送完成中断
////	{
////		if (ComBuf.send.begin)//发送开始
////		{
////			if (ComBuf.send.ptr<ComBuf.send.len)//没发送完继续
////			{
//////				SBUF=ComBuf.send.buf[ComBuf.send.ptr++];
////                 USART_SendData(USART3, (uint8_t) ComBuf.send.buf[ComBuf.send.ptr++]); /*发送一个字符函数*/ 

////                  /* Loop until the end of transmission */
////                  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)/*等待发送完成*/
////                  {
////                  
////                  }
////			}
////			else
////			{
////				ComBuf.send.begin=FALSE;//发送结束
////				ComBuf.send.ptr=0;//指针清零
////			}
////		}
////USART_ClearFlag(USART3, USART_FLAG_TXE);//		TI=0;//清发送标志
////	}	
//} 

void  TIM2_IRQHandler (void)//U盘用了定时器2
{
    USB_OTG_BSP_TimerIRQ();
	 	
}

void  BASIC_TIM_IRQHandler (void)
{
    static u8 num=0;
    u8 i;
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
//		LED1_TOGGLE;
		TIM_ClearITPendingBit(BASIC_TIM , TIM_IT_Update);  		
//        Key_Scan();
        //????
//        if(SystemStatus==SYS_STATUS_CLEAR)
//        {
//            num++;
//            if(num>9)//10mS??
//            {
//                num=0;
//                F_100ms=TRUE;//100ms????
//                //Test_value.Clear_Time++;
//            }
//        
//        }else
		Tick_10ms ++;
        MODS_Poll();
        if(SystemStatus==SYS_STATUS_TEST)
        {
            num++;
            if(num>9)//10mS??
            {
                num=0;
                F_100ms=TRUE;//100ms????
                Test_value.Test_Time++;
                //Voltage++;
            }
//            if(Jk516save.Sys_Setvalue.u_flag)
//            {
//                
//                USBH_Process(&USB_OTG_Core, &USB_Host);
//            }
        }
        else
        {
            if(num!=0)
                num=0;
        }
        Key_Scan();	 
       
        for (i=0;i<MAXTSOFTTIMER;i++)
        {
            if (SoftTimer[i])
                SoftTimer[i]--;
            
        }	
        
	
	}		 	
}
void KEY1_IRQHandler(void)//开关机
{
  //确保是否产生了EXTI Line中断
//    u32 i;
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{
		delay_ms(1000);
       
        if(GPIO_ReadInputDataBit( GPIOE,  GPIO_Pin_3)==0)
        {
            Int_Pe3flag=0;
            if(softswitch)
            {
                softswitch=0;
                SetSystemStatus(SYS_STATUS_TOOL);
            
            }else
            {
                softswitch=1;
                
                SetSystemStatus(SYS_STATUS_POWER);
            
            }
            NVIC_DisableIRQ(EXTI3_IRQn);
        }
		//GPIO_ClearInt(0, 1<<19);
		
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);     
	}  
}

void EXTI15_10_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) 
	{
		// LED2 取反		
		//LED2_TOGGLE;
    //清除中断标志位
        //Read__Convert_read();
		EXTI_ClearITPendingBit(EXTI_Line13);     
	}  
}
#ifdef USE_USB_OTG_FS  
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler(void)
    
#endif
{
  USBH_OTG_ISR_Handler(&USB_OTG_Core);
}

/**	过流检测，硬件不支持
  * @brief  EXTI1_IRQHandler
  *         This function handles External line 1 interrupt request.
  * @param  None
  * @retval None
  */
#if 0
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
      USB_Host.usr_cb->OverCurrentDetected();
      EXTI_ClearITPendingBit(EXTI_Line1);
  }
}


#endif
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                         */
/******************************************************************************/

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
