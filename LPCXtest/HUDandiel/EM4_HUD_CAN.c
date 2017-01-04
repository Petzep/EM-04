#include <chip.h>

#define CLK 1

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

void DataHigh() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, true);
}

void DataLow() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, false);
}

void DataHighBat() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, true);
}

void DataLowBat() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 6, false);
}

void DataHighDNR() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, true);
}

void DataLowDNR() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 7, false);
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

void dimLight(int dutyCycle, int CLKTIME) {
	for (int i = 0; i < CLKTIME; i++) {
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);
		Delay(100-dutyCycle);
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 1);
		Delay(dutyCycle);
	}
}

void sevenSegZero(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 1) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegOne(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 1 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegTwo(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 3 || i == 6) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegThree(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 5 || i == 6) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegFour(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 4 || i == 5 || i == 7) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegFive(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 2 || i == 5) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegSix(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 2) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegSeven(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 1 || i == 4 || i == 5 || i == 6) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegEight(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn)) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegNine(bool dotOn) {
	for (int i = 0; i < 8; i++) {
		if ((i == 0 && !dotOn) || i == 5) {
			DataLow();
			Tick();
		}
		else {
			DataHigh();
			Tick();
		}
	}
}

void sevenSegNumber(int nr, bool dotOn) {
	if (nr == 0) {
		sevenSegZero(dotOn);
	}

	else if (nr == 1) {
		sevenSegOne(dotOn);
	}

	else if (nr == 2) {
		sevenSegTwo(dotOn);
	}

	else if (nr == 3) {
		sevenSegThree(dotOn);
	}

	else if (nr == 4) {
		sevenSegFour(dotOn);
	}

	else if (nr == 5) {
		sevenSegFive(dotOn);
	}

	else if (nr == 6) {
		sevenSegSix(dotOn);
	}

	else if (nr == 7) {
		sevenSegSeven(dotOn);
	}

	else if (nr == 8) {
		sevenSegEight(dotOn);
	}

	else if (nr == 9) {
		sevenSegNine(dotOn);
	}
}

void sevenSeg(bool dotOn, int number) {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 1);
//	for (int j = 0; j < 60; j++) {
		sevenSegNumber(number/10, dotOn);
		sevenSegNumber(number % 10, false);
		Strobef();
//		Delay(100);
//	}
//	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 0);
}

