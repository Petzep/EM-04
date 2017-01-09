/*
===============================================================================
Name        : EM4_HUD_CAN.c
Author      : Daniel van der Klooster & Nephtaly Aniceta
Version     :
Copyright   : -
Description : Main HUD Function
Controls the HUD of EM-04
===============================================================================
*/

#include <chip.h>

#define DEVICE_NR			0b0110
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
#define BATTERY_ADDRESS		(0x003 + HUD_ADDRESS)
#define WARNING_ADDRESS		(0x002 + HUD_ADDRESS)
#define BROADCAST_ADDRESS	(0x030 + EM_04_CAN_RANGE)

#define	ALL_MESSAGE			1
#define	PERSNOAL_MESSAGE	2
#define	SPEED_MESSAGE		3
#define BATTERY_MESSAGE		4
#define WARNING_MESSAGE		5
#define	TOTAL_MESSAGE		6

#define RGB_TOP 1
#define RGB_BOT 0

// To have the timer tick run at 100,000 Hz, the prescaler is SYSTEM CLOCK / 100,000
#define PWM_FREQ_RESHZ (100000)//Divider to system clock to get PWM prescale value
#define PWM_PRESCALER ((unsigned long)SystemCoreClock / (unsigned long)PWM_FREQ_RESHZ)

#define PWM_PERIOD_HZ (1000)
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

CCAN_MSG_OBJ_T msg_obj;

enum RGB_LED
{
	redLed,
	greenLed,
	blueLed,
};

/**
* @brief	Handle interrupt from SysTick timer
* @return	Nothing
*/
void SysTick_Handler(void)
{
	SysTickCnt++;
}


void PWMUpdate(int pwm, unsigned char ucPercent)
{
	//set match register that control duty cycle
	switch(pwm)
	{
		case 0:
			Chip_TIMER_SetMatch(LPC_TIMER32_0, 0, PWM_DC_COUNT(ucPercent));
			break;
		case 1:
			Chip_TIMER_SetMatch(LPC_TIMER32_1, 0, PWM_DC_COUNT(ucPercent));
			break;
		case 2:
			Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, PWM_DC_COUNT(ucPercent));
			break;
		case 3:
			Chip_TIMER_SetMatch(LPC_TIMER16_1, 0, PWM_DC_COUNT(ucPercent));
			break;
		default:
			break;
	}
}

/**
* @brief	Handle interrupt from 32-bit timer
* @return	Nothing
*/
void TIMER32_0_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, false);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 1);
	}
}

void TIMER32_1_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_1, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER32_1, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, false);
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 1);
	}
}

void TIMER16_0_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER16_0, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER16_0, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 1);
	}
}

void TIMER16_1_IRQHandler(void)
{
	//if(Chip_TIMER_MatchPending(LPC_TIMER16_1, 0))
		//Chip_GPIO_SetPinToggle(LPC_GPIO, 7, 0);
}
/**
* @brief	Delay function in (SysTick / x) (default x = 1000, Delay in ms)
* @return	Nothing
*/
void Delay(unsigned long tick)
{
	unsigned long systickcnt;

	systickcnt = SysTickCnt;
	while((SysTickCnt - systickcnt) < tick)
		;
}

/**
* @brief	CCAN Interrupt Handler
* @return	Nothing
* @note	The CCAN interrupt handler must be provided by the user application.
*	It's function is to call the isr() API located in the ROM
*/
void CAN_IRQHandler(void)
{
	LPC_CCAN_API->isr();
}

/**
* @brief	Baudrate calculator
* @return	Baudrates on for the CAN
*/
void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg)
{
	uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
	pClk = Chip_Clock_GetMainClockRate();

	clk_per_bit = pClk / baud_rate;

	for(div = 0; div <= 15; div++)
	{
		for(quanta = 1; quanta <= 32; quanta++)
		{
			for(segs = 3; segs <= 17; segs++)
			{
				if(clk_per_bit == (segs * quanta * (div + 1)))
				{
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

/* CAN Initialise */
/* Initialises the CAN and configures the filters*/
void CAN_init()
{
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

	msg_obj.msgobj = SPEED_MESSAGE;
	msg_obj.mode_id = SPEED_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = BATTERY_MESSAGE;
	msg_obj.mode_id = BATTERY_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = WARNING_MESSAGE;
	msg_obj.mode_id = WARNING_ADDRESS;
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
void CAN_rx(uint8_t msg_obj_num)
{
	// Disable interupts while receiving
	//NVIC_DisableIRQ(CAN_IRQn);
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;

	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if(msg_obj_num < TOTAL_MESSAGE || msg_obj_num > 0)
	{
		if(msg_obj_num == PERSNOAL_MESSAGE)
		{
			int deadbeaf = 7331;
		}
	}
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num)
{

}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
an error has occured on the CAN bus */
void CAN_error(uint32_t error_info)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true); //led 2 (red)
}

//7-seg tick function
void Tick() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//7Seg
}

void TickBat() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 5, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 5, false);	//Bat
}

void TickDNR() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 1, false);	//DNR
}

