
/*
* @brief CAN example
* This example show how to use CAN peripheral
*
* @note
* Copyright(C) NXP Semiconductors, 2014
* All rights reserved.
*
* @par
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* LPC products.  This software is supplied "AS IS" without any warranties of
* any kind, and NXP Semiconductors and its licensor disclaim any and
* all warranties, express or implied, including all implied warranties of
* merchantability, fitness for a particular purpose and non-infringement of
* intellectual property rights.  NXP Semiconductors assumes no responsibility
* or liability for the use of the software, conveys no license or rights under any
* patent, copyright, mask work right, or any other intellectual property rights in
* or to any products. NXP Semiconductors reserves the right to make changes
* in the software without notification. NXP Semiconductors also makes no
* representation or warranty that such application will be suitable for the
* specified use without further testing or modification.
*
* @par
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors' and its
* licensor's relevant copyrights in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
*/
#include "chip.h"

volatile unsigned long SysTickCnt;

void SysTick_Handler(void)
{
	SysTickCnt++;
}

void Delay(unsigned long tick)
{
	unsigned long systickcnt;

	systickcnt = SysTickCnt;
	while ((SysTickCnt - systickcnt) < tick);
}

const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 24000000;
const uint32_t RTCOscRateIn = 32768;

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

#ifdef __cplusplus
extern "C"
#endif

/*****************************************************************************
* Private types/enumerations/variables
****************************************************************************/
#if defined(CHIP_LPC175X_6X)
#define CAN_CTRL_NO         0
#else
#define CAN_CTRL_NO         0
#endif
#if (CAN_CTRL_NO == 0)
#define LPC_CAN             (LPC_CAN1)
#else
#define LPC_CAN             (LPC_CAN2)
#endif
#define CAN_TX_MSG_STD_ID (0x200)
#define CAN_TX_MSG_REMOTE_STD_ID (0x300)
#define CAN_RX_MSG_ID (0x100)

volatile uint32_t timer;//ms timer
volatile uint8_t  t_flag;//timer flag

						 /* Reply message received */
static void ReplyMessage(CAN_MSG_T *pRcvMsg)
{
	CAN_MSG_T SendMsgBuf = *pRcvMsg;
	CAN_BUFFER_ID_T   TxBuf;
	SendMsgBuf.ID = CAN_TX_MSG_STD_ID;
	TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
	Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
}

//receive message and reply with CAN_TX_MSG_STD_ID (0x200)
void CAN_IRQHandler(void)
{
	uint32_t IntStatus;
	CAN_MSG_T RcvMsgBuf;
	IntStatus = Chip_CAN_GetIntStatus(LPC_CAN);

	/* New Message came */
	if (IntStatus & CAN_ICR_RI)
	{
		Chip_CAN_Receive(LPC_CAN, &RcvMsgBuf);
		ReplyMessage(&RcvMsgBuf);
	}
}

//init CAN, Pin muxing is done in board_sysinit.c already !!!
void CAN_init(void)
{
	//if no PIN setup is done, it's time now...
	Chip_IOCON_PinMux(LPC_IOCON, 0, 0, IOCON_MODE_INACT, IOCON_FUNC1);// P0.0 CAN-RD1
	Chip_IOCON_PinMux(LPC_IOCON, 0, 1, IOCON_MODE_INACT, IOCON_FUNC1);// P0.1 CAN-TD1
	Chip_CAN_Init(LPC_CAN, LPC_CANAF, LPC_CANAF_RAM);
	Chip_CAN_SetBitRate(LPC_CAN, 500000);
	Chip_CAN_EnableInt(LPC_CAN, CAN_IER_BITMASK);
	Chip_CAN_SetAFMode(LPC_CANAF, CAN_AF_BYBASS_MODE);
	NVIC_EnableIRQ(CAN_IRQn);
}

int main(void)
{
	CAN_BUFFER_ID_T TxBuf;//select buffer
	CAN_MSG_T SendMsgBuf;//send message
	SystemCoreClockUpdate();
	//init CAN
	CAN_init();
	//init timer
	SysTick_Config(SystemCoreClock / 1000);  //ms timer


											 //setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 10 | 1 << 11);


	//send simple message
	SendMsgBuf.ID = CAN_TX_MSG_STD_ID;
	SendMsgBuf.DLC = 2;
	SendMsgBuf.Type = 0;
	SendMsgBuf.Data[0] = 20;
	SendMsgBuf.Data[1] = 60;
	TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
	Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
	while ((Chip_CAN_GetStatus(LPC_CAN) & CAN_SR_TCS(TxBuf)) == 0) {
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, 1);
		Delay(100);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, 0);
		Delay(100);
	}

	while (1)
	{
		if (t_flag)
		{
			t_flag = 0;
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, 1);
			Delay(100);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, 0);
			Delay(100);
			SendMsgBuf.Data[0]++;
		}
	}
}