/*
===============================================================================
Name        : EM4_HUD_CAN.c
Author      : Daniel van der Klooster & Nephtaly Aniceta
Version     : 0.7
Copyright   : GPLv3
Description : Main HUD Function
Controls the HUD of EM-04
===============================================================================
*/

#include <chip.h>

#define DEVICE_NR			0b1001
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

#define NFC_ADDRESS			0x5ca
#define NFC_NEPHTALY		0x0476280ada328000
#define NFC_LINDSEY			0x047b5a02da328000
#define NFC_ROEL			0x04213d929e318000
#define NFC_THOM			0x046d89929e318000
#define NFC_DANIEL			0x047c7a72f93b8000
#define NFC_QUINTEN			0xdeadbeefb00b1355
#define NFC_LOES			0x044d6d0a07348000


#define	ALL_MESSAGE			1
#define	PERSNOAL_MESSAGE	2
#define	SPEED_MESSAGE		3
#define BATTERY_MESSAGE		4
#define WARNING_MESSAGE		5
#define DIMMER_MESSAGE		6
#define TEMPERATURE_MESSAGE	7
#define	NFC_MESSAGE			8
#define	LEFT_MESSAGE		10
#define	RIGHT_MESSAGE		11
#define LIGHT_MESSAGE		12
#define FRONT_MESSAGE		13
#define	TOTAL_MESSAGE		14

#define RGB_TOP 1
#define RGB_BOT 0

// To have the timer tick run at 100,000 Hz, the prescaler is SYSTEM CLOCK / 100,000
#define PWM_FREQ_RESHZ (100000)//Divider to system clock to get PWM prescale value
#define PWM_PRESCALER ((unsigned long)SystemCoreClock / (unsigned long)PWM_FREQ_RESHZ)

#define PWM_PERIOD_HZ (200)
#define PWM_PERIOD_COUNT (PWM_FREQ_RESHZ / PWM_PERIOD_HZ)
#define PWM_DC_COUNT(a) ( (((101-a) * PWM_PERIOD_COUNT) / 100) )

#define CHECK_BIT(var,pos) ((var) & (1 << (pos)))

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

int HUDdimmer = 0;
bool CLOCK_DEMO = false;
bool CLOCK_MIRROR = false;

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

/**
* @brief	Updated the PWM dutycycle
* @return	Nothing
*/
void PWMUpdate(int pwm, unsigned char ucPercent)
{
	//set match register that control duty cycle
	switch(pwm)
	{
		//Battery + RGBcolor (top)
		case 0:
			Chip_TIMER_SetMatch(LPC_TIMER32_0, 0, PWM_DC_COUNT(ucPercent));
			break;
		//DNR
		case 1:
			Chip_TIMER_SetMatch(LPC_TIMER32_1, 0, PWM_DC_COUNT(ucPercent));
			break;
		//RGB
		case 2:
			Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, PWM_DC_COUNT(ucPercent));
			break;
		//7seg + RGBcolor(bot)
		case 3:
			Chip_TIMER_SetMatch(LPC_TIMER16_1, 0, PWM_DC_COUNT(ucPercent));
			break;
		default:
			break;
	}
}

/**
* @brief	Handle interrupt from 32-bit timer (Battery + RGBcolor_top)
* @return	Nothing
*/
void TIMER32_0_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 7, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 7, false);
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, false);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, false);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 1);
	}
	if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 2))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 2);
	}
	if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 3))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 3);
	}
}

/**
* @brief	Handle interrupt from 32-bit timer (DNR)
* @return	Nothing
*/
void TIMER32_1_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_1, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 1, true);
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER32_1, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 1, false);
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 1);
	}
}

/**
* @brief	Handle interrupt from 32-bit timer (7Seg + DNRcolor_bot)
* @return	Nothing
*/
void TIMER16_0_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER16_0, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, true);
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);
	}
	else if(Chip_TIMER_MatchPending(LPC_TIMER16_0, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, false);
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 1);
	}
}

