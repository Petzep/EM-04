/*
 ===============================================================================
 Name        : EM4_CAN_OUT_AS_IN.c
 Author      : Nephtaly Aniceta
 Version     : 0.5
 Copyright   : GPLv3
 Description : CAN_OUT used as input
	makeshift project to test the CANbus between multiple CAN_OUTs
 ===============================================================================
 */

#include <chip.h>

#define DEVICE_NR			0x020

#define ALL_ADDRESS			0x000
#define LIGHT_ADDRESS			0x008
#define FRONT_DEVICES		0x000
#define REAR_DEVICES		0x001
#define LEFT_DEVICES		0x002
#define RIGHT_DEVICES		0x003
#define BROADCAST_ADDRESS	0x030

#define	ALL_MESSAGE			1
#define FRONT_MESSAGE		2
#define	REAR_MESSAGE		3
#define	LEFT_MESSAGE		4
#define	RIGHT_MESSAGE		5
#define	PERSNOAL_MESSAGE	6
#define	LIGHT_MESSAGE			7
#define	TOTAL_MESSAGE		8

/*enum CAN_MESSAGE
{
	ALL_MESSAGE,
	FRONT_MESSAGE,
	REAR_MESSAGE,
	LEFT_MESSAGE,
	RIGHT_MESSAGE,
	PERSNOAL_MESSAGE,
	LIGHT_MESSAGE,
	TOTAL_MESSAGE,
};*/


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
void TIMER32_0_IRQHandler(void)
{
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
	CCAN_CALLBACKS_T callbacks = {
		CAN_rx,
		CAN_tx,
		CAN_error,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	};
	
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

	if (DEVICE_NR & 0b0010)
	{
		msg_obj.msgobj = FRONT_MESSAGE;
		msg_obj.mode_id = FRONT_DEVICES + LIGHT_ADDRESS; //0000 0000 101x
		msg_obj.mask = 0xFFE; //1111 1111 1110 filters for any LIGHT_ADDRESS in the F/R_DEVICES 
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}

	if (!(DEVICE_NR & 0b0010))
	{
		msg_obj.msgobj = REAR_MESSAGE;
		msg_obj.mode_id = REAR_DEVICES + LIGHT_ADDRESS; //0000 0000 100x
		msg_obj.mask = 0xFFE; //1111 1111 1110 filters for any LIGHT_ADDRESS in the F/R_DEVICES 
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}

	if (!(DEVICE_NR & 0b0001))
	{
		msg_obj.msgobj = LEFT_MESSAGE;
		msg_obj.mode_id = LEFT_DEVICES + LIGHT_ADDRESS; //0000 0000 10x0
		msg_obj.mask = 0xFFD; //1111 1111 1101 filters for any LIGHT_ADDRESS in the L/R_DEVICES
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}
	
	if (DEVICE_NR & 0b0001)
	{
		msg_obj.msgobj = RIGHT_MESSAGE;
		msg_obj.mode_id = RIGHT_DEVICES + LIGHT_ADDRESS; //0000 0000 10x1
		msg_obj.mask = 0xFFD; //1111 1111 1101 filters for any LIGHT_ADDRESS in the L/R_DEVICES
		LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	}

	msg_obj.msgobj = PERSNOAL_MESSAGE;
	msg_obj.mode_id = DEVICE_NR;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	//msg_obj.msgobj = LIGHT_MESSAGE;
	//msg_obj.mode_id = LIGHT_ADDRESS;
	//msg_obj.mask = 0xFFF;
	//->config_rxmsgobj(&msg_obj);
	
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
			setPort(2, msg_obj.data[0]);
		}

		if (msg_obj_num == REAR_MESSAGE)
		{
			setPort(2, msg_obj.data[0]);
		}

		if (msg_obj_num == LEFT_MESSAGE)
		{
			setPort(2, msg_obj.data[0]);
		}

		if (msg_obj_num == RIGHT_MESSAGE)
		{
			setPort(2, msg_obj.data[0]);
		}

		if (msg_obj_num == LIGHT_MESSAGE)
		{
			setPort(2, msg_obj.data[0]);
		}

		if (msg_obj_num == PERSNOAL_MESSAGE)
		{
			setPort(0, msg_obj.data[0]);
			setPort(1, msg_obj.data[1]);
			setPort(2, msg_obj.data[2]);
			setPort(3, msg_obj.data[3]);
			setPort(4, msg_obj.data[4]);
			setPort(5, msg_obj.data[5]);
		}

		if (msg_obj_num == ALL_MESSAGE)
		{
			
			setPort(0, msg_obj.data[0	]);
			setPort(1, msg_obj.data[1]);
			setPort(2, msg_obj.data[2]);
			setPort(3, msg_obj.data[3]);
			setPort(4, msg_obj.data[4]);
			setPort(5, msg_obj.data[5]);
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
void CAN_tx(uint8_t msg_obj_num) {

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
	
	//Timer setup for match and interrupt at 1/2 seconds (500ms)
	Chip_TIMER_Reset(LPC_TIMER32_0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 1, (SystemCoreClock/2));
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_0, 1);
	Chip_TIMER_Enable(LPC_TIMER32_0);
	
	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 3 | 1 << 5 | 1 << 7);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 5);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 1 | 1 << 2 | 1 << 7 | 1 << 8 | 1 << 10);
	
	bool ledOn = true;
	unsigned long lastSystickcnt = 0;

	for (;;)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);	//led 3 (blue)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);	//led 3 (blue)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //All on
		msg_obj.mode_id = ALL_ADDRESS |  CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0UL;
		msg_obj.dlc = 6;
		msg_obj.data[0] = true;
		msg_obj.data[1] = true;
		msg_obj.data[2] = true;
		msg_obj.data[3] = true;
		msg_obj.data[4] = true;
		msg_obj.data[5] = true;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //All off
		msg_obj.mode_id = ALL_ADDRESS |  CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0UL;
		msg_obj.dlc = 6;
		msg_obj.data[0] = false;
		msg_obj.data[1] = false;
		msg_obj.data[2] = false;
		msg_obj.data[3] = false;
		msg_obj.data[4] = false;
		msg_obj.data[5] = false;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //left on
		msg_obj.mode_id = (LIGHT_ADDRESS + LEFT_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = true;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //left off
		msg_obj.mode_id = (LIGHT_ADDRESS + LEFT_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = false;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //RIGHT on
		msg_obj.mode_id = (LIGHT_ADDRESS + RIGHT_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = true;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //RIGHT off
		msg_obj.mode_id = (LIGHT_ADDRESS + RIGHT_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = false;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //FRONT on
		msg_obj.mode_id = (LIGHT_ADDRESS + FRONT_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = true;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //FRONT off
		msg_obj.mode_id = (LIGHT_ADDRESS + FRONT_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = false;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //REAR on
		msg_obj.mode_id = (LIGHT_ADDRESS + REAR_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = true;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(1000);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		msg_obj.msgobj = 0; //REAR off
		msg_obj.mode_id = (LIGHT_ADDRESS + REAR_DEVICES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = false;
		LPC_CCAN_API->can_transmit(&msg_obj);
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
		
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);	//led 3 (blue)
		Delay(1000);
	}
	return 0;
}


/*
connector schematic chip
1			BJT1		2,7
2			BJT2		2,8
3			BJT3		2,1
4			BJT4		0,3
//5			BJT5		0,4
//6			BJT6		0,5
*/

// led 1 (green) power light
// led 2 (red) 2,10
// led 3 (yellow) 2,2
// led 4 (blue) 0,7