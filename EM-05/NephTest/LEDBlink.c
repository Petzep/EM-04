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

int main()
{
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	
	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 10 | 1 << 11);

	for (;;)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, true);
		Delay(500);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, false);
		Delay(501);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, false);
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, true);
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, false);
		Delay(600);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, true);
		Delay(600);
	}

	return 0;
}
