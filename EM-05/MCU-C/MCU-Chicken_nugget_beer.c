#include <chip.h>

#define	EM_05_CAN_RANGE		0x100
#define CENTRAL_ADDRESS		(EM_05_CAN_RANGE+0x001)
#define LIGHT_ADDRESS		(EM_05_CAN_RANGE+0x002)
#define BLOWER_ADDRESS		(EM_05_CAN_RANGE+0x003)
#define TORADEX_ADDRESS		(EM_05_CAN_RANGE+0x006)

#define CENTRAL_MESSAGE		1
#define LIGHT_MESSAGE		2
#define TORADEX_MESSAGE		3
#define	BLOWER_MESSAGE		4
#define	TOTAL_MESSAGE		8
CCAN_MSG_OBJ_T msg_obj;
bool Light[8];
bool measureLight[8];
bool knipperend[3];
bool LightChange = true;
bool Blowchange = true;

bool wiper_button;
bool wiper;
bool spuit_button;
bool spuit;
bool n00tn00t_button;
bool n00tn00t;
int Time = 0;
int knipperjob;
/*
	Licht data
0	stadslicht
1	dimlicht
2	groot licht
3	richting links		kniperen gebeurd op MCU-c
4	richting rechts		kniperen gebeurd op MCU-c
5	
6
7
*/

/*
	Voorruit data
0	spuit
1	whiper
2	toeter
3	blower


*/

volatile unsigned long SysTickCnt;
volatile unsigned long Knipper = 0;
bool knipper = 0;
static ADC_CLOCK_SETUP_T ADCSetup;
uint16_t dataADC1 = 0; //ADCdata1
uint16_t dataADC2 = 0; //ADCdata2
uint8_t	 blowjob = 0; // how hard to suck it
Status status;
#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	SysTickCnt++;
	Time++;
	Knipper++;
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
		if (msg_obj_num == CENTRAL_MESSAGE)
		{

		}

	

		// Turn on the yellow led and Enable timer interrupt
		//Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, msg_obj.data[0]); //led 4 (yellow)
		NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
		NVIC_EnableIRQ(TIMER_32_0_IRQn);
	}
	NVIC_EnableIRQ(CAN_IRQn);
}
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

	msg_obj.msgobj = CENTRAL_MESSAGE;
	msg_obj.mode_id = CENTRAL_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
	

	/* Enable the CAN Interrupt */
	NVIC_EnableIRQ(CAN_IRQn);
}

void SendLight() {
	
	msg_obj.msgobj = LIGHT_MESSAGE;     //__COUNTER__;
	msg_obj.mode_id = LIGHT_ADDRESS;
	msg_obj.mask = 0x0;
	msg_obj.dlc = 5;
	msg_obj.data[0] = Light[0];
	msg_obj.data[1] = Light[1];
	msg_obj.data[2] = Light[2];
	msg_obj.data[3] = Light[3];
	msg_obj.data[4] = Light[4];
	LPC_CCAN_API->can_transmit(&msg_obj);

	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 0);
	Delay(50);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 1);
}

void SendBobsandVagene() {
	msg_obj.msgobj = BLOWER_MESSAGE;     //__COUNTER__;
	msg_obj.mode_id = BLOWER_ADDRESS;
	msg_obj.mask = 0x0;
	msg_obj.dlc = 4;
	msg_obj.data[0] = spuit;
	msg_obj.data[1] = wiper;
	blowjob = dataADC2 / 10;
	msg_obj.data[3] = blowjob;
	LPC_CCAN_API->can_transmit(&msg_obj);

	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 0);
	Delay(50);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 1);
}

int main()
{
	CAN_init();
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	
	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 7 | 1 << 2 | 1 << 6 | 1 << 8 | 1 << 9 | 1 << 11);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 1, 1 << 4);

	for (int i = 0; i <= 7; i++) {
		Light[i] = false;
	}
	for (int i = 0; i <= 7; i++) {
		measureLight[i] = false;
	}

	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_SetBurstCmd(LPC_ADC, true);

	//Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_1, FUNC2); //ADC2
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_11, FUNC2);	//port 0 pin 11
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);					// channel of P0pin11
	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

	for (;;)
	{
		measureLight[0] = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 2);	//stadlicht
		measureLight[1] = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 6);	//dimlicht
		measureLight[2] = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 8);	//grootlicht
		measureLight[3] = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 9);	//richting links
		measureLight[4] = !Chip_GPIO_ReadPortBit(LPC_GPIO, 1, 4);	//richting rechts
		measureLight[5] = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 7);	//ALARM ERROR STREEEEEEEEESSSS WAAAAAAAAAAAAAAH

		
		for (int i = 0; i < 3; i++) {
			if (measureLight[i] != Light[i]) {
				Light[i] = measureLight[i];
				LightChange = true;
			}}
		
		if (measureLight[3] || measureLight[4] || measureLight[5]) {
			for (int i = 0; i < 3; i++) {
				if (measureLight[i+3] != knipperend[i]) {
					knipperjob = 1;
					knipperend[i] = measureLight[i+3];
					LightChange = true;
					Knipper = 0;
				}
				
			}
			if (Knipper < 500 && knipperjob != 2) {
				LightChange = true;
				knipperjob = 2;
				Light[3] = knipperend[0];
				Light[4] = knipperend[1];
				if (knipperend[2]) {
					Light[3] = true;
					Light[4] = true;
			}
			}
			else if(Knipper > 500 && knipperjob != 3){
				LightChange = true;
				knipperjob = 3;
				Light[3] = false;
				Light[4] = false;
				
			}
			if (Knipper > 1000) {
				Knipper = 0;
			}
		}
		if(!measureLight[3] && !measureLight[4] && !measureLight[5] && knipperjob != 4)
		{
			knipperjob = 4;
			Light[3] = false;
			Light[4] = false;
			knipperend[0] = false;
			knipperend[1] = false;
			knipperend[2] = false;
			Knipper = 0;
			LightChange = true;
		}
		

		
		for (int i = 0; i < 500000; i++) {
			if (Chip_ADC_ReadStatus(LPC_ADC, ADC_CH0, ADC_DR_DONE_STAT) == SET) {
				break;
			}
		}
		//Read ADC value
		Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &dataADC1);
		status = Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &dataADC1);

		if ((dataADC1+40 < dataADC2 ) || (dataADC1-40 > dataADC2)) {
			dataADC2 = dataADC1;
			Blowchange = true;
		}
		wiper_button = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 8);	//ruitenwisser
		spuit_button = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 9);	//sproeier
		n00tn00t_button = !Chip_GPIO_ReadPortBit(LPC_GPIO, 0, 9);	//Claxoon/toeter/n00tn00t
		if (wiper != wiper_button) {
			wiper = wiper_button;
			Blowchange = true;
		}
		if (spuit != spuit_button) {
			spuit = spuit_button;
			Blowchange = true;
		}
		if (n00tn00t != n00tn00t_button) {
			n00tn00t = n00tn00t_button;
			Blowchange = true;
		}
		
		
		if (Time > 1000)
		{
			dataADC2 = dataADC1;
			Blowchange = false;
			LightChange = false;
			Time = 0;
			SendBobsandVagene();
			SendLight();
		}

		if (Blowchange)
		{
			Blowchange = false;
			SendBobsandVagene();
		}
		if (LightChange)
		{
			LightChange = false;
			SendLight();
	}
	}

	return 0;
}