/**
* @brief	Handle interrupt from 32-bit timer (RGB)
* @return	Nothing
*/
void TIMER16_1_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER16_1, 0))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, true);
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, 0);
	}
	if(Chip_TIMER_MatchPending(LPC_TIMER16_1, 1))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, false);
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, false);
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, false);
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, 1);
	}
	if(Chip_TIMER_MatchPending(LPC_TIMER16_1, 2))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, true);
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, 2);
	}
	if(Chip_TIMER_MatchPending(LPC_TIMER16_1, 3))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, true);
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, 3);
	}
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

	msg_obj.msgobj = DIMMER_MESSAGE;
	msg_obj.mode_id = DIMMER_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = SPEED_MESSAGE;
	msg_obj.mode_id = SPEED_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = WARNING_MESSAGE;
	msg_obj.mode_id = WARNING_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = TEMPERATURE_MESSAGE;
	msg_obj.mode_id = TEMPERATURE_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = PERSNOAL_MESSAGE;
	msg_obj.mode_id = DEVICE_NR;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = NFC_MESSAGE;
	msg_obj.mode_id = NFC_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = LEFT_MESSAGE;
	msg_obj.mode_id = LEFT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = RIGHT_MESSAGE;
	msg_obj.mode_id = RIGHT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = LIGHT_MESSAGE;
	msg_obj.mode_id = LIGHT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = FRONT_MESSAGE;
	msg_obj.mode_id = FRONT_ADDRESS;
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
		if(msg_obj_num == WARNING_MESSAGE)
		{
			// led t1(red)
			Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, msg_obj.data[0]);
		}
		if(msg_obj_num == DIMMER_MESSAGE)
		{
			HUDdimmer = msg_obj.data[0];
			PWMUpdate(0, HUDdimmer);	//BATPWM
			PWMUpdate(1, HUDdimmer);	//7SEGPWM
			PWMUpdate(2, HUDdimmer);	//DNRPWM
			PWMUpdate(3, HUDdimmer);	//RGBPWM
		}
		if(msg_obj_num == TEMPERATURE_MESSAGE && !CLOCK_DEMO)
		{
			rgbLed(RGB_BOT, msg_obj.data[0]);

		}
		if(msg_obj_num == PERSNOAL_MESSAGE)
		{
			// CLOCK_DEMO_CONTROLL
			if(msg_obj.data[0] == 0xdd)
			{
				CLOCK_DEMO = true;
				CLOCK_MIRROR = msg_obj.data[1];
			}
			else if(msg_obj.data[0] == 0xff)
			{
				CLOCK_DEMO = false;
				sevenSeg(msg_obj.data[2], msg_obj.data[1], msg_obj.data[3]);
				DNR(msg_obj.data[4], msg_obj.data[3]);
				BatClock(msg_obj.data[5]);
			}

			// led t2(green)
			if(msg_obj.data[0] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, false);
			else if(msg_obj.data[0] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, true);

			//led t3(red)
			if(msg_obj.data[1] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);
			else if(msg_obj.data[1] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);

			//led t4(red)
			if(msg_obj.data[2] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 0, false);
			else if(msg_obj.data[2] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 0, true);
	
			//led t5(green)
			if(msg_obj.data[3] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 1, false);
			else if(msg_obj.data[3] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 1, true);

			//led t6(green)
			if(msg_obj.data[4] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 2, false);
			else if(msg_obj.data[4] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 2, true);
			
			//led t7(blue)
			if(msg_obj.data[5] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 0, false);
			else if(msg_obj.data[5] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 0, true);

			//led t8(blue)
			if(msg_obj.data[6] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 6, false);
			else if(msg_obj.data[6] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 6, true);

			//led t9(green)
			if(msg_obj.data[7] == 10)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, false);
			else if(msg_obj.data[7] == 11)
				Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, true);
		}
		if(msg_obj_num == NFC_MESSAGE)
		{
			uint8_t id[8] = { msg_obj.data[7], msg_obj.data[6], msg_obj.data[5], msg_obj.data[4], msg_obj.data[3], msg_obj.data[2], msg_obj.data[1],msg_obj.data[0] };
			uint64_t totalID = 0;
			memcpy(&totalID, &id, 8 * sizeof(uint8_t));

			if(totalID == NFC_NEPHTALY)
			{
				rgbLed(RGB_TOP, 100);
			}
			if(totalID == NFC_THOM)
			{
				rgbLed(RGB_TOP, 75);
			}
			if(totalID == NFC_DANIEL)
			{
				rgbLed(RGB_TOP, 28);
			}
			if(totalID == NFC_LINDSEY)
			{
				rgbLed(RGB_TOP, 0);
			}
			if(totalID == NFC_ROEL)
			{
				rgbLed(RGB_TOP, 12);
			}
			if(totalID == NFC_QUINTEN)
			{
				rgbLed(RGB_TOP, 50);
			}
			if(totalID == NFC_LOES)
			{
				rgbLed(RGB_TOP, 59);
			}
		}
		if(msg_obj_num == RIGHT_MESSAGE)
		{
			//led t9(green)
			Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, msg_obj.data[0]);
		}
		if(msg_obj_num == LEFT_MESSAGE)
		{
			//led t2(green)
			Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, msg_obj.data[0]);
		}
		if(msg_obj_num == LIGHT_MESSAGE)
		{
			//niks
		}
		if(msg_obj_num == FRONT_MESSAGE)
		{
			//led t5(green) (city)
			Chip_GPIO_WritePortBit(LPC_GPIO, 1, 1, msg_obj.data[0]);
			//led t6(green) (dim)
			Chip_GPIO_WritePortBit(LPC_GPIO, 1, 2, msg_obj.data[1]);
			//led t7(blue) (full)
			Chip_GPIO_WritePortBit(LPC_GPIO, 3, 0, msg_obj.data[3]);
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
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, true); //led 2 (red)
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
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, true);
}

