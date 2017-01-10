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

#define BLINK_FREQ			750

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

#ifdef __cplusplus
extern "C"
#endif
	
volatile unsigned long SysTickCnt;
volatile unsigned long lastClick;

const uint32_t ExtRateIn	= 0;
const uint32_t OscRateIn	= 12000000;
const uint32_t RTCOscRateIn	= 32768;

CCAN_MSG_OBJ_T msg_obj;

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void) {
	SysTickCnt++;
}

/**
 * @brief	Handle interrupt from 32-bit timer
 * @return	Nothing
 */
void TIMER32_0_IRQHandler(void){
	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
	}
}

void Delay(unsigned long tick) {
	unsigned long systickcnt;

	systickcnt = SysTickCnt;
	while ((SysTickCnt - systickcnt) < tick)
		;
}

/**
 * @brief	CCAN Interrupt Handler
 * @return	Nothing
 * @note	The CCAN interrupt handler must be provided by the user application.
 *	It's function is to call the isr() API located in the ROM
 */
void CAN_IRQHandler(void) {
	LPC_CCAN_API->isr();
}

void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg) {
	uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
	pClk = Chip_Clock_GetMainClockRate();

	clk_per_bit = pClk / baud_rate;

	for (div = 0; div <= 15; div++) {
		for (quanta = 1; quanta <= 32; quanta++) {
			for (segs = 3; segs <= 17; segs++) {
				if (clk_per_bit == (segs * quanta * (div + 1))) {
					segs -= 3;
					seg1 = segs / 2;
					seg2 = segs - seg1;
					can_sjw = seg1 > 3 ? 3 : seg1;
					can_api_timing_cfg[0] = div;
					can_api_timing_cfg[1] =
						((quanta - 1) & 0x3F) | (can_sjw & 0x03) << 6 | (seg1 & 0x0F) << 8 | (seg2 & 0x07) << 12;
					return;
				}
			}
		}
	}
}

/* Callback function prototypes */
void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);

void setPort(int port, bool onoff);


void CAN_init() {
	/* Publish CAN Callback Functions */
	CCAN_CALLBACKS_T callbacks = { CAN_rx, CAN_tx, CAN_error, NULL, NULL, NULL,
		NULL,
		NULL, };

	/* Initialize CAN Controller */
	uint32_t CanApiClkInitTable[2];
	baudrateCalculate(500000, CanApiClkInitTable); //500kbits

	LPC_CCAN_API->init_can(&CanApiClkInitTable[0], TRUE);
	/* Configure the CAN callback functions */
	LPC_CCAN_API->config_calb(&callbacks);

	msg_obj.msgobj = ALL_MESSAGE;
	msg_obj.mode_id = ALL_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = PERSNOAL_MESSAGE;
	msg_obj.mode_id = DEVICE_NR;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	/* Enable the CAN Interrupt */
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
 a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num) {
	// Disable interupts while receiving
	//NVIC_DisableIRQ(CAN_IRQn);
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;

	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if (msg_obj_num < TOTAL_MESSAGE || msg_obj_num > 0)
	{
		//Message "Inbox" for all the FRONT_MESSAGES {...}
		if (msg_obj_num == PERSNOAL_MESSAGE)
		{

		}

		if (msg_obj_num == ALL_MESSAGE)
		{
			
		}
		
		// Turn on the yellow led and Enable timer interrupt
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, msg_obj.data[0]); //led 4 (yellow)
		NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
		NVIC_EnableIRQ(TIMER_32_0_IRQn);
	}
	NVIC_EnableIRQ(CAN_IRQn);
}



/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
 a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num){
	// Turn on the yellow led and Enable timer interrupt
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, msg_obj.data[0]); //led 4 (yellow)
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
 an error has occured on the CAN bus */
void CAN_error(uint32_t error_info) {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (red)
}

void setPort(int port, bool onoff) {
	if (port == 0) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, onoff);
	if (port == 1) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, onoff);
	if (port == 2) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, onoff);
	if (port == 3) Chip_GPIO_WritePortBit(LPC_GPIO, 0, 3, onoff);
	if (port == 4) Chip_GPIO_WritePortBit(LPC_GPIO, 1, 5, onoff);
	if (port == 5) Chip_GPIO_WritePortBit(LPC_GPIO, 0, 5, onoff);
}

