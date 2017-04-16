/*
===============================================================================
 Name        : EM4_MOTOR_CONTROLLER.c
 Author      : Daniël van der Klooster & Nephtaly Aniceta
 Version     : -
 Copyright   : GPLv3
 Description : Main CAN IN Function
				Motorcontroller for EM-04
				Uses CANBUS to receive msg and forwards it to the Atmega by
				setting pins
===============================================================================
*/

#include <chip.h>
#include <string.h>

#define DEVICE_NR			0b1110
#define	EM_04_CAN_RANGE		0x100

#define ALL_ADDRESS			(0x000 + EM_04_CAN_RANGE)
#define FAN_ADDRESS			(0x010 + EM_04_CAN_RANGE)
#define COUT_ADDRESS		(0x020 + EM_04_CAN_RANGE)
#define LIGHT_ADDRESS			(0x001 + COUT_ADDRESS)
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
#define BROADCAST_ADDRESS	(0x050 + EM_04_CAN_RANGE)

#define NFC_ADDRESS			0x5ca

#define	ALL_MESSAGE			1
#define	PERSNOAL_MESSAGE	2
#define	MOTOR1_MESSAGE		3
#define	MOTOR2_MESSAGE		4
#define	TOTAL_MESSAGE		5

#define DEFAULT_I2C          I2C0

#define SPEED_100KHZ         100000
#define SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    SPEED_100KHZ
#define I2C_FASTPLUS_BIT     0

/* Transmit and receive  buffer sizes */
#define I2C_SRB_SIZE 256

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

static int mode_poll;	/* Poll/Interrupt mode flag */
static I2C_ID_T i2cDev = DEFAULT_I2C;	/* Currently active I2C device */

/**
* @brief	Handle interrupt from SysTick timer
* @return	Nothing
*/
void SysTick_Handler(void)
{
	SysTickCnt++;
}

/**
* @brief	Handle interrupt from 32-bit timer
* @return	Nothing
*/
void TIMER32_0_IRQHandler(void)
{
	if(Chip_TIMER_MatchPending(LPC_TIMER32_0, 1))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led 4 (yellow)
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

static void Init_I2C_PinMux(void)
{
	Chip_SYSCTL_PeriphReset(RESET_I2C0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_4, IOCON_FUNC1 | I2C_FASTPLUS_BIT);
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_5, IOCON_FUNC1 | I2C_FASTPLUS_BIT);
}

/* Set I2C mode to polling/interrupt */
static void i2c_set_mode(I2C_ID_T id, int polling)
{
	if(!polling)
	{
		mode_poll &= ~(1 << id);
		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandler);
		NVIC_EnableIRQ(I2C0_IRQn);
	}
	else
	{
		mode_poll |= 1 << id;
		NVIC_DisableIRQ(I2C0_IRQn);
		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandlerPolling);
	}
}

/* State machine handler for I2C0 and I2C1 */
static void i2c_state_handling(I2C_ID_T id)
{
	if(Chip_I2C_IsMasterActive(id))
	{
		Chip_I2C_MasterStateHandler(id);
	}
	else
	{
		Chip_I2C_SlaveStateHandler(id);
	}
}

/* Initialize the I2C bus */
static void i2c_app_init(I2C_ID_T id, int speed)
{
	Init_I2C_PinMux();

	/* Initialize I2C */
	Chip_I2C_Init(id);
	Chip_I2C_SetClockRate(id, speed);

	/* Set default mode to interrupt */
	i2c_set_mode(id, 0);
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
* @brief	I2C Interrupt Handler
* @return	None
*/
void I2C_IRQHandler(void)
{
	i2c_state_handling(I2C0);
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

	msg_obj.msgobj = MOTOR1_MESSAGE;
	msg_obj.mode_id = MC_ADDRESS + 1;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	msg_obj.msgobj = MOTOR2_MESSAGE;
	msg_obj.mode_id = MC_ADDRESS + 2;
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
	NVIC_DisableIRQ(CAN_IRQn);
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;

	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if(msg_obj_num < TOTAL_MESSAGE || msg_obj_num > 0)
	{
		if(msg_obj_num == MOTOR1_MESSAGE)
		{
			if(msg_obj.data == true)
			{
				/* Transmit and receive buffers */
				static I2C_XFER_T xfer;
				static uint8_t tx[I2C_SRB_SIZE], rx[I2C_SRB_SIZE];

				tx[0] = 'S';
				tx[1] = 'T';
				tx[2] = 'A';
				tx[3] = 'R';
				tx[4] = 'T';

				xfer.slaveAddr = 5;
				xfer.txBuff = &tx[0];
				xfer.txSz = 2;
				Chip_I2C_MasterSend(i2cDev, xfer.slaveAddr, xfer.txBuff, xfer.txSz);
			}
		}

		if(msg_obj_num == MOTOR2_MESSAGE)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, msg_obj.data[0]);
		}

		// Turn on the yellow led and Enable timer interrupt
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//Yellow led
		NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
		NVIC_EnableIRQ(TIMER_32_0_IRQn);
	}
	NVIC_EnableIRQ(CAN_IRQn);
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//Yellow led
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
an error has occured on the CAN bus */
void CAN_error(uint32_t error_info)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);			//turn red LED on
}

