/*
===============================================================================
Name        : EM4_CAN_OUT.c
Author      : Nephtaly Aniceta
Version     : 1.0 Final
Copyright   : GPLv3
Description : Main CAN OUT Function
Inspired by work from previous years.
Rewritten for Visual Studio and LPCOpen v2.xx
===============================================================================
*/

#include <chip.h>

#define DEVICE_NR			0b1100
#define	EM_04_CAN_RANGE		0x100

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
#define CLAXON_ADDRESS		(0x007 + COUT_ADDRESS)
#define BLOWER_ADDRESS		(0x008 + COUT_ADDRESS)
#define HUD_ADDRESS			(0x030 + COUT_ADDRESS)
#define SPEED_ADDRESS		(0x001 + HUD_ADDRESS)
#define WARNING_ADDRESS		(0x002 + HUD_ADDRESS)
#define TEMPERATURE_ADDRESS	(0x003 + HUD_ADDRESS)
#define BATTERY_ADDRESS		(0x004 + HUD_ADDRESS)
#define DIMMER_ADDRESS		(0x005 + HUD_ADDRESS)
#define CLOCK_ADDRES		(0x00a + HUD_ADDRESS)
#define MC_ADDRESS			(0x040 + EM_04_CAN_RANGE)
#define MC_SPEED_STAT		(0x001 + MC_ADDRESS)
#define MC_MOTOR_STAT		(0x002 + MC_ADDRESS)
#define MC_I2C				(0x003 + MC_ADDRESS)
#define MC_DNR				(0x004 + MC_ADDRESS)
#define BROADCAST_ADDRESS	(0x050 + EM_04_CAN_RANGE)

#define	ALL_MESSAGE			1
#define	PERSNOAL_MESSAGE	2
#define	FAN_MESSAGE			3
#define	TOTAL_MESSAGE		4

// To have the timer tick run at 100,000 Hz, the prescaler is SYSTEM CLOCK / 100,000
#define PWM_FREQ_RESHZ (100000)//Divider to system clock to get PWM prescale value
#define PWM_PRESCALER ((unsigned long)SystemCoreClock / (unsigned long)PWM_FREQ_RESHZ)

#define PWM_PERIOD_HZ (25000)
#define PWM_PERIOD_COUNT (PWM_FREQ_RESHZ / PWM_PERIOD_HZ)
#define PWM_DC_COUNT(a) ( (((101-a) * PWM_PERIOD_COUNT) / 100) )

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

#ifdef __cplusplus
extern "C"
#endif

volatile unsigned long SysTickCnt;

const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;
const int min_dutyCycle = 35;
const int max_dutyClycle = 99;
int dutyCycle = 35;


CCAN_MSG_OBJ_T msg_obj;
/**
* @brief	Handle interrupt from SysTick timer
* @return	Nothing
*/
void SysTick_Handler(void)
{
	SysTickCnt++;
}


/**
* @brief	Updated the PWM dutycycle
* @return	Nothing
*/
void PWMUpdate(int fan, unsigned char ucPercent)
{
	if(fan == 0)
		Chip_TIMER_SetMatch(LPC_TIMER32_0, 0, PWM_DC_COUNT(ucPercent));
	else if(fan == 1)
		Chip_TIMER_SetMatch(LPC_TIMER32_1, 0, PWM_DC_COUNT(ucPercent));

}

/**
* @brief	Handle interrupt from 32-bit timer (Fan)
* @return	Nothing
*/
void TIMER32_0_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 3, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 3, false);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 1);
	}
}

void TIMER32_1_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_1, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER32_1, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, false);
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 1);
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

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


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

	msg_obj.msgobj = FAN_MESSAGE;
	msg_obj.mode_id = FAN_ADDRESS;
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
		if (msg_obj_num == FAN_MESSAGE)
		{
			int setting = msg_obj.data[1];
			if (setting > 100)
				dutyCycle = 100;

			if(setting <= 0)
			{
				dutyCycle = min_dutyCycle;
			}
			else
				dutyCycle = map(setting, 0, 100, min_dutyCycle, max_dutyClycle);

			PWMUpdate(msg_obj.data[0], dutyCycle);
		}

		/*if (msg_obj_num == PERSNOAL_MESSAGE)
		{
		
		}*/

		/*if (msg_obj_num == ALL_MESSAGE)
		{

		}*/

		// Turn on the yellow led and Enable timer interrupt
	}
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num) {

}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
an error has occured on the CAN bus */
void CAN_error(uint32_t error_info) {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (red)
}