int main(void) {

	CAN_init();
	
	SystemCoreClockUpdate();
	//Enable and setup SysTick Timer at 1/1000 seconds (1ms)
	SysTick_Config(SystemCoreClock / 1000);

	//Enable timer 1 clock
	Chip_TIMER_Init(LPC_TIMER32_0);

	//Timer setup for match and interrupt at 1/10 seconds (100ms)
	Chip_TIMER_Reset(LPC_TIMER32_0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 1, (SystemCoreClock / 10));
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_0, 1);
	Chip_TIMER_Enable(LPC_TIMER32_0);
	
	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 2 | 1 << 3);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 1, 1 << 1 | 1 << 2 | 1 << 7 | 1 << 8 | 1 << 10);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 2 | 1 << 10);
	
	bool blinkLeftOn =		false;
	bool blinkLeftState =	false;
	bool blinkRightOn =		false;
	bool blinkRightState =	false;

	bool lightsOn =			false;
	bool alarmOn =			false;
	bool wiperOn =			false;

	bool ledOn =			false;
	unsigned long lastSystickcnt = 0;


	for (;;) //infinite loop
	{		
		bool blinkLeft = Chip_GPIO_ReadPortBit(LPC_GPIO, 0,3);
		bool blinkRight = Chip_GPIO_ReadPortBit(LPC_GPIO, 2,7);
		bool alarm = Chip_GPIO_ReadPortBit(LPC_GPIO, 2,8);
		bool lights = Chip_GPIO_ReadPortBit(LPC_GPIO, 0,2);
		bool wiper = Chip_GPIO_ReadPortBit(LPC_GPIO, 2,1);
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

		if(alarm != alarmOn)
		{
			blinkLeftOn = alarm;
			blinkRightOn = alarm;
			alarmOn = alarm;
		}

		if(lights != lightsOn)
		{
			//Toggle DIM_LIGHTS head and rear
			lightsOn = lights;
			msg_obj.msgobj = __COUNTER__;
			msg_obj.mode_id = DIM_ADDRESS | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			msg_obj.data[0] = lightsOn;
			LPC_CCAN_API->can_transmit(&msg_obj);
		}

		if(wiper != wiperOn)
		{
			//Toggle whiper, send to personal adress from whiper
			wiperOn = wiper;
			msg_obj.msgobj = __COUNTER__;
			msg_obj.mode_id = WHIPER_ADDRESS | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 5;
			msg_obj.data[0] = 0;
			msg_obj.data[1] = 0;
			msg_obj.data[2] = 0;
			LPC_CCAN_API->can_transmit(&msg_obj);

			if(wiperOn)
			{
				//first disable reset
				msg_obj.data[3] = false;
				msg_obj.data[4] = false;
				LPC_CCAN_API->can_transmit(&msg_obj);

				//then set wiper on
				msg_obj.data[3] = true;
				msg_obj.data[4] = true;
				Delay(100);				
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			else 
			{
				//first set wiper off
				msg_obj.data[3] = false;
				msg_obj.data[4] = false;
				LPC_CCAN_API->can_transmit(&msg_obj);

				//then enable reset
				msg_obj.data[3] = false;
				msg_obj.data[4] = true;
				Delay(100);
				LPC_CCAN_API->can_transmit(&msg_obj);
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
			msg_obj.msgobj = __COUNTER__;
			msg_obj.mode_id = LEFT_DEVICES + DIM_ADDRESS | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			//Turn on if there is no blink and (left_blinker or Alarm is on)
			if(!blinkLeftState)
			{
				blinkLeftState = true;
				msg_obj.data[0] = true;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			else
			{
				blinkLeftState = false;
				msg_obj.data[0] = false;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
		}

		//
		//Right Blink
		//
		if ((blinkRightOn || alarmOn) && ((LoopTick - lastClick) >= BLINK_FREQ))
		{
			click = true;
			msg_obj.msgobj = __COUNTER__;
			msg_obj.mode_id = RIGHT_DEVICES + DIM_ADDRESS | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			if (!blinkRightState)
			{
				blinkRightState = true;
				msg_obj.data[0] = true;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			else
			{
				blinkRightState = false;
				msg_obj.data[0] = false;
				LPC_CCAN_API->can_transmit(&msg_obj);
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
			
			msg_obj.msgobj = __COUNTER__;
			msg_obj.mode_id = (BROADCAST_ADDRESS + DEVICE_NR) | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			msg_obj.data[0] = DEVICE_NR;
			LPC_CCAN_API->can_transmit(&msg_obj);

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
connector schematic chip
1			d6		0,5
2			d7		0,3
3			d8		2,8
4			d9		0,2
5			d10		2,6
12			d1		0,4
13			d2		2,1
14			d3		2,7
15			d4		1,8
16			d5		2,0

int p1 = getPin(0,5);
int p2 = getPin(0,3); // --> right indicator
int p3 = getPin(2,8); // --> middle
int p4 = getPin(0,2); // --> left middle
int p5 = getPin(2,6);
int p12 = getPin(0,4);
int p13 = getPin(2,1); // --> right middle
int p14 = getPin(2,7); // --> left indicator
int p15 = getPin(1,8); //
int p16 = getPin(2,0); //

DEVICE ID config:
-------------

 name ||KIPPP| out |twins|front| 0b0000
======||===============================
  IN  ||--0--|--1--|--0--|--0--| 0b0000
Front ||--0--|--1--|--1--|--1--| 0b0111
 Back ||--0--|--1--|--1--|--0--| 0b0110
  Mid ||--0--|--1--|--0--|--0--| 0b0100
  HUD ||--1--|--0--|--0--|--1--| 0b1001
  Tor ||--1--|--0--|--0--|--0--| 0b1000
  Mid ||--0--|--1--|--0--|--0--| 0b0100
*/

// led 1 (green) power light
// led 2 (red) 2,10
// led 3 (yellow) 2,2
// led 4 (blue) 0,7
