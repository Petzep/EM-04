/*
 ===============================================================================
 Name        : EM4_CAN_OUT.c
 Author      : Nephtaly Aniceta
 Version     : 0.9
 Copyright   : GPLv3
 Description : Main CAN OUT Function
	Inspired by work from previous years.
	Rewritten for Visual Studio and LPCOpen v2.xx
 ===============================================================================
 */

#include <chip.h>

#define DEVICE_NR			0b0111
#define	EM_04_CAN_RANGE		0x100

#define ALL_ADDRESS			(0x000 + EM_04_CAN_RANGE)
#define FAN_ADDRESS			(0x010 + EM_04_CAN_RANGE)
#define COUT_ADDRESS		(0x020 + EM_04_CAN_RANGE)
#define LIGHT_ADDRESS		(0x001 + COUT_ADDRESS)
#define FRONT_ADDRESS		(0x002 + COUT_ADDRESS)
#define REAR_ADDRESS		(0x003 + COUT_ADDRESS)
#define LEFT_ADDRESS		(0x004 + COUT_ADDRESS)
#define RIGHT_ADDRESS		(0x005 + COUT_ADDRESS)
#define WIPER_ADDRESS		(0x006 + COUT_ADDRESS)
#define BLOWER_ADDRESS		(0x007 + COUT_ADDRESS)
#define HUD_ADDRESS			(0x030 + COUT_ADDRESS)
#define SPEED_ADDRESS		(0x001 + HUD_ADDRESS)
#define WARNING_ADDRESS		(0x002 + HUD_ADDRESS)
#define TEMPERATURE_ADDRESS	(0x003 + HUD_ADDRESS)
#define BATTERY_ADDRESS		(0x004 + HUD_ADDRESS)
#define DIMMER_ADDRESS		(0x005 + HUD_ADDRESS)
#define CLOCK_ADDRES		(0x00a + HUD_ADDRESS)
#define MC_ADDRESS			(0x040 + EM_04_CAN_RANGE)
#define MC_SIGNAL1			(0x001 + MC_ADDRESS)
#define MC_SIGNAL2			(0x002 + MC_ADDRESS)
#define MC_I2C				(0x003 + MC_ADDRESS)
#define BROADCAST_ADDRESS (0x700)

#define	ALL_MESSAGE			1
#define FRONT_MESSAGE		2
#define	REAR_MESSAGE		3
#define	LEFT_MESSAGE		4
#define	RIGHT_MESSAGE		5
#define	PERSNOAL_MESSAGE	6
#define	LIGHT_MESSAGE			7
#define WIPER_MESSAGE		8
#define BLOWER_MESSAGE		9
#define	TOTAL_MESSAGE		10

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

#ifdef __cplusplus
extern "C"
#endif
	
volatile unsigned long SysTickCnt;

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
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (yellow)
	}
}

/**
* @brief	Delay function in (SysTick / x) (default x = 1000, Delay in ms)
* @return	Nothing
*/
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

