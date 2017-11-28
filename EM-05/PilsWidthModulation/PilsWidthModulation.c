#include <chip.h>

#define	EM_04_CAN_RANGE		0x100
#define ALL_ADDRESS			(EM_04_CAN_RANGE+0x001)
#define PARTY_ADDRESS		(EM_04_CAN_RANGE+0x002)
#define STAHP_ADDRESS		(EM_04_CAN_RANGE+0x003)
#define DEVICE_NR			2
#define	PERSNOAL_MESSAGE	6
#define	ALL_MESSAGE			1
#define	TOTAL_MESSAGE		8
#define PARTY_MESSAGE		2
#define STAHP_MESSAGE		3
bool PartyButton;
bool HaltButton;
bool PartyTime = false;
bool Halt = false;
CCAN_MSG_OBJ_T msg_obj;
bool colour = true;
#define PWM_FREQ_RESHZ (100000)//Divider to system clock to get PWM prescale value
#define PWM_PRESCALER ((unsigned long)SystemCoreClock / (unsigned long)PWM_FREQ_RESHZ)

#define PWM_PERIOD_HZ (25000)
#define PWM_PERIOD_COUNT (PWM_FREQ_RESHZ / PWM_PERIOD_HZ)
#define PWM_DC_COUNT(a) ( (((101-a) * PWM_PERIOD_COUNT) / 100) )

void PWMUpdate(unsigned char ucPercent)
{
		Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, PWM_DC_COUNT(ucPercent));

}

void TIMER16_0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, 0))
	{
	
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, false);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, false);
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);
	}
	else if (Chip_TIMER_MatchPending(LPC_TIMER16_0, 1))
	{
		//Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, true);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, true);
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 1);
	}
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


void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);

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

	msg_obj.msgobj = PARTY_MESSAGE;
	msg_obj.mode_id = PARTY_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = STAHP_MESSAGE;
	msg_obj.mode_id = STAHP_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);




	/*
	if (DEVICE_NR == 2) // Front/Mid
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
	*/
	msg_obj.msgobj = PERSNOAL_MESSAGE;
	msg_obj.mode_id = DEVICE_NR;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	/* Enable the CAN Interrupt */
	NVIC_EnableIRQ(CAN_IRQn);
}

void CAN_rx(uint8_t msg_obj_num) {
	// Disable interupts while receiving
	NVIC_DisableIRQ(CAN_IRQn);
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;

	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if (msg_obj_num < TOTAL_MESSAGE || msg_obj_num > 0)
	{
		//Message "Inbox" for all the FRONT_MESSAGES {...}
		if (msg_obj_num == PARTY_MESSAGE)
		{
			colour = true;

		}

		if (msg_obj_num == STAHP_MESSAGE) {
			colour = false;
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

void CAN_IRQHandler(void) {
	LPC_CCAN_API->isr();
}
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

int main()
{
	CAN_init();

	//Enable timer 0 & 1 clock 
	Chip_TIMER_Init(LPC_TIMER16_0);
	//Reset any timer pending
	Chip_TIMER_Reset(LPC_TIMER16_0);
	//set the resolution of the ticks to the PWM timer (match register resolution)
	Chip_TIMER_PrescaleSet(LPC_TIMER16_0, (PWM_PRESCALER - 1));
	//Set duty cycle - MR0 default
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, PWM_DC_COUNT(0));
	//Enable interupt on MR0 & MR1
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 1);
	//MR0 should not stop or clear the timer
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_0, 0);
	//Set period - MR1
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 1, PWM_PERIOD_COUNT);
	//MR1 should reset the timer to restart the cycle
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_0, 1);
	//Enable the timer
	Chip_TIMER_Enable(LPC_TIMER16_0);
	// PWM mode enabled on CT32B0_MAT0
	((LPC_TIMER_T *)LPC_TIMER16_0)->PWMC = 1;
	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER_16_0_IRQn);
	NVIC_EnableIRQ(TIMER_16_0_IRQn);


	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	
	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7 | 1 << 8 | 1 << 9);

	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);
	PWMUpdate(20);
	for (;;)
	{
		Delay(30);
		if (colour) {
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);
			PWMUpdate(20);
				}
		else {
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);
			PWMUpdate(0);
		}
	}

	return 0;
}
