#include <chip.h>
#include "PWM.h"
volatile unsigned long SysTickCnt;


/*
typedef struct {					//!< TIMERn Structure       
	__IO uint32_t IR;				//!< Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. 
	__IO uint32_t TCR;				//!< Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. 
	__IO uint32_t TC;				//!< Timer Counter. The 32 bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. 
	__IO uint32_t PR;				//!< Prescale Register. The Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. 
	__IO uint32_t PC;				//!< Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. 
	__IO uint32_t MCR;				//!< Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. 
	__IO uint32_t MR[4];			//!< Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. 
	__IO uint32_t CCR;				//!< Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. 
	__IO uint32_t CR[4];			//!< Capture Register. CR is loaded with the value of TC when there is an event on the CAPn.0 input. 
	__IO uint32_t EMR;				//!< External Match Register. The EMR controls the external match pins MATn.0-3 (MAT0.0-3 and MAT1.0-3 respectively). 
	__I  uint32_t RESERVED0[12];
	__IO uint32_t CTCR;				//!< Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. 
	__IO uint32_t PWMC;
} LPC_TIMER_T;

*/

// To have the timer tick run at 100,000 Hz, the prescaler is SYSTEM CLOCK / 100,000
#define PWM_FREQ_RESHZ (100000)//Divider to system clock to get PWM prescale value
#define PWM_PRESCALER ((unsigned long)SystemCoreClock / (unsigned long)PWM_FREQ_RESHZ)

#define PWM_PERIOD_HZ (25000)
#define PWM_PERIOD_COUNT (PWM_FREQ_RESHZ / PWM_PERIOD_HZ)
#define PWM_DC_COUNT(a) ( (((101-a) * PWM_PERIOD_COUNT) / 100) )



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



void party(void) {										//please don't use during work hours

	for (int banana = 0; banana<200; banana++) {
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, true);
		Delay(15);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, true);
		Delay(15);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, false);
		Delay(15);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, false);
		Delay(15);
	}
}


/**
* @brief	Updated the PWM dutycycle
* @return	Nothing
*/

void PWMUpdate(int fan, unsigned char ucPercent)
{
	if (fan == 0)
		Chip_TIMER_SetMatch(LPC_TIMER3, 0, PWM_DC_COUNT(ucPercent));
	else if (fan == 1)
		Chip_TIMER_SetMatch(LPC_TIMER3, 0, PWM_DC_COUNT(ucPercent));

}


int main()
{
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	






	SystemCoreClockUpdate();
	//Enable and setup SysTick Timer at 1/10000 seconds (0.1ms)
	SysTick_Config(SystemCoreClock / 10000);
	/*
	//Enable timer 0 & 1 clock 
	Chip_TIMER_Init(LPC_TIMER3);
	//Reset any timer pending
	Chip_TIMER_Reset(LPC_TIMER3);
	//set the resolution of the ticks to the PWM timer (match register resolution)
	Chip_TIMER_PrescaleSet(LPC_TIMER3, (PWM_PRESCALER - 1));
	//Set duty cycle - MR0 default
	Chip_TIMER_SetMatch(LPC_TIMER3, 0, PWM_DC_COUNT(0));
	Chip_TIMER_SetMatch(LPC_TIMER3, 1, PWM_DC_COUNT(0));
	//Enable interupt on MR0 & MR1
	Chip_TIMER_MatchEnableInt(LPC_TIMER3, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER3, 1);
	//MR0 should not stop or clear the timer
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER3, 0);
	Chip_TIMER_ResetOnMatchDisable(LPC_TIMER3, 1);
	//Set period - MR1
	Chip_TIMER_SetMatch(LPC_TIMER3, 1, PWM_PERIOD_COUNT);
	Chip_TIMER_SetMatch(LPC_TIMER3, 1, PWM_PERIOD_COUNT);
	//MR1 should reset the timer to restart the cycle
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER3, 1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER3, 1);
	//Enable the timer
	Chip_TIMER_Enable(LPC_TIMER3);
	Chip_TIMER_Enable(LPC_TIMER3);

	
	// PWM mode enabled on CT32B0_MAT0
	((LPC_TIMER_T *)LPC_TIMER3)->PWMC = 1;
	((LPC_TIMER_T *)LPC_TIMER3)->PWMC = 1;
	*/
	/* Enable timer interrupt */
/*
	NVIC_ClearPendingIRQ(TIMER3_IRQn);
	NVIC_EnableIRQ(TIMER3_IRQn);
	
	*/





















	SysTick_Config(SystemCoreClock / 1000);
	Chip_GPIO_SetPortDIROutput(LPC_GPIO, 0, 1 << 10 | 1 << 11);
	volatile static int i = 0;
	for (;;)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, true);
		Delay(500);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 11, false);
		Delay(500);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, false);
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, true);
		Delay(300);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, false);
		Delay(600);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 10, true);
		Delay(600);
		i++;
		if (i > 40) {
			party();
			i = 0;

		}



	}

	return 0;
}