/**
* @brief	Baudrate calculator
* @return	Baudrates on for the CAN
*/
void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg){
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

/* CAN Initialise */
/* Initialises the CAN and configures the filters*/
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

	if(DEVICE_NR == 0b0111) // Front/Mid
	{
		msg_obj.msgobj = WIPER_MESSAGE;
		msg_obj.mode_id = WIPER_ADDRESS;
		msg_obj.mask = 0xFFF;
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);

		msg_obj.msgobj = BLOWER_MESSAGE;
		msg_obj.mode_id = BLOWER_ADDRESS;
		msg_obj.mask = 0xFFF;
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}
	if (DEVICE_NR & 0b0001) //Select only the front bit of the twins [bug for mid, solve by shifting]
	{
		msg_obj.msgobj = FRONT_MESSAGE;
		msg_obj.mode_id = FRONT_ADDRESS;
		msg_obj.mask = 0xFFF;
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}

	if (!(DEVICE_NR & 0b0001)) //Select only the rear bit (=not front bit) of the twins [bug for mid, solve by shifting]
	{
		msg_obj.msgobj = REAR_MESSAGE;
		msg_obj.mode_id = REAR_ADDRESS; 
		msg_obj.mask = 0xFFF;
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}

	if (DEVICE_NR & 0b0010)  //Select only the twin bit
	{
		msg_obj.msgobj = LEFT_MESSAGE;
		msg_obj.mode_id = LEFT_ADDRESS;
		msg_obj.mask = 0xFFF;
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);

		msg_obj.msgobj = RIGHT_MESSAGE;
		msg_obj.mode_id = RIGHT_ADDRESS;
		msg_obj.mask = 0xFFF;
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}

	msg_obj.msgobj = PERSNOAL_MESSAGE;
	msg_obj.mode_id = DEVICE_NR;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = LIGHT_MESSAGE;
	msg_obj.mode_id = LIGHT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API -> config_rxmsgobj(&msg_obj);
	
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
		if (msg_obj_num == FRONT_MESSAGE)
		{
			setPort(0, msg_obj.data[0]);
		}

		if (msg_obj_num == REAR_MESSAGE)
		{
			setPort(0, msg_obj.data[0]);
		}

		if (msg_obj_num == LEFT_MESSAGE)
		{
			setPort(1, msg_obj.data[0]);
		}

		if (msg_obj_num == RIGHT_MESSAGE)
		{
			setPort(2, msg_obj.data[0]);
		}

		if (msg_obj_num == LIGHT_MESSAGE)
		{
			//Toggle DIM_lights (Head and rear)
			setPort(3, msg_obj.data[0]);
		}

		if(msg_obj_num == WIPER_MESSAGE)
		{
			setPort(6, msg_obj.data[0]);
		}

		if(msg_obj_num == BLOWER_MESSAGE)
		{
			setPort(7, msg_obj.data[0]);
		}

		if (msg_obj_num == PERSNOAL_MESSAGE)
		{
			setPort(0, msg_obj.data[0]);
			setPort(1, msg_obj.data[1]);
			setPort(2, msg_obj.data[2]);
			setPort(3, msg_obj.data[3]);
			setPort(4, msg_obj.data[4]);
			setPort(5, msg_obj.data[5]);
			setPort(6, msg_obj.data[6]);
			setPort(7, msg_obj.data[7]);
		}

		if (msg_obj_num == ALL_MESSAGE)
		{
			if(msg_obj.data[0])
			{
				setPort(0, true);
				setPort(1, true);
				setPort(2, true);
				setPort(3, true);
				setPort(4, true);
				setPort(5, true);
				setPort(6, true);
				setPort(7, true);
			}
			else
			{
				setPort(0, false);
				setPort(1, false);
				setPort(2, false);
				setPort(3, false);
				setPort(4, false);
				setPort(5, false);
				setPort(6, false);
				setPort(7, false);
			}

		}
		// Turn on the yellow led and Enable timer interrupt
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (yellow)
		NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
		NVIC_EnableIRQ(TIMER_32_0_IRQn);
	}
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
 a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num){
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (yellow)
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
 an error has occured on the CAN bus */
void CAN_error(uint32_t error_info){
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true); //led 3 (red)
}

void setPort(int port, bool onoff){
	if (port == 0) Chip_GPIO_WritePortBit(LPC_GPIO, 1, 7, onoff);
	if (port == 1) Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, onoff);
	if (port == 2) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, onoff);
	if (port == 3) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, onoff);
	if (port == 4) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, onoff);
	if (port == 5) Chip_GPIO_WritePortBit(LPC_GPIO, 0, 3, onoff);
	if (port == 6) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, onoff);
	if (port == 7) Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, onoff);
}


int main(void){

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
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 3 | 1 << 7);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 7 | 1 << 10);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 1 | 1 << 2 | 1 << 5 | 1 << 7 | 1 << 8 | 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 3, 1 << 3);
	
	unsigned long lastSystickcnt = 0;

	setPort(0, false);
	setPort(1, false);
	setPort(2, false);
	setPort(3, false);
	setPort(4, false);
	setPort(5, false);
	setPort(6, false);
	setPort(7, false);

	for (;;)
	{
		if ((SysTickCnt - lastSystickcnt) >= 1000)
		{
			lastSystickcnt = SysTickCnt;
			
			msg_obj.msgobj = 0;
			msg_obj.mode_id = (BROADCAST_ADDRESS + DEVICE_NR) | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			msg_obj.data[0] = DEVICE_NR;
			LPC_CCAN_API->can_transmit(&msg_obj);

			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 7);	//led 4 (blue)
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
led 1 (green)	power light
led 2 (yellow)	2,10
led 3 (red)		2,2
led 4 (blue)	0,7

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
   MC ||--1--|--1--|--1--|--0--|  14 | 0b1110

*/
/*
int test = 0b1100
;*/
