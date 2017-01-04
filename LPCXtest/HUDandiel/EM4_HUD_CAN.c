#include <chip.h>

#define CLK 1
#define RGB_TOP 1
#define RGB_BOT 0

enum RGB_LED
{
	redLed,
	greenLed,
	blueLed,
};

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

//ugly delay function + dimmer
void dimLight(int dutyCycle, int CLKTIME) {
	for (int i = 0; i < CLKTIME; i++) {
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 0);
		Delay(100-dutyCycle);
		Chip_GPIO_WritePortBit(LPC_GPIO, 3, 3, 1);
		Delay(dutyCycle);
	}
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
	for(int i = 0; i < 8; i++)
	{
		unsigned long long bit = value & 0b10000000;
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 8, bit);
		Tick();
		value <<= 1;
	}
	
}

//7-seg function
void sevenSeg(bool dotOn, int number)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 10, 1);
	sevenSegNumber(number/10, dotOn);
	sevenSegNumber(number % 10, false);
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
void DNR(char ch)
{
	unsigned long long value;
	Chip_GPIO_WritePortBit(LPC_GPIO, 2, 0, 1);
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

	ledInit();

	bool dot = false;
	int counter = 1;
	int number = 0;
	int limit = 59;
	char DNRcount = '0';
	int dutyCycle = 10;		//integer between 0 and 100
	int CLKTIME = 1000;		//Time for one integer to be added on 7Seg

	for (;;)
	{		
		//RGBcycle(500, true, true);
		sevenSeg(dot, number);
		//rgbLed(RGB_TOP, number % 3);
		//rgbLed(RGB_BOT, number % 3);
		//rgbLed(RGB_TOP, greenLed);
		//BatFill(10000);
		//rgbLed(RGB_TOP, redLed);
		//RGBcycle(500, false, true);
		dimLight(dutyCycle, CLKTIME);

		if (number == limit && counter == 0) {
			DNR(DNRcount);
			DNRcount++;
			if(DNRcount == 58)
				DNRcount = 65;
			else if(DNRcount == 91)
				DNRcount = 97;
			else if(DNRcount == 123)
				DNRcount = 48;
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
		if (number > limit)
			number = 0;
	}
	return 0;
}