void DataHighBat() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, true);
}

void DataLowBat() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, false);
}

void Strobef() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, true);
	
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, false);	//7Seg

}

void StrobefBat(){
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 7, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 7, false);	//Bat
}

void StrobefDNR() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, false);	//Bat
}

//7-seg sub function
void sevenSegNumber(int number, bool dotOn) {
	unsigned long long value;
	switch(number)
	{
		case 0:
			value = 0b00111111;
			break;
		case 1:
			value = 0b00110000;
			break;
		case 2:
			value = 0b01101101;
			break;
		case 3:
			value = 0b01111001;
			break;
		case 4:
			value = 0b01110010;
			break;
		case 5:
			value = 0b01011011;
			break;
		case 6:
			value = 0b01011111;
			break;
		case 7:
			value = 0b00110001;
			break;
		case 8:
			value = 0b01111111;
			break;
		case 9:
			value = 0b01111011;
			break;
		default:
			value = NULL;
			break;
	}

	unsigned int count = 0;
	
	if(dotOn)
		value |= 0b10000000;

	for(int i = 0; i < 8; i++)
	{
		unsigned long long bit = value & 0b10000000;
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, bit);
		Tick();
		value <<= 1;
	}
	
}

//7-seg function
void sevenSeg(bool dotOn, int number, int pwm)
{
	PWMUpdate(2, pwm);
	if(dotOn)
	{
		sevenSegNumber(number / 10, true);
		sevenSegNumber(number % 10, false);
		Strobef();
	}
	else
	{
		sevenSegNumber(number / 10, false);
		sevenSegNumber(number % 10, false);
	}
	Strobef();
}

//Battery Fill Rourtine
void BatFill(int speed) {
	for (int i = 0; i < 5; i++) {
		DataHighBat();
		TickBat();
		StrobefBat();
		for (int j = 0; j < speed; j++) {
			if ((j % 25) == 1) {
				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 1);
				Delay(1);
			}
			else {
				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);
				Delay(1);
			}
		}
	}


	for (int i = 0; i < 5; i++) {
		DataLowBat();
		TickBat();
		StrobefBat();
		for (int j = 0; j < speed; j++) {
			if ((j % 20) == 1) {
				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 1);
				Delay(1);
			}
			else {
				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);
				Delay(1);
			}
		}
	}
}

//Battery till 10
void BatClock(int counter) {
	for (int i = 0; i < (10-counter); i++) {
		DataLowBat();
		TickBat();
	}


	for (int i = 0; i < counter; i++) {
		DataHighBat();
		TickBat();
	}
	StrobefBat();
}