void DataLowBat() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, false);
}

void Strobef() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 9, false);	//7Seg
}

void StrobefBat(){
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, false);	//Bat
}

void StrobefDNR() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 8, false);	//Bat
}

//7-seg sub function
void sevenSegNumber(int number, bool dotOn, bool mirror) {
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
	
	if(mirror)
	{
		unsigned long long mask = 0b00000000;
		if((CHECK_BIT(value, 1) == 0) ^ (CHECK_BIT(value, 5) == 0))
			mask |= 0b00100010;
		if((CHECK_BIT(value, 2) == 0) ^ (CHECK_BIT(value, 4) == 0))
			mask |= 0b00010100;
		value ^= mask; //mirrored bits
	}

	if(dotOn)
		value |= 0b10000000; //turn on the dot

	for(int i = 0; i < 8; i++)
	{
		unsigned long long bit = value & 0b10000000;
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, bit); //write data
		Tick();
		value <<= 1;
	}
	
}

//7-seg function
void sevenSeg(bool dotOn, int number, bool mirror)
{
	if(dotOn)
	{
		if(mirror)
		{
			sevenSegNumber(number % 10, true, mirror);
			sevenSegNumber(number / 10, false, mirror);
		}
		else
		{
			sevenSegNumber(number / 10, true, mirror);
			sevenSegNumber(number % 10, false, mirror);
		}
		Strobef();
	}
	else
	{
		if(mirror)
		{
			sevenSegNumber(number % 10, false, mirror);
			sevenSegNumber(number / 10, false, mirror);
		}
		else
		{
			sevenSegNumber(number / 10, false, mirror);
			sevenSegNumber(number % 10, false, mirror);
		}
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
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, true);
				Delay(1);
			}
			else {
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, false);
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
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, true);
				Delay(1);
			}
			else {
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, false);
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
void DNR(char ch, bool mirror)
{
	unsigned long long value;
	switch(ch)
	{
		case 'A':
			value = 0b0000001111101101;
			break;
		case 'a':
			value = 0b1001100110000000;
			break;
		case 'B':
			value = 0b0011111001001101;
			break;
		case 'b':
			value = 0b0001100110100000;
			break;
		case 'C':
			value = 0b0011000100101100;
			break;
		case 'c':
			value = 0b0001000110000000;
			break;
		case 'D':
			value = 0b0011111001001100;
			break;
		case 'd':
			value = 0b0001110110000000;
			break;
		case 'E':
			value = 0b0011000110101100;
			break;
		case 'e':
			value = 0b0111000110000000;
			break;
		case 'F':
			value = 0b0000000110101100;
			break;
		case 'f':
			value = 0b0000110010001001;
			break;
		case 'G':
			value = 0b0011001100101101;
			break;
		case 'g':
			value = 0b0001110010100100;
			break;
		case 'H':
			value = 0b0000001111100001;
			break;
		case 'h':
			value = 0b0000100110100000;
			break;
		case 'I':
			value = 0b0011110000001100;
			break;
		case 'i':
			value = 0b0000100000000000;
			break;
		case 'J':
			value = 0b0011001101000000;
			break;
		case 'j':
			value = 0b0001110100000000;
			break;
		case 'K':
			value = 0b1000000110100010;
			break;
		case 'k':
			value = 0b1000110000000010;
			break;
		case 'L':
			value = 0b0011000100100000;
			break;
		case 'l':
			value = 0b0010110000000000;
			break;
		case 'M':
			value = 0b0000001101110010;
			break;
		case 'm':
			value = 0b0000101110000001;
			break;
		case 'N':
			value = 0b1000001101110000;
			break;
		case 'n':
			value = 0b0000100110000000;
			break;
		case 'O':
			value = 0b0011001101101100;
			break;
		case 'o':
			value = 0b0001100110000000;
			break;
		case 'P':
			value = 0b0000000111101101;
			break;
		case 'p':
			value = 0b0000010110100100;
			break;
		case 'Q':
			value = 0b1011001101101100;
			break;
		case 'q':
			value = 0b0000110010100100;
			break;
		case 'R':
			value = 0b1000000111101101;
			break;
		case 'r':
			value = 0b0000000110000000;
			break;
		case 'S':
			value = 0b0011001010101101;
			break;
		case 's':
			value = 0b0001100010100100;
			break;
		case 'T':
			value = 0b0000110000001100;
			break;
		case 't':
			value = 0b0001110010000001;
			break;
		case 'U':
			value = 0b0011001101100000;
			break;
		case 'u':
			value = 0b0001100100000000;
			break;
		case 'V':
			value = 0b0100000100100010;
			break;
		case 'v':
			value = 0b0100000100000000;
			break;
		case 'W':
			value = 0b1100001101100000;
			break;
		case 'w':
			value = 0b1100001100000000;
			break;
		case 'X':
			value = 0b1100000000010010;
			break;
		case 'x':
			value = 0b1100000000010010;
			break;
		case 'Y':
			value = 0b0000100011100001;
			break;
		case 'y':
			value = 0b0000100000010010;
			break;
		case 'Z':
			value = 0b0111000000001110;
			break;
		case 'z':
			value = 0b0101000010000000;
			break;
		case '0':
			value = 0b0011001101101100;
			break;
		case '1':
			value = 0b0000001001000010;
			break;
		case '2':
			value = 0b0011000111001101;
			break;
		case '3':
			value = 0b0011001001001101;
			break;
		case '4':
			value = 0b0000001011100001;
			break;
		case '5':
			value = 0b0011001010101101;
			break;
		case '6':
			value = 0b0011001110101101;
			break;
		case '7':
			value = 0b0000001001001100;
			break;
		case '8':
			value = 0b0011001111101101;
			break;
		case '9':
			value = 0b0011001011101101;
			break;
		default:
			value = NULL;
			break;
	}

	if(mirror)
	{
		unsigned long long mask = 0b0000000000000000;

		if((CHECK_BIT(value, 12) == 0) ^ (CHECK_BIT(value, 13) == 0))
			mask |= 0b0011000000000000;
		if((CHECK_BIT(value, 8) == 0) ^ (CHECK_BIT(value, 9) == 0))
			mask |= 0b0000001100000000;
		if((CHECK_BIT(value, 14) == 0) ^ (CHECK_BIT(value, 15) == 0))
			mask |= 0b1100000000000000;
		if((CHECK_BIT(value, 7) == 0) ^ (CHECK_BIT(value, 0) == 0))
			mask |= 0b0000000010000001;
		if((CHECK_BIT(value, 5) == 0) ^ (CHECK_BIT(value, 6) == 0))
			mask |= 0b0000000001100000;
		if((CHECK_BIT(value, 4) == 0) ^ (CHECK_BIT(value, 1) == 0))
			mask |= 0b0000000000010010;
		if((CHECK_BIT(value, 2) == 0) ^ (CHECK_BIT(value, 3) == 0))
			mask |= 0b0000000000001100;

		value ^= mask; //mirrored bits
	}
	for(int i = 0; i < 16; i++)
	{
		unsigned long long bit = value & 1;
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, bit); //data to write
		TickDNR();
		value >>= 1;
	}
	StrobefDNR();
}

