/*
 ===============================================================================
 Name        : EM4_CAN_OUT.c
 Author      : Nephtaly Aniceta
 Version     :
 Copyright   : -
 Description : Main CAN OUT Function
	Inspired by work from previous years.
	Rewritten for Visual Studio and LPCOpen v2.xx
 ===============================================================================
 */

#include <chip.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_NR			0x003
#if DEVICE_NR == 0x002 || DEVICE_NR == 0x003
	#define FRONT_ADDRESS 		0x002
#endif
#if DEVICE_NR == 0x004 || DEVICE_NR == 0x005
	#define REAR_ADDRESS		0x003
#endif
#if DEVICE_NR == 0x002 || DEVICE_NR == 0x004
	#define LEFT_ADDRESS		0x004
#endif
#if DEVICE_NR == 0x003 || DEVICE_NR == 0x005
	#define RIGHT_ADDRESS		0x005
#endif
#define ALL_ADDRESS				0x006
#if DEVICE_NR == 0x002 || DEVICE_NR == 0x003 || DEVICE_NR == 0x004 || DEVICE_NR == 0x005
	#define DIM_ADDRESS			0x007 //Light Controll Devices
#endif
#define BROADCAST_ADDRESS	0x101


#if DEVICE_NR == 0x002
	#define PERSONAL_ADDRESS	0x012
#elif DEVICE_NR == 0x003
	#define PERSONAL_ADDRESS	0x013
#elif DEVICE_NR == 0x004
	#define PERSONAL_ADDRESS	0x014
#elif DEVICE_NR == 0x005
	#define PERSONAL_ADDRESS	0x015
#endif

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

bool ready	= false;

CCAN_MSG_OBJ_T msg_obj;

void SysTick_Handler(void)
{
	SysTickCnt++;
}

void Delay(unsigned long tick)
{
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

/* Callback function prototypes */
void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);

void setPort(int port, bool onoff);


void CAN_init() {
	/* Publish CAN Callback Functions */
	CCAN_CALLBACKS_T callbacks = { CAN_rx, CAN_tx, CAN_error, NULL, NULL, NULL,
	NULL,
	NULL, };
	
	/* Initialize CAN Controller */
	uint32_t CanApiClkInitTable[2] = {
		0x00000000UL,	// CANCLKDIV
		0x00004DC5UL	// CAN_BTR
	};
	LPC_CCAN_API->init_can(&CanApiClkInitTable[0], TRUE);
	/* Configure the CAN callback functions */
	LPC_CCAN_API->config_calb(&callbacks);


#ifdef FRONT_ADDRESS
	msg_obj.msgobj = 1;
	msg_obj.mode_id = FRONT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
#endif
#ifdef REAR_ADDRESS
	msg_obj.msgobj = 1;
	msg_obj.mode_id = REAR_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
#endif
#ifdef LEFT_ADDRESS
	msg_obj.msgobj = 2;
	msg_obj.mode_id = LEFT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
#endif
#ifdef RIGHT_ADDRESS
	msg_obj.msgobj = 2;
	msg_obj.mode_id = RIGHT_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
#endif

	//all devices
	msg_obj.msgobj = 3;
	msg_obj.mode_id = ALL_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	//all devices
	msg_obj.msgobj = 4;
	msg_obj.mode_id = PERSONAL_ADDRESS;
	msg_obj.mask = 0x018;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);


#ifdef DIM_ADDRESS
	msg_obj.msgobj = 5;
	msg_obj.mode_id = DIM_ADDRESS;
	msg_obj.mask = 0xFFF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);
#endif


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
	if (msg_obj.msgobj == 1 || msg_obj.msgobj == 2 || msg_obj.msgobj == 3
			|| msg_obj.msgobj == 4 || msg_obj.msgobj == 5)
	{
		LPC_CCAN_API->can_receive(&msg_obj);

#ifdef FRONT_ADDRESS
		//both front devices
		if (msg_obj.msgobj == 1)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
			setPort(2, msg_obj.data[2]);
		}
#endif
#ifdef REAR_ADDRESS
		//both rear devices
		if (msg_obj.msgobj == 1)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
			setPort(2, msg_obj.data[2]);
		}
#endif
#ifdef LEFT_ADDRESS
		//both left devices
		if (msg_obj.msgobj == 2)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
			setPort(1, msg_obj.data[1]);
		}
#endif
#ifdef RIGHT_ADDRESS
		//both right devices
		if (msg_obj.msgobj == 2)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
			setPort(1, msg_obj.data[1]);
		}
#endif

#ifdef DIM_ADDRESS
		if (msg_obj.msgobj == 5)
		{
			setPort(2, msg_obj.data[2]);
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
		}
#endif

		//all devices
		if (msg_obj.msgobj == 3)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
			//setPort(0, msg_obj.data[0]);
			setPort(1, msg_obj.data[1]);
			setPort(2, msg_obj.data[2]);
			setPort(3, msg_obj.data[3]);
			setPort(4, msg_obj.data[4]);
			setPort(5, msg_obj.data[5]);
		}

		//all devices
		if (msg_obj.msgobj == 4)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO,0,7,true); //led3
			setPort(0, 1);
			setPort(1, msg_obj.data[1]);
			setPort(2, msg_obj.data[2]);
			setPort(3, msg_obj.data[3]);
			setPort(4, msg_obj.data[4]);
			setPort(5, msg_obj.data[5]);
		}
	}
	NVIC_EnableIRQ(CAN_IRQn);
}


/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
 a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num){
	ready = true;
	return;
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
 an error has occured on the CAN bus */
void CAN_error(uint32_t error_info){
	if (error_info & CAN_ERROR_PASS) {
		CAN_init();

	} else if (error_info & CAN_ERROR_BOFF) {
		CAN_init();
	}
	else {
		CAN_init();
	}
	return;
}

void setPort(int port, bool onoff){
	if(port == 0) Chip_GPIO_WritePortBit(LPC_GPIO,2,7,onoff);
	if(port == 1) Chip_GPIO_WritePortBit(LPC_GPIO,2,8,onoff);
	if(port == 2) Chip_GPIO_WritePortBit(LPC_GPIO,2,1,onoff);
	if(port == 3) Chip_GPIO_WritePortBit(LPC_GPIO,0,3,onoff);
	if(port == 4) Chip_GPIO_WritePortBit(LPC_GPIO,1,5,onoff);
	if(port == 5) Chip_GPIO_WritePortBit(LPC_GPIO,0,5,onoff);
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

int main(void){

	CAN_init();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	
	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 3 | 1 << 4 | 1 << 5);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 2, 1 << 1 | 1 << 7 | 1 << 8);
	
	bool ledOn = true;
	setPort(0,true);

	if (!(SysTickCnt % 10000))
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);		//led3

		msg_obj.msgobj = 0;
		msg_obj.mode_id = (0x100 + DEVICE_NR) | CAN_MSGOBJ_STD;
		msg_obj.mask = 0x0;
		msg_obj.dlc = 1;
		msg_obj.data[0] = DEVICE_NR;
		ready = false;
		LPC_CCAN_API->can_transmit(&msg_obj);

		if(ledOn == 1){
			ledOn = false;
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, true);	//led 3
			Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, false);	//led 2
			Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, false);	//led ?
		}
		else {
			ledOn = true;
			Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, false);	//led3
			Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, true);	//led2
			Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, true);	//led3
		}
	}
	return 0;
}
