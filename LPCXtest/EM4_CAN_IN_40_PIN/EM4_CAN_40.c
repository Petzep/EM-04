/*
===============================================================================
Name        : EM4_CAN_IN.c
Author      : Nephtaly Aniceta
Version     : 0.8
Copyright   : GPLv3
Description : Main CAN IN Function
Inspired by work from previous years.
Rewritten for Visual Studio and LPCOpen v2.xx
===============================================================================
*/

#include <chip.h>

#define DEVICE_NR			0b0000
#define	EM_04_CAN_RANGE		0x100

#define ALL_ADDRESS			(0x000 + EM_04_CAN_RANGE)
#define DIM_ADDRESS			(0x008 + EM_04_CAN_RANGE)
#define FRONT_DEVICES		(0x000 + EM_04_CAN_RANGE)
#define REAR_DEVICES		(0x001 + EM_04_CAN_RANGE)
#define LEFT_DEVICES		(0x002 + EM_04_CAN_RANGE)
#define RIGHT_DEVICES		(0x003 + EM_04_CAN_RANGE)
#define WHIPER_ADDRESS		(0x004 + EM_04_CAN_RANGE)
#define FAN_ADDRESS			(0x005 + EM_04_CAN_RANGE)
#define HUD_ADDRESS			(0x010 + EM_04_CAN_RANGE)
#define SPEED_ADDRESS		(0x001 + HUD_ADDRESS)
#define WARNING_ADDRESS		(0x002 + HUD_ADDRESS)
#define BATTERY_ADDRESS		(0x003 + HUD_ADDRESS)
#define CLOCK_ADDRES		(0x004 + HUD_ADDRESS)
#define BROADCAST_ADDRESS	(0x030 + EM_04_CAN_RANGE)

#define	ALL_MESSAGE			1
#define FRONT_MESSAGE		2
#define	REAR_MESSAGE		3
#define	LEFT_MESSAGE		4
#define	RIGHT_MESSAGE		5
#define	PERSNOAL_MESSAGE	6
#define	DIM_MESSAGE			7
#define	TOTAL_MESSAGE		8

