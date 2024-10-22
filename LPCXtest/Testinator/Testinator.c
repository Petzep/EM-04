/*
 ===============================================================================
 Name        : Testinator.c
 Author      : Nephtaly Aniceta
 Version     :
 Copyright   : -
 Description : Testprogram
 ===============================================================================
 */

#include <chip.h>

#define DEVICE_NR			0x010

#define ALL_ADDRESS			0x000
#define LIGHT_ADDRESS			0x008
#define FRONT_DEVICES		0x000
#define LEFT_DEVICES		0x001
#define REAR_DEVICES		0x002
#define RIGHT_DEVICES		0x003
#define BROADCAST_ADDRESS	0x101

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

#ifdef __cplusplus
extern "C"
#endif
	
volatile unsigned long SysTickCnt;
uint8_t test = FRONT_DEVICES;
const uint32_t ExtRateIn	= 0;
const uint32_t OscRateIn	= 12000000;
const uint32_t RTCOscRateIn	= 32768;

CCAN_MSG_OBJ_T msg_obj;

void SysTick_Handler(void) {
	SysTickCnt++;
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

void setPort(int port, bool onoff) {
	if (port == 0) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, onoff);
	if (port == 1) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, onoff);
	if (port == 2) Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, onoff);
	if (port == 3) Chip_GPIO_WritePortBit(LPC_GPIO, 0, 3, onoff);
	if (port == 4) Chip_GPIO_WritePortBit(LPC_GPIO, 1, 5, onoff);
	if (port == 5) Chip_GPIO_WritePortBit(LPC_GPIO, 0, 5, onoff);
}

/* Callback function prototypes */
void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);

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
	
	/* Configure message object 1 to receive all 11-bit messages 0x400-0x4FF */
	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0x400;
	msg_obj.mask = 0x700; //0bx111 0000 0000
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	
	/* Configure message object 1 to receive all 11-bit messages 0x200-0x2FF */
	msg_obj.msgobj = 2;
	msg_obj.mode_id = 0x200;
	msg_obj.mask = 0x700; //0bx111 0000 0000
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	
	/* Configure message object 1 to receive all 11-bit messages 0x600-0x6FF */
	msg_obj.msgobj = 4;
	msg_obj.mode_id = 0x600;
	msg_obj.mask = 0x700; //0bx111 0000 0000
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	
	/* Enable the CAN Interrupt */
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
 a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num) {
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;
	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	
	if (msg_obj_num == 1) {
		/* Simply transmit CAN frame (echo) with with ID +0x100 via buffer 2 */
		msg_obj.msgobj = 0;
		msg_obj.mode_id += 0x100;
		LPC_CCAN_API->can_transmit(&msg_obj);
	}
	
	if (msg_obj_num == 2)
	{
		setPort(1, msg_obj.data[0]);
		/* Simply transmit CAN frame (echo) with with ID +0x100 via buffer 0 */
		msg_obj.msgobj = 0;
		msg_obj.mode_id += 0x010;
		LPC_CCAN_API->can_transmit(&msg_obj);
	}
	
		//all devices
	if (msg_obj_num == 4)
	{
		setPort(1, msg_obj.data[1]);
		setPort(2, msg_obj.data[2]);
		setPort(3, msg_obj.data[3]);
		setPort(4, msg_obj.data[4]);
		setPort(5, msg_obj.data[5]);
	}
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
	if (error_info & CAN_ERROR_PASS) {
		CAN_init();

	}
	else if (error_info & CAN_ERROR_BOFF) {
		CAN_init();
	}
	else {
		CAN_init();
	}
	return;
}



int main(void) {

	CAN_init();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	
	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 3 | 1 << 5 | 1 << 7);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 5);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 1 | 1 << 2 | 1 << 7 | 1 << 8 | 1 << 10);
	
	bool ledOn = true;
	unsigned long lastSystickcnt = 0;
	for (;;)
	{
		if ((SysTickCnt - lastSystickcnt) >= 1000)
		{
			lastSystickcnt = SysTickCnt;
			if (ledOn)
			{
				ledOn = false;
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);	//led 3 (blue)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 4 (yellow)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 2 (red)
				/* Send a simple one time CAN message */
				msg_obj.msgobj = 0;
				msg_obj.mode_id = 0x600UL;
				msg_obj.mask = 0x0UL;
				msg_obj.dlc = 2;
				msg_obj.data[0] = 0x00;
				msg_obj.data[1] = 0x00;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			else 
			{
				ledOn = true;
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);	//led 3 (blue)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led 4 (yellow)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led 2 (red)
				msg_obj.msgobj = 0;
				msg_obj.mode_id = 0x600UL;
				msg_obj.mask = 0x0UL;
				msg_obj.dlc = 2;
				msg_obj.data[0] = 0x00;
				msg_obj.data[1] = 0x01;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			
			/* Send a simple one time CAN message */
			msg_obj.msgobj = 0;
			msg_obj.mode_id = 0x123UL;
			msg_obj.mask = 0x0UL;
			msg_obj.dlc = 1;
			msg_obj.data[0] = 0x00;
			LPC_CCAN_API->can_transmit(&msg_obj);
		}
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

// led 1 (green) x,x
// led 2 (red) 2,10
// led 3 (yellow) 2,2
// led 4 (blue) 0,7