//DNR alphanumerical
void DNR(char ch, int pwm)
{
	unsigned long long value;
	PWMUpdate(1, pwm);
	switch(ch)
	{
		case 'A':
		case 'a':
			value = 0b000001110111;
			break;
		case 'B':
			value = 0b011000111001;
			break;
		case 'b':
			value = 0b000001111100;
			break;
		case 'C':
		case 'c':
			value = 0b000000111001;
			break;
		case 'D':
			value = 0b000010001111;
			break;
		case 'd':
			value = 0b000001011110;
			break;
		case 'E':
		case 'e':
			value = 0b000001111001;
			break;
		case 'F':
		case 'f':
			value = 0b000001110001;
			break;
		case 'G':
		case 'g':
			value = 0b010000111001;
			break;
		case 'H':
			value = 0b000001110110;
			break;
		case 'h':
			value = 0b00001110100;
			break;
		case 'I':
			value = 0b000010001001;
			break;
		case 'i':
			value = 0b000010000000;
			break;
		case 'J':
			value = 0b000000011110;
			break;
		case 'j':
			value = 0b100000001110;
			break;
		case 'K':
			value = 0b011001110000;
			break;
		case 'k':
			value = 0b011010000000;
			break;
		case 'L':
		case 'l':
			value = 0b000000111000;
			break;
		case 'M':
		case 'm':
			value = 0b001100110110;
			break;
		case 'N':
		case 'n':
			value = 0b010100110110;
			break;
		case 'O':
		case 'o':
			value = 0b000000111111;
			break;
		case 'p':
		case 'P':
			value = 0b000001110011;
			break;
		case 'Q':
		case 'q':
			value = 0b010000111111;
			break;
		case 'R':
		case 'r':
			value = 0b010001110011;
			break;
		case 'S':
		case 's':
			value = 0b000001101101;
			break;
		case 'T':
		case 't':
			value = 0b000010000001;
			break;
		case 'U':
		case 'u':
			value = 0b000000111110;
			break;
		case 'V':
			value = 0b101000110000;
			break;
		case 'v':
			value = 0b001100000000;
			break;
		case 'W':
		case 'w':
			value = 0b110000110110;
			break;
		case 'X':
		case 'x':
			value = 0b111100000000;
			break;
		case 'Y':
		case 'y':
			value = 0b001110000000;
			break;
		case 'Z':
		case 'z':
			value = 0b101001001001;
			break;
		case '0':
			value = 0b000000111111;
			break;
		case '1':
			value = 0b001000000110;
			break;
		case '2':
			value = 0b000001011011;
			break;
		case '3':
			value = 0b000001001111;
			break;
		case '4':
			value = 0b000001100110;
			break;
		case '5':
			value = 0b000001101101;
			break;
		case '6':
			value = 0b000001111101;
			break;
		case '7':
			value = 0b000000000111;
			break;
		case '8':
			value = 0b000001111111;
			break;
		case '9':
			value = 0b000001101111;
			break;
		default:
			value = NULL;
			break;
	}

	unsigned int count = 0;
	for(int i = 0; i < 12; i++)
	{
		unsigned long long bit = value & 0b100000000000;
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, bit);
		TickDNR();
		value <<= 1;
	}
	StrobefDNR();
}

//Set RGBLeds
void rgbLed(bool topBot, enum RGB_LED rgb)
{
	int pinA;
	int pinB;
	int portA;
	int portB;

	if(topBot == RGB_TOP)
	{
		portA = 3;
		portB = 2;
		pinA = 2;
		pinB = 3;
	}
	else if(topBot == RGB_BOT)
	{
		portA = 3;
		portB = 1;
		pinA = 1;
		pinB = 11;
	}
	switch(rgb)
	{
		case redLed:
			Chip_GPIO_WritePortBit(LPC_GPIO, portA, pinA, true);
			Chip_GPIO_WritePortBit(LPC_GPIO, portB, pinB, false);
			break;
		case greenLed:
			Chip_GPIO_WritePortBit(LPC_GPIO, portA, pinA, true);
			Chip_GPIO_WritePortBit(LPC_GPIO, portB, pinB, true);
			break;
		case blueLed:
			Chip_GPIO_WritePortBit(LPC_GPIO, portA, pinA, false);
			Chip_GPIO_WritePortBit(LPC_GPIO, portB, pinB, true);
			break;
		default:
			break;
	}
}

//Cycle RGB color
void RGBcycle(int speed, bool top, bool bot) {
	for(int i = 0; i < speed; i++){
		if(top) rgbLed(RGB_TOP, redLed);
		if(bot) rgbLed(RGB_BOT, redLed);
		Delay(100 - i/(speed/100));
		
		if(top) rgbLed(RGB_TOP, greenLed);
		if(bot) rgbLed(RGB_BOT, greenLed);
		Delay(i/ (speed / 100));
	}
	for (int i = 0; i < speed; i++){
		if(top) rgbLed(RGB_TOP, greenLed);
		if(bot) rgbLed(RGB_BOT, greenLed);
		Delay(100 - i / (speed / 100));

		if(top) rgbLed(RGB_TOP, blueLed);
		if(bot) rgbLed(RGB_BOT, blueLed);
		Delay(i / (speed / 100));
	}
	for(int i = 0; i < speed; i++){
		if(top) rgbLed(RGB_TOP, blueLed);
		if(bot) rgbLed(RGB_BOT, blueLed);
		Delay(100 - i/ (speed / 100));
		
		if(top) rgbLed(RGB_TOP, redLed);
		if(bot) rgbLed(RGB_BOT, redLed);
		Delay(i/ (speed / 100));
	}
}

//Initialize the HUD
void ledInit()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, false);	//DataLow
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, false);	//DataLowBat
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, false);	//DataLowDNR

	//Flush shift registers
	for(int i = 0; i < 16; i++)
	{
		Tick();
		TickBat();
		TickDNR();
	}
}