int main()
{
	/* Transmit and receive buffers */
	static I2C_XFER_T xfer;
	static uint8_t tx[I2C_SRB_SIZE], rx[I2C_SRB_SIZE];

	CAN_init();

	SystemCoreClockUpdate();
	// and setup SysTick Timer at 1/1000 seconds (1ms)
	SysTick_Config(SystemCoreClock / 1000);

	//Setup I2C for the Arduino bitrate
	i2c_app_init(I2C0, I2C_DEFAULT_SPEED);

	/* Setup I2C parameters to send 4 bytes of data */
	tx[0] = 't';
	tx[1] = 'e';
	tx[2] = 'm';
	tx[3] = 'p';
	tx[4] = ':';
	tx[5] = ' ';
	tx[6] = '1';
	tx[7] = '8';
	tx[8] = '6';
	tx[9] = ' ';
	tx[10] = 'a';

	xfer.slaveAddr = 8;
	xfer.txBuff = &tx[0];
	xfer.txSz = 9;

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
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 7 | 1<<6);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 2 | 1<<10);

	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, 0);  //board red led off
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 0); //board yellow led off

	unsigned long lastSystickcnt = 0;
	unsigned long loopTickcnt = 0;
	int firstDigit = 0, secondDigit = 0, firstDecimal = 0, secondDecimal = 0, temperatureDecimalLead = 0, temperatureDecimalFollow = 0;
	int temperatureHexLead = 0, temperatureHexFollow = 0;

	for (;;)
	{
		if((SysTickCnt - loopTickcnt) >= 500)
		{
			loopTickcnt = SysTickCnt;
			xfer.rxBuff = &rx[0];
			xfer.rxSz = 11;
			Chip_I2C_MasterRead(i2cDev, xfer.slaveAddr, xfer.rxBuff, xfer.rxSz);

			firstDigit = rx[6] - '0';
			secondDigit = rx[7] - '0';
			firstDecimal = rx[9] - '0';

			if('0' < rx[10] < '9')
				secondDecimal = rx[10] - '0';
			else
				secondDecimal = 0;


			temperatureDecimalLead = firstDigit * 10 + secondDigit;
			temperatureDecimalFollow = firstDecimal * 10 + secondDecimal;

			temperatureHexLead = floor(temperatureDecimalLead/10) * 6 + temperatureDecimalLead;
			temperatureHexFollow = floor(temperatureDecimalFollow/10) * 6 + temperatureDecimalFollow;

			msg_obj.msgobj = 0;
			msg_obj.mode_id = MC_I2C | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 2;

			msg_obj.data[0] = temperatureHexLead;
			msg_obj.data[1] = temperatureHexFollow;
			LPC_CCAN_API->can_transmit(&msg_obj);
		}

		if((SysTickCnt - lastSystickcnt) >= 1000)
		{
			lastSystickcnt = SysTickCnt;

			msg_obj.msgobj = 0;
			msg_obj.mode_id = (BROADCAST_ADDRESS + DEVICE_NR) | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			msg_obj.data[0] = DEVICE_NR;
			LPC_CCAN_API->can_transmit(&msg_obj);
			
			Chip_I2C_MasterSend(i2cDev, xfer.slaveAddr, xfer.txBuff, xfer.txSz);

			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 7);				//Toggle blue led
		}
	}

	return 0;
}

/*
Ouput pins:
-------------
SDA 0,4
SDL	0,5

Led pins:
-------------
led 1 (green) power light
led 2 (red) 2,2
led 3 (yellow) 2,10
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
/**
int test = 0b1110;
*/