int main(void) {

	CAN_init();

	SystemCoreClockUpdate();
	//Enable and setup SysTick Timer at 1/1000 seconds (1ms)
	SysTick_Config(SystemCoreClock / 1000);

	//Enable timer 0 & 1 clock (2 & 3 for speed)
	Chip_TIMER_Init(LPC_TIMER32_0);
	Chip_TIMER_Init(LPC_TIMER32_1);
	Chip_TIMER_Init(LPC_TIMER16_0);
	Chip_TIMER_Init(LPC_TIMER16_1);
	//Reset any timer pending
	Chip_TIMER_Reset(LPC_TIMER32_0);
	Chip_TIMER_Reset(LPC_TIMER32_1);
	Chip_TIMER_Reset(LPC_TIMER16_0);
	Chip_TIMER_Reset(LPC_TIMER16_1);
	//set the resolution of the ticks to the PWM timer (match register resolution)
	Chip_TIMER_PrescaleSet(LPC_TIMER32_0, (PWM_PRESCALER - 1));
	Chip_TIMER_PrescaleSet(LPC_TIMER32_1, (PWM_PRESCALER - 1));
	//Set the resolution of the ticks for the timer to on nano
	Chip_TIMER_PrescaleSet(LPC_TIMER16_1, (SystemCoreClock / 1000000));
	Chip_TIMER_PrescaleSet(LPC_TIMER16_1, (SystemCoreClock / 1000000));
	//Set Match on capture
	Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER16_0, 0);
	Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER16_1, 0);
	//Set Interupt on capture
	Chip_TIMER_CaptureEnableInt(LPC_TIMER16_0, 0);
	Chip_TIMER_CaptureEnableInt(LPC_TIMER16_1, 0);
	//Set duty cycle - MR0 default
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER32_1, 0, PWM_DC_COUNT(0));
	//Enable interupt on MR0 & MR1
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 1);
	//MR0 should not stop or clear the timer
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_0, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_1, 0);
	//Set period - MR1
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 1, PWM_PERIOD_COUNT);
	Chip_TIMER_SetMatch(LPC_TIMER32_1, 1, PWM_PERIOD_COUNT);
	//MR1 should reset the timer to restart the cycle
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_0, 1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_1, 1);
	//Enable the timer
	Chip_TIMER_Enable(LPC_TIMER32_0);
	Chip_TIMER_Enable(LPC_TIMER32_1);
	Chip_TIMER_Enable(LPC_TIMER16_0);
	Chip_TIMER_Enable(LPC_TIMER16_1);
	// PWM mode enabled on CT32B0_MAT0
	((LPC_TIMER_T *)LPC_TIMER32_0)->PWMC = 1;
	((LPC_TIMER_T *)LPC_TIMER32_1)->PWMC = 1;

	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 2);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 1, 1 << 8);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7 | 1 << 3);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 1 | 1 << 2 | 1 << 10);

	//PinFunction
	Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO0_2, IOCON_MODE_PULLUP, IOCON_FUNC2);
	Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO1_8, IOCON_MODE_PULLUP, IOCON_FUNC1);

	unsigned long lastSystickcnt = 0;
	PWMUpdate(0, dutyCycle);
	PWMUpdate(1, dutyCycle);

	for (;;)
	{
		if((SysTickCnt - lastSystickcnt) >= 1000)
		{
			lastSystickcnt = SysTickCnt;

			msg_obj.msgobj = 0;
			msg_obj.mode_id = (BROADCAST_ADDRESS + DEVICE_NR) | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			msg_obj.data[0] = DEVICE_NR;
			LPC_CCAN_API->can_transmit(&msg_obj);

			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 7);	//led 3 (blue)
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
   MC ||--1--|--1--|--1--|--0--|  14 | 0b1110

*/
/*
int test = 0b1100
;*/
