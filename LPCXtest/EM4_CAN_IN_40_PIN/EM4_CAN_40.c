/*
===============================================================================
Name        : EM4_CAN_IN.c
Author      : Nephtaly Aniceta
Version     :
Copyright   : -
Description : Main CAN IN Function
Inspired by work from previous years.
Rewritten for Visual Studio and LPCOpen v2.xx
===============================================================================
*/

#include <chip.h>

#define DEVICE_NR			0x020

#define ALL_ADDRESS			0x000
#define DIM_ADDRESS			0x008
#define FRONT_DEVICES		0x000
#define REAR_DEVICES		0x001
#define LEFT_DEVICES		0x002
#define RIGHT_DEVICES		0x003
#define WHIPER_ADDRESS		0x012
#define BROADCAST_ADDRESS	0x030

#define	ALL_MESSAGE			1
#define FRONT_MESSAGE		2
#define	REAR_MESSAGE		3
#define	LEFT_MESSAGE		4
#define	RIGHT_MESSAGE		5
#define	PERSNOAL_MESSAGE	6
#define	DIM_MESSAGE			7
#define	TOTAL_MESSAGE		8

#define BLINK_FREQ			3

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

#ifdef __cplusplus
extern "C"
#endif

volatile unsigned long SysTickCnt;
volatile unsigned long lastClick;

const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 24000000;
const uint32_t RTCOscRateIn = 32768;

CAN_MSG_T SendMsgBuf;

/**
* @brief	Handle interrupt from SysTick timer
* @return	Nothing
*/
void SysTick_Handler(void) {
	SysTickCnt++;
}

void Delay(unsigned long tick) {
	unsigned long systickcnt;

	systickcnt = SysTickCnt;
	while ((SysTickCnt - systickcnt) < tick)
		;
}

//TODO
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
#define CAN_MSGOBJ_STD  0x00000000UL
#define CAN_TX_MSG_REMOTE_STD_ID (0x300)
#define CAN_RX_MSG_ID (0x100)

volatile uint32_t timer;//ms timer
volatile uint8_t  t_flag;//timer flag

/* Reply message received */
static void ReplyMessage(CAN_MSG_T *pRcvMsg)
{
	CAN_MSG_T SendMsgBuf = *pRcvMsg;
	CAN_BUFFER_ID_T   TxBuf;
	SendMsgBuf.ID = (BROADCAST_ADDRESS + DEVICE_NR);
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
	//Enable and setup SysTick Timer at 1/1000 seconds (1ms)
	SysTick_Config(SystemCoreClock / 1000);

	//init CAN
	CAN_init();

	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 10 | 1 << 11);

	bool blinkLeftOn = false;
	bool blinkLeftState = false;
	bool blinkRightOn = false;
	bool blinkRightState = false;

	bool lightsOn = false;
	bool alarmOn = false;
	bool wiperOn = false;

	bool ledOn = false;
	unsigned long lastSystickcnt = 0;


	for (;;) //infinite loop
	{
		bool blinkLeft = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 3);
		bool blinkRight = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 7);
		bool alarm = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 8);
		bool lights = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 2);
		bool wiper = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 1);
		bool click = false;

		unsigned long LoopTick = SysTickCnt;		//Ensure there are no count "jumps" during the loop

		//////////////////////////////
		////////BUTTON HANDLER////////
		//////////////////////////////
		if (blinkLeft != blinkLeftOn)
		{
			blinkLeftOn = blinkLeft;
		}

		if (blinkRight != blinkRightOn)
		{
			blinkRightOn = blinkRight;
		}

		if (alarm != alarmOn)
		{
			blinkLeftOn = alarm;
			blinkRightOn = alarm;
			alarmOn = alarm;
		}

		if (lights != lightsOn)
		{
			//Toggle DIM_LIGHTS head and rear
			lightsOn = lights;
			SendMsgBuf.ID = DIM_ADDRESS | CAN_MSGOBJ_STD;
			SendMsgBuf.DLC = 1;
			SendMsgBuf.Type = 0;
			SendMsgBuf.Data[0] = lightsOn;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
		}

		if (wiper != wiperOn)
		{
			//Toggle whiper, send to personal adress from whiper
			wiperOn = wiper;

			SendMsgBuf.ID = WHIPER_ADDRESS | CAN_MSGOBJ_STD;
			SendMsgBuf.DLC = 5;
			SendMsgBuf.Data[0] = 0;
			SendMsgBuf.Data[1] = 0;
			SendMsgBuf.Data[2] = 0;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);//???? Hazard! [3][4] undefined? Are they nessecary
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);//????

			if (wiperOn)
			{
				//first disable reset
				SendMsgBuf.Data[3] = false;
				SendMsgBuf.Data[4] = false;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				//then set wiper on
				SendMsgBuf.Data[3] = true;
				SendMsgBuf.Data[4] = true;
				Delay(100);
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
			else
			{
				//first set wiper off
				SendMsgBuf.Data[3] = false;
				SendMsgBuf.Data[4] = false;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				//then enable reset
				SendMsgBuf.Data[3] = false;
				SendMsgBuf.Data[4] = true;
				Delay(100);
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
		}


		//////////////////////////////
		////////////TIMERS////////////
		//////////////////////////////
		//
		//Left Blink
		//
		if ((blinkLeftOn || alarmOn) && ((LoopTick - lastClick) >= BLINK_FREQ))
		{
			click = true;
			SendMsgBuf.ID = LEFT_DEVICES + DIM_ADDRESS;
			SendMsgBuf.DLC = 1;
			//Turn on if there is no blink and (left_blinker or Alarm is on)
			if (!blinkLeftState)
			{
				blinkLeftState = true;
				SendMsgBuf.Data[0] = true;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
			else
			{
				blinkLeftState = false;
				SendMsgBuf.Data[0] = false;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
		}

		//
		//Right Blink
		//
		if ((blinkRightOn || alarmOn) && ((LoopTick - lastClick) >= BLINK_FREQ)) //TODO: check if blinkRightState has to be included
		{
			click = true;
			SendMsgBuf.ID = RIGHT_DEVICES + DIM_ADDRESS;
			SendMsgBuf.DLC = 1;
			if (!blinkRightState)
			{
				blinkRightState = true;
				SendMsgBuf.Data[0] = true;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
			else
			{
				blinkRightState = false;
				SendMsgBuf.Data[0] = false;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
		}

		if (click)
			lastClick = SysTickCnt;

		//
		//heartbeat
		//
		if ((LoopTick - lastSystickcnt) >= 1000)
		{
			lastSystickcnt = SysTickCnt;

			SendMsgBuf.ID = (BROADCAST_ADDRESS + DEVICE_NR) | CAN_MSGOBJ_STD;
			SendMsgBuf.Type = 0;
			SendMsgBuf.DLC = 1;
			SendMsgBuf.Data[0] = DEVICE_NR;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

			if (ledOn)
			{
				ledOn = false;
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);	//led 3 (blue)
			}
			else
			{
				ledOn = true;
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);	//led 3 (blue)
			}
		}
	}
	return 0;
}