#include <chip.h>
//#include "Cannedy.h"
#define DEVICE_NR			2
#define ALL_ADDRESS			0x000
#define Party_ADDRESS		0x001
#define	PERSNOAL_MESSAGE	6
#define	ALL_MESSAGE			1
#define	TOTAL_MESSAGE		8
#define	EM_05_CAN_RANGE		0x100
#define CENTRAL_ADDRESS		(EM_05_CAN_RANGE+0x001)
#define LIGHT_ADDRESS		(EM_05_CAN_RANGE+0x002)
#define TORADEX_ADDRESS		(EM_05_CAN_RANGE+0x006)

#define CENTRAL_MESSAGE		1
#define LIGHT_MESSAGE		2
#define TORADEX_MESSAGE		3
CCAN_MSG_OBJ_T msg_obj;
bool Button = true;




/**
* @brief	CCAN Interrupt Handler
* @return	Nothing
* @note	The CCAN interrupt handler must be provided by the user application.
*	It's function is to call the isr() API located in the ROM
*/
void CAN_IRQHandler(void) {
	LPC_CCAN_API->isr();
}

/*ignore for now.*/
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

void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);



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

	msg_obj.msgobj = LIGHT_MESSAGE;
	msg_obj.mode_id = LIGHT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	/* Enable the CAN Interrupt */
	NVIC_EnableIRQ(CAN_IRQn);
}

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

		if (msg_obj_num == LIGHT_MESSAGE)
		{
			if (msg_obj.data[0] || msg_obj.data[1] || msg_obj.data[2])
			{
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);
			}
			else
			{
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);
			}

			if (msg_obj.data[4])
			{
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, false);
			}
			else
			{
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, true);
			}

			//Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, msg_obj.data[3]);
			Button = false;
		}


		// Turn on the yellow led and Enable timer interrupt
		//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (yellow)
		NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
		NVIC_EnableIRQ(TIMER_32_0_IRQn);
	}
	NVIC_EnableIRQ(CAN_IRQn);
}


void CAN_tx(uint8_t msg_obj_num) {
	//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (yellow)
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
an error has occured on the CAN bus */
void CAN_error(uint32_t error_info) {
	//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true); //led 3 (red)

}

volatile unsigned long SysTickCnt;

volatile static int i = 0;
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

int main()
{
	CAN_init();
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);

	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7 | 1 << 8 | 1 << 9);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 1);

	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, true);


	for (;;)
	{
		Delay(1);
	}
	return 0;
}