void BatFill() {
	for (int i = 0; i < 5; i++) {
		DataHighBat();
		TickBat();
		StrobefBat();
		for (int j = 0; j < 1000; j++) {
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
		for (int j = 0; j < 1000; j++) {
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

void DNR(int j) {
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, 1);
//	for (int j = 0; j < 26; j++) {
		if (j == 0) {	//A
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}
		if (j == 1) {	//B
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}
		if (j == 2) {	//C
			for (int i = 0; i < 12; i++) {
				if (i == 6 || i == 7 || i == 8 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}
		if (j == 3) {	//D
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 7 || i == 8 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}
		if (j == 4) {	//E
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 7 || i == 8 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 5) {	//F
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 7 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 6) {	//G
			for (int i = 0; i < 12; i++) {
				if (i == 1 || i == 6 || i == 7 || i == 8 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 7) {	//H
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 7 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 8) {	//I
			for (int i = 0; i < 12; i++) {
				if (i == 4 || i == 8 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 9) {	//J
			for (int i = 0; i < 12; i++) {
				if (i == 0 || i == 8 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 10) {	//K
			for (int i = 0; i < 12; i++) {
				if (i == 1 || i == 2 || i == 5 || i == 6 || i == 7) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 11) {	//L
			for (int i = 0; i < 12; i++) {
				if (i == 6 || i == 7 || i == 8) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 12) {	//M
			for (int i = 0; i < 12; i++) {
				if (i == 2 || i == 3 || i == 6 || i == 7 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 13) {	//N
			for (int i = 0; i < 12; i++) {
				if (i == 1 || i == 3 || i == 6 || i == 7 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 14) {	//O
			for (int i = 0; i < 12; i++) {
				if (i == 6 || i == 7 || i == 8 || i == 9 || i == 10 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 15) {	//P
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 7 || i == 10 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 16) {	//Q
			for (int i = 0; i < 12; i++) {
				if (i == 1 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 17) {	//R
			for (int i = 0; i < 12; i++) {
				if (i == 1 || i == 5 || i == 6 || i == 7 || i == 10 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 18) {	//S
			for (int i = 0; i < 12; i++) {
				if (i == 5 || i == 6 || i == 8 || i == 9 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 19) {	//T
			for (int i = 0; i < 12; i++) {
				if (i == 4 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 20) {	//U
			for (int i = 0; i < 12; i++) {
				if (i == 6 || i == 7 || i == 8 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 21) {	//V
			for (int i = 0; i < 12; i++) {
				if (i == 2 || i == 3) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 22) {	//W
			for (int i = 0; i < 12; i++) {
				if (i == 0 || i == 1 || i == 6 || i == 7 || i == 9 || i == 10) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 23) {	//X
			for (int i = 0; i < 12; i++) {
				if (i == 0 || i == 1 || i == 2 || i == 3) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 24) {
			for (int i = 0; i < 12; i++) {
				if (i == 2 || i == 3 || i == 4) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

		if (j == 25) {
			for (int i = 0; i < 12; i++) {
				if (i == 0 || i == 2 || i == 5 || i == 8 || i == 11) {
					DataHighDNR();
					TickDNR();
				}
				else {
					DataLowDNR();
					TickDNR();
				}
			}
		}

	

		



		StrobefDNR();



//	for (int i = 0; i < 12; i++) {
//		DataHighDNR();
//		TickDNR();
//		StrobefDNR();
//		Delay(2000);
///*		for (int j = 0; j < 500; j++) {
//			if ((j % 25) == 1) {
//				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 1);
//				Delay(1);
//			}
//			else {
//				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);
//				Delay(1);
//			}
//		}*/
//	}
//
//
//	for (int i = 0; i < 12; i++) {
//		DataLowDNR();
//		TickDNR();
//		StrobefDNR();
//		Delay(2000);
///*		for (int j = 0; j < 500; j++) {
//			if ((j % 25) == 1) {
//				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 1);
//				Delay(1);
//			}
//			else {
//				Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);
//				Delay(1);
//			}
//		}*/
//	}
}

void botRed() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, 0);
}

void botGreen() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, (1));
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, (1));
}

void botBlue() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 1, (0));
	Chip_GPIO_WritePortBit(LPC_GPIO, 1, 11, (1));
}

void topRed() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, (1));
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, (0));
}

void topGreen() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, (1));
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, (1));
}

void topBlue() {
	Chip_GPIO_WritePortBit(LPC_GPIO, 3, 2, (0));
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 3, (1));
}
void RGBcycle() {
	for (int i = 0; i < (300); i++) {
		topRed();
		botRed();		
		Delay(100 - i/3);
		
		topGreen();
		botGreen();
		Delay(i/3);
	}
	for (int i = 0; i < 300; i++) {
		topGreen();
		botGreen();
		Delay(100 - i/3);

		topBlue();
		botBlue();
		Delay(i/3);
	}
	for (int i = 0; i < 300; i++) {
		topBlue();
		botBlue();
		Delay(100 - i/3);

		topRed();
		botRed();
		Delay(i/3);
	}
}

const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

#ifndef LPC_GPIO
#define LPC_GPIO LPC_GPIO_PORT
#endif

int main()
{
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);

	SysTick_Config(SystemCoreClock / 100000);
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

	DataLow();
	DataLowBat();
	DataLowDNR();

	for (int i = 0; i < 16; i++) {		//Flush shift registers
		Tick();
		TickBat();
		TickDNR();
	}


	bool dot = false;
	int counter = 1;
	int number = 0;
	int limit = 59;
	int DNRcount = 0;
	int dutyCycle = 10;		//integer between 0 and 100
	int CLKTIME = 1000;		//Time for one integer to be added on 7Seg

	for (;;)
	{		
		//RGBcycle();
		sevenSeg(dot, number);
		dimLight(dutyCycle, CLKTIME);
		/*if (dot == false) {
			dot = true;
		}
		else {
			dot = false;
		}*/
		/*for (int i = 0; i < 10; i++) {
			BatFill(counter);
		}*/
		if (number == limit && counter == 0) {
			DNR(DNRcount);
			DNRcount++;
		}
		if (number == (limit)) {
			BatClock(counter);
			counter++;
		}
		if (counter > 10) {
			counter = 0;
		}
		if (DNRcount == 25) {
			DNRcount = 0;
		}
		number++;
		if (number > limit) {
			number = 0;
		}


		
		
		/*Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, 1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, 1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, 1);
		Delay(1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 0);
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 10, 0);
		Chip_GPIO_WritePortBit(LPC_GPIO, 2, 11, 0);
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 8, 0);
		Delay(49);*/
	}

	return 0;
}
