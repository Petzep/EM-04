#include <chip.h>

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


static ADC_CLOCK_SETUP_T ADCSetup;
uint16_t dataADC1; //ADCdata1



int main()
{

	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_SetBurstCmd(LPC_ADC, true);

	Chip_IOCON_PinMux(LPC_IOCON, 32, IOCON_MODE_INACT, IOCON_FUNC2);	//port 0 pin 11
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);					// channel of P0pin11



	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	
	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 7);

	for (;;)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 1);
		Delay(500);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 7, 0);
		Delay(500);



		//Waiting for A/D conversion complete
		if (Chip_ADC_ReadStatus(LPC_ADC, ADC_CH0, ADC_DR_DONE_STAT) != SET) {}
		//Read ADC value
		Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &dataADC1);



	}

	return 0;
}