//Set RGBLeds
void rgbLed(bool topBot, int rgb)
{
	int rgbinv = 50 - (rgb - 51);
	if(topBot == RGB_TOP)
	{
		if(rgb <= 50)
		{
			Chip_TIMER_SetMatch(LPC_TIMER32_0, 2, PWM_DC_COUNT(100));
			Chip_TIMER_SetMatch(LPC_TIMER32_0, 3, PWM_DC_COUNT(rgb * 2));
		}
		else
		{
			Chip_TIMER_SetMatch(LPC_TIMER32_0, 2, PWM_DC_COUNT((rgbinv) * 2));
			Chip_TIMER_SetMatch(LPC_TIMER32_0, 3, PWM_DC_COUNT(100));
		}
	}
	else if(topBot == RGB_BOT)
	{
		if(rgb <= 50)
		{
			Chip_TIMER_SetMatch(LPC_TIMER16_1, 2, PWM_DC_COUNT(100));
			Chip_TIMER_SetMatch(LPC_TIMER16_1, 3, PWM_DC_COUNT(rgb * 2));
		}
		else
		{
			Chip_TIMER_SetMatch(LPC_TIMER16_1, 2, PWM_DC_COUNT((rgbinv) * 2));
			Chip_TIMER_SetMatch(LPC_TIMER16_1, 3, PWM_DC_COUNT(100));
		}
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
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, false);	//DataLowBat
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, false);	//DataLowDNR

	//Flush shift registers
	for(int i = 0; i < 17; i++)
	{
		Tick();
		TickBat();
		TickDNR();
	}
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//Set the HUD as a clock
void clockDemo(int CLKTIME, int batPWM, int segPWM, int dnrPWM, int rgbPWM, bool mirror)
{
	CLOCK_DEMO = true;
	CLOCK_MIRROR = mirror;
	bool decimal = true;
	bool ms = decimal;
	int counter = 1;
	int number = 0;
	int limit = 59;
	char DNRcount = '0';
	bool bug = false;
	ledInit();
	PWMUpdate(0, batPWM);	//BATPWM
	PWMUpdate(2, rgbPWM);	//RGBPWM


	while(CLOCK_DEMO)
	{
		if(ms)
		{
			rgbLed(RGB_BOT, number);
			rgbLed(RGB_TOP, number);
		}
		else
		{
			rgbLed(RGB_BOT, map(number, 0, limit, 0, 100));
			rgbLed(RGB_TOP, map(number, 0, limit, 0, 100));
		}
		if(decimal)
		{
			if(number == 99 && ms)
			{
				number = 10;
				ms = false;
			}

			if(number < 99 && ms)
			{
				sevenSeg(ms, number, mirror);
				Delay(CLKTIME / 10);
			}
			else
			{
				ms = false;
				sevenSeg(ms, number, mirror);
				Delay(CLKTIME);
			}
		}
		else
		{
			sevenSeg(false, number, mirror);
			Delay(CLKTIME);
		}


		if(number == limit && counter == 0 && !ms)
		{
			DNR(DNRcount, mirror);
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
		msg_obj.mode_id = (CLOCK_ADDRES) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 3;
		msg_obj.data[0] = (int)(number / 10) * 6 + number;
		msg_obj.data[1] = (int)(counter / 10) * 6 + counter;
		msg_obj.data[2] = (int)(DNRcount / 10) * 6 + DNRcount;
		LPC_CCAN_API->can_transmit(&msg_obj);
	}
}

int main()
{
	CAN_init();

	SystemCoreClockUpdate();
	//Enable and setup SysTick Timer at 1/1000 seconds (1ms)
	SysTick_Config(SystemCoreClock / 1000);
	unsigned long lastSystickcnt = 0;

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
	Chip_TIMER_PrescaleSet(LPC_TIMER16_0, (PWM_PRESCALER - 1)/10); //takes controll of the RGB PWM 10x resolution of the normal PWM
	Chip_TIMER_PrescaleSet(LPC_TIMER16_1, (PWM_PRESCALER - 1));
	//Set duty cycle - MR0 default
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER32_1, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER16_1, 0, PWM_DC_COUNT(0));
	//Enable interupt on MR0 & MR1
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 2);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 3);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 2);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 3);
	//MR0 should not stop or clear the timer
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_0, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_0, 2);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_0, 3);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER32_1, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_0, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_1, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_1, 2);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER16_1, 3);
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
	Chip_TIMER_Enable(LPC_TIMER16_1);

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

	//Configure pins to GPIO (See doc talbe Table 163. p159 for which function) (these are the only pins that are not configured automaticly to GPIO )
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO1_1, IOCON_MODE_PULLUP, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO1_2, IOCON_MODE_PULLUP, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO0_11, IOCON_MODE_PULLUP, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO1_0, IOCON_MODE_PULLUP, IOCON_FUNC1);

	//setup GPIO to Output
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 1 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 11);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 6 | 1 << 7  | 1 << 8 | 1 << 10 | 1 << 11);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 3, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	

	//LED's off
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 0, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 1, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 2, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 0, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 6, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, false);

	//Output enable 7 Seg low
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, false);

	//Output enable Bat low
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 7, false);

	//Output enable DNR low
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 1, false);

	//RGB LEDS low
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, false);	//pwm low

	ledInit();
	
	clockDemo(1000, 10, 20, 8, 10, false);
	//Will not execute when clockDemo is runned
	for(;;)
	{	
		if(CLOCK_DEMO)
			clockDemo(1000, 10, 20, 8, 10, CLOCK_MIRROR);
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

//Color loop
/*
if(((SysTickCnt - loopSystickcnt) >= 100))
{
loopSystickcnt = SysTickCnt;
Chip_TIMER_SetMatch(LPC_TIMER16_1, 2, PWM_DC_COUNT(100));
Chip_TIMER_SetMatch(LPC_TIMER16_1, 3, PWM_DC_COUNT(i));
int test = PWM_DC_COUNT(100);
if(UP)
i++;
else
i--;

if(i > 100 || i < 0)
UP = !UP;
}*/


/*
Led pins:
-------------
led b1 (green)	power light
led b2 (blue)	0,7
led t1 (red)	1,10
led t2 (green)	2,11
led t3 (red)	0,11
led t4 (red)	1,0
led t5 (green)	1,1
led t6 (green)	1,2
led t7 (blue)	3,0
led t8 (blue)	2,6
led t9 (green)	1,8

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