//Set the HUD as a clock
void clockDemo(int CLKTIME, int batPWM, int segPWM, int dnrPWM)
{
	bool decimal = true;
	bool ms = decimal;
	int counter = 1;
	int number = 0;
	int limit = 59;
	char DNRcount = '0';
	PWMUpdate(0, batPWM);	//BATPWM

	for(;;)
	{
		rgbLed(RGB_TOP, number % 3);
		rgbLed(RGB_BOT, (number + 1) % 3);
		if(decimal)
		{
			if(number == 99 && ms)
			{
				number = 10;
				ms = false;
			}

			if(number < 99 && ms)
			{
				sevenSeg(ms, number, segPWM);
				Delay(CLKTIME / 10);
			}
			else
			{
				ms = false;
				sevenSeg(ms, number, segPWM);
				Delay(CLKTIME);
			}
		}
		else
		{
			sevenSeg(false, number, segPWM);
			Delay(CLKTIME);
		}


		if(number == limit && counter == 0)
		{
			DNR(DNRcount, dnrPWM);
			DNRcount++;
			if(DNRcount == 58)
				DNRcount = 65;
			else if(DNRcount == 91)
				DNRcount = 97;
			else if(DNRcount == 123)
				DNRcount = 48;
		}
		if(number == limit && !ms)
		{
			BatClock(counter);
			counter++;
		}
		if(counter > 10)
		{
			counter = 0;
		}
		if(DNRcount == 25)
		{
			DNRcount = 0;
		}
		number++;
		if(number > limit && !ms)
		{
			number = 0;
			ms = true;
		}

		msg_obj.msgobj = 0;
		msg_obj.mode_id = BROADCAST_ADDRESS | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 3;
		msg_obj.data[0] = number;
		msg_obj.data[1] = counter;
		msg_obj.data[2] = DNRcount;
		LPC_CCAN_API->can_transmit(&msg_obj);
	}
}

int main()
{
	CAN_init();

	SystemCoreClockUpdate();
	//Enable and setup SysTick Timer at 1/1000 seconds (1ms)
	SysTick_Config(SystemCoreClock / 1000);

	//Enable timer 0,1,2,3 clock 
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
	Chip_TIMER_PrescaleSet(LPC_TIMER16_0, (PWM_PRESCALER - 1));
	Chip_TIMER_PrescaleSet(LPC_TIMER16_1, (PWM_PRESCALER - 1));
	//Set duty cycle - MR0 default
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER32_1, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER16_1, 0, PWM_DC_COUNT(0));
	//Enable interupt on MR0 & MR1
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 1);
	//MR0 should not stop or clear the timer
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_0, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_1, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_0, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_1, 0);
	//Set period - MR1
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 1, PWM_PERIOD_COUNT);
	Chip_TIMER_SetMatch(LPC_TIMER32_1, 1, PWM_PERIOD_COUNT);
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 1, PWM_PERIOD_COUNT);
	Chip_TIMER_SetMatch(LPC_TIMER16_1, 1, PWM_PERIOD_COUNT);
	//MR1 should reset the timer to restart the cycle
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_0, 1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_1, 1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_0, 1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_1, 1);
	//Enable the timers
	Chip_TIMER_Enable(LPC_TIMER32_0);
	Chip_TIMER_Enable(LPC_TIMER32_1);
	Chip_TIMER_Enable(LPC_TIMER16_0);
	//Chip_TIMER_Enable(LPC_TIMER16_1);

	((LPC_TIMER_T *)LPC_TIMER32_0)->PWMC = 1;// PWM mode enabled on CT32B0_MAT0
	((LPC_TIMER_T *)LPC_TIMER32_1)->PWMC = 1;// PWM mode enabled on CT32B1_MAT0
	((LPC_TIMER_T *)LPC_TIMER16_0)->PWMC = 1;// PWM mode enabled on CT16B0_MAT0
	((LPC_TIMER_T *)LPC_TIMER16_1)->PWMC = 1;// PWM mode enabled on CT16B1_MAT0	

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_ClearPendingIRQ(TIMER_32_1_IRQn);
	NVIC_ClearPendingIRQ(TIMER_16_0_IRQn);
	NVIC_ClearPendingIRQ(TIMER_16_1_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_1_IRQn);
	NVIC_EnableIRQ(TIMER_16_0_IRQn);
	NVIC_EnableIRQ(TIMER_16_1_IRQn);

	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7 | 1 << 8 | 1 << 9);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 7 | 1 << 8 | 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 3, 1 << 1 | 1 << 2 | 1 << 3);

	//LED's off
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, 0);

	//Output enable 7 Seg
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 0);

	//Output enable Bat
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);

	//Output enable DNR
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, 0);

	//RGB LEDS
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 0);

	ledInit();

	clockDemo(1000, 10, 10, 10);
	
	return 0;
}
