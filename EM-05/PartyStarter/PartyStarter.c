#include <chip.h>
//#include "Canny.h"
#define DEVICE_NR			1
#define ALL_ADDRESS			0x000
#define Party_ADDRESS		0x001
#define	PERSNOAL_MESSAGE	6
#define	ALL_MESSAGE			1
#define	TOTAL_MESSAGE		8
#define Party_MESSAGE		2
bool PartyButton;
bool PartyTime = false;
CCAN_MSG_OBJ_T msg_obj;

//data delay
bool Running[8];
unsigned long Time[8];
//LED states
bool LEDstate[8];

/**
* @brief	CCAN Interrupt Handler
* @return	Nothing
* @note	The CCAN interrupt handler must be provided by the user application.
*	It's function is to call the isr() API located in the ROM
*/



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
		//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, msg_obj.data[0]); //led 4 (yellow)
		NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
		NVIC_EnableIRQ(TIMER_32_0_IRQn);
	}
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num) {
	// Turn on the yellow led and Enable timer interrupt
	//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, msg_obj.data[0]); //led 4 (yellow)
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
an error has occured on the CAN bus */
void CAN_error(uint32_t error_info) {
	//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (red)
}

void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);

void CAN_IRQHandler(void) {
	LPC_CCAN_API->isr();
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

	/* Enable the CAN Interrupt */
	NVIC_EnableIRQ(CAN_IRQn);
}


/*	CAN receive callback */

volatile unsigned long SysTickCnt;

#ifdef __cplusplus
extern "C"
#endif
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
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

void Party() {
	
		msg_obj.msgobj = Party_MESSAGE;     //__COUNTER__;
		msg_obj.mode_id = Party_ADDRESS;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = true;
		LPC_CCAN_API->can_transmit(&msg_obj);

		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 0);
	Delay(100);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 1);
	PartyTime = false;

}
void partycheck() {
	if (!PartyTime) {
		PartyButton = Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 7);
		PartyTime = !PartyButton;
		
	}
}


void Blink(int ms, int nr, int LED) {
	if (!Running[nr]) {
		Time[nr] = SysTickCnt;
		Running[nr] = true;
	}
	if ((SysTickCnt - Time[nr]) > ms) {
		ToggleLED(LED);
		Running[nr] = false;
	}
}

void ToggleLED(int LED) {
	LEDstate[LED] = !LEDstate[LED];


	if (LED == 1) {
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, LEDstate[LED]);
	}
	
}


int main()
{
	CAN_init();
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	
	for (int p = 0; p < 7; p++) {
		Running[p] = false;
		Time[p] = 0;

	}

	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 7);
	for (;;)
	{
		Blink(500, 1, 1);
		partycheck();
		if (PartyTime) {
			Party();
		}

	}

	return 0;
}
