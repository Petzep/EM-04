/*
 ===============================================================================
 Name        : EM4_CAN_IN.c
 Author      : Nephtaly Aniceta
 Version     :
 Copyright   : -
 Description : Main CAN IN Function
	Inspired by work from previous years.
	Rewritten for Visual Studio and LPCOpen v2.xx
 ===============================================================================
 */

#include <chip.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_NR			0x001
#define LEFT_DEVICES		0x004
#define RIGHT_DEVICES		0x005
#define ALL_ADDRESS			0x006
#define DIM_ADDRESS			0x007
#define BROADCAST_ADDRESS	0x101

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

void SysTick_Handler(void){
	SysTickCnt++;
}

void Delay(unsigned long tick){
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
	
	/* Enable the CAN Interrupt */
	//NVIC_EnableIRQ(CAN_IRQn)
}

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
 a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num){
	//Nothing to receive
}


/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
 a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num) {
	ready = true;

	while(1) ready++; //WHY????

	return;
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
 an error has occured on the CAN bus */
void CAN_error(uint32_t error_info) {
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

int main(void) {

	CAN_init();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	
	//setup GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 0, 1 << 2 | 1 << 3);
	Chip_GPIO_SetPortDIRInput(LPC_GPIO, 2, 1 << 1 | 1 << 7 | 1 << 8);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 1, 1 << 2 | 1 << 10);
	
	bool blinkLeftOn =		false;
	bool blinkLeftState =	false;
	bool blinkRightOn =		false;
	bool blinkRightState =	false;

	bool lightsOn =			false;
	bool alarmOn =			false;
	bool wiperOn =			false;

	bool ledOn =			false;


	for (;;) //infinite loop
	{		
		bool blinkLeft = 	Chip_GPIO_ReadPortBit(LPC_GPIO, 0,3);
		bool blinkRight = 	Chip_GPIO_ReadPortBit(LPC_GPIO, 2,7);
		bool alarm = 		Chip_GPIO_ReadPortBit(LPC_GPIO, 2,8);
		bool lights = 		Chip_GPIO_ReadPortBit(LPC_GPIO, 0,2);
		bool wiper = 		Chip_GPIO_ReadPortBit(LPC_GPIO, 2,1);


		//////////////////////////////
		////////BUTTON HANDLER////////
		//////////////////////////////
		if (blinkLeft != blinkLeftOn)
		{
			blinkLeftOn = blinkLeft;	
		}

		if (blinkRight != blinkRightOn)
		{
			blinkRightOn = blinkRight;
		}	

		if(alarm != alarmOn)
		{
			blinkLeftOn = alarm;
			blinkRightOn = alarm;
			alarmOn = alarm;
		}

		if(lights != lightsOn)
		{
			lightsOn = lights;
			msg_obj.msgobj = 0;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 3;
			msg_obj.mode_id = DIM_ADDRESS | CAN_MSGOBJ_STD;
			msg_obj.data[0] = 0;
			msg_obj.data[1] = 0;
			msg_obj.data[2] = lightsOn;
			//note this address only responds to bits on data[2]

			Delay(1000);
			
			ready = false;
			LPC_CCAN_API->can_transmit(&msg_obj);
		}

		if(wiper != wiperOn)
		{
			wiperOn = wiper;
			msg_obj.msgobj = 0;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 5;
			msg_obj.mode_id = 0x0012 | CAN_MSGOBJ_STD;
			msg_obj.data[0] = 0;
			msg_obj.data[1] = 0;
			msg_obj.data[2] = 0;

			if(wiperOn)
			{
				//first disable reset
				/*
				msg_obj.data[3] = 0;
				msg_obj.data[4] = 0;
				int i = 0;
				while (i < 10000) {
					i++;
				}
				ready = 0;
				LPC_CCAN_API->can_transmit(&msg_obj);
*/
				//then set wiper on
				msg_obj.data[3] = 1;
				msg_obj.data[4] = 1;
				
				Delay(1000);
				
				ready = false;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			else 
			{
				/*
				//first set wiper off
				msg_obj.data[3] = 0;
				msg_obj.data[4] = 0;
				int i = 0;
				while (i < 10000) {
					i++;
				}
				ready = 0;
				LPC_CCAN_API->can_transmit(&msg_obj);
				*/

				//then enable reset
				msg_obj.data[3] = 0;
				msg_obj.data[4] = 1;

				Delay(1000);
				
				ready = false;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			//note, this address is the personal address of device 0x002 and reacts to only 000000011000

		}




		//////////////////////////////
		////////////TIMERS////////////
		//////////////////////////////
		//
		//Left Blink
		//
		if (!(SysTickCnt % 5000))
		{
			msg_obj.msgobj = 0;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 2;
			msg_obj.data[0] = 0;
			if(blinkLeftOn || alarmOn)
			{
				msg_obj.mode_id = LEFT_DEVICES | CAN_MSGOBJ_STD;
				if(!blinkLeftState)
				{
					blinkLeftState = true;
					msg_obj.data[1] = 1;
				}
				Delay(1000);
				ready = false;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
			else if(blinkLeftState)
			{
				blinkLeftState = 0;
				msg_obj.mode_id = LEFT_DEVICES | CAN_MSGOBJ_STD;
				msg_obj.data[1] = 0;
				Delay(1000);
				ready = false;
				LPC_CCAN_API->can_transmit(&msg_obj);
			}
		}

		if (!(SysTickCnt % 1000) && blinkLeftState) //on each second while blinkLeftState is true
		{
			msg_obj.msgobj = 0;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 2;
			msg_obj.data[0] = 0;
			msg_obj.data[1] = 0;
			msg_obj.mode_id = LEFT_DEVICES | CAN_MSGOBJ_STD;
			blinkLeftState = false;
			ready = false;
			Delay(1000);
			LPC_CCAN_API->can_transmit(&msg_obj);
		}

		//
		//Right Blink
		//
		if (!(SysTickCnt % 5000))
		{
			msg_obj.msgobj = 0;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 2;
			msg_obj.data[0] = 0;
			if(blinkRightOn || alarmOn)
			{
				msg_obj.mode_id = RIGHT_DEVICES | CAN_MSGOBJ_STD;
				if(!blinkRightState)
				{
					blinkRightState = true;
					msg_obj.data[1] = 1;
				}
				Delay(1000);
				ready = false;
				LPC_CCAN_API->can_transmit(&msg_obj);

			}
			else if(blinkRightState)
			{
				blinkRightState = false;
				msg_obj.mode_id = RIGHT_DEVICES | CAN_MSGOBJ_STD;
				msg_obj.data[1] = false;
				Delay(1000);
				ready = false;
				LPC_CCAN_API->can_transmit(&msg_obj);

			}
		}
		
		if (!(SysTickCnt % 1000) && blinkRightState)
		{
			msg_obj.msgobj = 0;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 2;
			msg_obj.data[0] = 0;
			msg_obj.data[1] = 0;
			msg_obj.mode_id = RIGHT_DEVICES | CAN_MSGOBJ_STD;
			blinkRightState = false;
			Delay(1000);
			ready = false;
			LPC_CCAN_API->can_transmit(&msg_obj);
		}

		//
		//heartbeat
		//
		if (!(SysTickCnt % 1000))
		{
			Delay(100);
			msg_obj.msgobj = 0;
			msg_obj.mode_id = BROADCAST_ADDRESS | CAN_MSGOBJ_STD;
			msg_obj.mask = 0x0;
			msg_obj.dlc = 1;
			msg_obj.data[0] = DEVICE_NR;
			ready = false;
			LPC_CCAN_API->can_transmit(&msg_obj);

			if(ledOn)
			{
				ledOn = false;
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 1);	//led 3
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, 0);	//led 2
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 0);	//led ?
			}
			else 
			{
				ledOn = true;
				Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 0);	//led 3
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 2, 1);	//led 2
				Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 1);	//led ?
			}
		}
	}
	return 0;
}


/*
connector schematic chip
1			d6		0,5
2			d7		0,3
3			d8		2,8
4			d9		0,2
5			d10		2,6
12			d1		0,4
13			d2		2,1
14			d3		2,7
15			d4		1,8
16			d5		2,0

int p1 = getPin(0,5);
int p2 = getPin(0,3); // --> right indicator
int p3 = getPin(2,8); // --> middle
int p4 = getPin(0,2); // --> left middle
int p5 = getPin(2,6);
int p12 = getPin(0,4);
int p13 = getPin(2,1); // --> right middle
int p14 = getPin(2,7); // --> left indicator
int p15 = getPin(1,8); //
int p16 = getPin(2,0); //
*/