#define BLINK_FREQ			750

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
		//ReplyMessage(&RcvMsgBuf);
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
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 <<  10| 1 << 11);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 6 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 10 | 1 << 11 | 1 << 15 | 1 << 16 | 1 << 17 | 1 << 18 | 1 << 22);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 1, 1 << 0 | 1 << 1 | 1 << 4 | 1 << 8 | 1 << 9 | 1 << 10 | 1 << 14 | 1 << 15);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 2, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 4, 1 << 28 | 1 << 29);


	bool blinkLeftOn = false;
	bool blinkLeftState = false;
	bool blinkRightOn = false;
	bool blinkRightState = false;

	bool lightsOn = false;
	bool alarmOn = false;
	bool wiperOn = false;

	bool sendOn = false;
	bool can1On = false;
	bool can2On = false;

	bool fanOn = false;
	int fanSetting = 0;

	bool hud1On = false;
	bool hud2On = false;
	bool hud3On = false;
	bool hud4On = false;
	bool hud5On = false;
	bool hud6On = false;
	bool hud7On = false;
	bool hud8On = false;
	bool hudWarningOn = false;

	bool ledOn = false;
	unsigned long lastSystickcnt = 0;


	for (;;) //infinite loop
	{
		bool pin1 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 16);
		bool pin2 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 15);
		bool pin3 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 17);
		bool pin4 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 18);
		bool pin5 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 22);
		bool pin6 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 4);
		bool pin7 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 5);
		bool pin8 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 6);
		bool pin9 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 7);
		bool pin10 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 8);
		bool pin11 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 9);
		bool pin12 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 0);
		bool pin13 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 1);
		bool pin14 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 2);
		bool pin15 = Chip_GPIO_ReadPortBit(LPC_GPIO, 2, 3);
		bool pin16 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 6);
		bool pin17 = Chip_GPIO_ReadPortBit(LPC_GPIO, 4, 29);
		bool pin18 = Chip_GPIO_ReadPortBit(LPC_GPIO, 4, 28);
		bool pin19 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 8);
		bool pin20 = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 7);
		bool pin21 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 10);
		bool pin22 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 15);
		bool pin23 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 0);
		bool pin24 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 14);
		bool pin25 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 1);
		bool pin26 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 4);
		bool pin27 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 9);
		bool pin28 = Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 8);

		bool blinkLeft = pin1;
		bool blinkRight = pin5;
		bool alarm = pin8;
		bool lights = pin3;
		bool wiper = pin15;
		bool can1 = pin7;
		bool can2 = pin9;
		bool send = pin28;
		bool fan = pin27;
		bool hud1 = pin17;
		bool hud2 = pin18;
		bool hud3 = pin19;
		bool hud4 = pin20;
		bool hud5 = pin21;
		bool hud6 = pin22;
		bool hud7 = pin23;
		bool hud8 = pin24;
		bool hudWarning = pin16;
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

		if (can1 != can1On)
		{
			//Toggle DIM_LIGHTS head and rear
			can1On = can1;
			SendMsgBuf.ID = 0b0111 | CAN_MSGOBJ_STD;
			SendMsgBuf.DLC = 1;
			SendMsgBuf.Type = 0;
			SendMsgBuf.Data[0] = can1On;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
		}

		if (can2 != can2On)
		{
			//Toggle DIM_LIGHTS head and rear
			can2On = can2;
			SendMsgBuf.ID = 0b0100 | CAN_MSGOBJ_STD;
			SendMsgBuf.DLC = 1;
			SendMsgBuf.Type = 0;
			SendMsgBuf.Data[0] = can2On;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
		}

		if(fan != fanOn)
		{
			fanOn = fan;
			if(fan)
			{
				fanSetting += 10;
				if(fanSetting > 100)
					fanSetting = 0;

				SendMsgBuf.ID = FAN_ADDRESS | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 1;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = fanSetting;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
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

		//Send an overview of the inputs
		if (send != sendOn)
		{
			sendOn = send;
			//SEND all buttons
			if (send)
			{
				SendMsgBuf.ID = BROADCAST_ADDRESS + 1 + 256 | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 6;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = 1;
				SendMsgBuf.Data[1] = pin1;
				SendMsgBuf.Data[2] = pin2;
				SendMsgBuf.Data[3] = pin3;
				SendMsgBuf.Data[4] = pin4;
				SendMsgBuf.Data[5] = pin5;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				Delay(50);

				SendMsgBuf.ID = BROADCAST_ADDRESS + 6 + 256 | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 6;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = 0x6;
				SendMsgBuf.Data[1] = pin6;
				SendMsgBuf.Data[2] = pin7;
				SendMsgBuf.Data[3] = pin8;
				SendMsgBuf.Data[4] = pin9;
				SendMsgBuf.Data[5] = pin10;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				Delay(50);

				SendMsgBuf.ID = BROADCAST_ADDRESS + 11 + 256 | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 6;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = 0x11;
				SendMsgBuf.Data[1] = pin11;
				SendMsgBuf.Data[2] = pin12;
				SendMsgBuf.Data[3] = pin13;
				SendMsgBuf.Data[4] = pin14;
				SendMsgBuf.Data[5] = pin15;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				Delay(50);

				SendMsgBuf.ID = BROADCAST_ADDRESS + 16 + 256 | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 6;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = 0x16;
				SendMsgBuf.Data[1] = pin16;
				SendMsgBuf.Data[2] = pin17;
				SendMsgBuf.Data[3] = pin18;
				SendMsgBuf.Data[4] = pin19;
				SendMsgBuf.Data[5] = pin20;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				Delay(50);

				SendMsgBuf.ID = BROADCAST_ADDRESS + 21 + 256 | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 6;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = 0x21;
				SendMsgBuf.Data[1] = false;
				SendMsgBuf.Data[2] = pin21;
				SendMsgBuf.Data[3] = pin22;
				SendMsgBuf.Data[4] = pin23;
				SendMsgBuf.Data[5] = pin24;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);

				Delay(50);

				SendMsgBuf.ID = BROADCAST_ADDRESS + 26 + 256 | CAN_MSGOBJ_STD;
				SendMsgBuf.DLC = 6;
				SendMsgBuf.Type = 0;
				SendMsgBuf.Data[0] = 0x26;
				SendMsgBuf.Data[1] = false;
				SendMsgBuf.Data[2] = !pin25;
				SendMsgBuf.Data[3] = !pin26;
				SendMsgBuf.Data[4] = !pin27;
				SendMsgBuf.Data[5] = !pin28;
				TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
				Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
			}
			
		}

		if((hud1 != hud1On) || (hud2 != hud2On) || (hud3 != hud3On) || (hud4 != hud4On) || (hud5 != hud5On) || (hud6 != hud6On) || (hud7 != hud7On) || (hud8 != hud8On))
		{
			hud1On = hud1;
			hud2On = hud2;
			hud3On = hud3;
			hud4On = hud4;
			hud5On = hud5;
			hud6On = hud6;
			hud7On = hud7;
			hud8On = hud8;

			SendMsgBuf.ID = 0b1001 | CAN_MSGOBJ_STD;
			SendMsgBuf.DLC = 8;
			SendMsgBuf.Type = 0;
			SendMsgBuf.Data[0] = hud1 + 10;
			SendMsgBuf.Data[1] = hud2 + 10;
			SendMsgBuf.Data[2] = hud3 + 10;
			SendMsgBuf.Data[3] = hud4 + 10;
			SendMsgBuf.Data[4] = hud5 + 10;
			SendMsgBuf.Data[5] = hud6 + 10;
			SendMsgBuf.Data[6] = hud7 + 10;
			SendMsgBuf.Data[7] = hud8 + 10;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
		}

		if(hudWarning != hudWarningOn)
		{
			hudWarningOn = hudWarning;
			
			SendMsgBuf.ID = WARNING_ADDRESS | CAN_MSGOBJ_STD;
			SendMsgBuf.DLC = 1;
			SendMsgBuf.Type = 0;
			SendMsgBuf.Data[0] = hudWarning;
			TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
			Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);
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

/*
Ouput pins:
-------------
8	1,7
7	3,3
1	2,7
2	2,8
3	2,1
4	0,3
5	0,4
6	0,5

Led pins:
-------------
led 1 (green) power light
led 2 (red) 2,10
led 3 (yellow) 2,2
led 4 (blue) 0,7

DEVICE ID config:
-------------

 name ||KIPPP| out |twins|front| dec | 0b0000
======||=====================================
  IN  ||--0--|--0--|--0--|--0--|  0  | 0b0000
Front ||--0--|--1--|--1--|--1--|  7  | 0b0111
 Back ||--0--|--1--|--1--|--0--|  6  | 0b0110
  Mid ||--0--|--1--|--0--|--0--|  4  | 0b0100
  HUD ||--1--|--0--|--0--|--1--|  9  | 0b1001
  Tor ||--1--|--0--|--0--|--0--|  8  | 0b1000
  Fan ||--1--|--1--|--0--|--0--|  12 | 0b1100

*/
/*
int test = 0b1100
;*/