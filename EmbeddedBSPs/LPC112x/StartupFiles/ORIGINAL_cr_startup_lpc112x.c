/*
	This file contains the entry point (Reset_Handler) of your firmware project.
	The reset handled initializes the RAM and calls system library initializers as well as
	the platform-specific initializer and the main() function.
*/

extern void *_estack;

#define NULL ((void *)0)

void Reset_Handler();
void Default_Handler();

#ifdef DEBUG_DEFAULT_INTERRUPT_HANDLERS
void __attribute__ ((weak)) NMI_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void NMI_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HardFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HardFault_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SVC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SVC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PendSV_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PendSV_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SysTick_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SysTick_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP3_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP4_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP5_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP5_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP6_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP6_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP7_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP7_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP8_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP8_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP9_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP9_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP10_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP10_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP11_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP11_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WAKEUP12_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP12_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC_B_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC_B_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSP1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER_16_0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER_16_0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER_16_1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER_16_1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER_32_0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER_32_0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER_32_1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER_32_1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC_A_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC_A_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WDT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDT_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) BOD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BOD_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) FMC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FMC_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT3_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT0_IRQHandler();
	asm("bkpt 255");
}

#else
void NMI_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP0_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP1_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP2_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP3_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP4_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP5_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP6_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP7_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP8_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP9_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP10_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP11_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP12_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void ADC_B_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void SSP1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void I2C_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void TIMER_16_0_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void TIMER_16_1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void TIMER_32_0_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void TIMER_32_1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void SSP0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void UART0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void UART1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void UART2_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC_A_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void BOD_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void FMC_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EINT3_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void EINT2_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void EINT1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void EINT0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x30] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_estack,
	&Reset_Handler,
	&NMI_Handler,
	&HardFault_Handler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&SVC_Handler,
	NULL,
	NULL,
	&PendSV_Handler,
	&SysTick_Handler,
	&WAKEUP0_IRQHandler,
	&WAKEUP1_IRQHandler,
	&WAKEUP2_IRQHandler,
	&WAKEUP3_IRQHandler,
	&WAKEUP4_IRQHandler,
	&WAKEUP5_IRQHandler,
	&WAKEUP6_IRQHandler,
	&WAKEUP7_IRQHandler,
	&WAKEUP8_IRQHandler,
	&WAKEUP9_IRQHandler,
	&WAKEUP10_IRQHandler,
	&WAKEUP11_IRQHandler,
	&WAKEUP12_IRQHandler,
	&ADC_B_IRQHandler,
	&SSP1_IRQHandler,
	&I2C_IRQHandler,
	&TIMER_16_0_IRQHandler,
	&TIMER_16_1_IRQHandler,
	&TIMER_32_0_IRQHandler,
	&TIMER_32_1_IRQHandler,
	&SSP0_IRQHandler,
	&UART0_IRQHandler,
	&UART1_IRQHandler,
	&UART2_IRQHandler,
	&ADC_A_IRQHandler,
	&WDT_IRQHandler,
	&BOD_IRQHandler,
	&FMC_IRQHandler,
	&EINT3_IRQHandler,
	&EINT2_IRQHandler,
	&EINT1_IRQHandler,
	&EINT0_IRQHandler,
};

void SystemInit();
void __libc_init_array();
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;

void __attribute__((naked, noreturn)) Reset_Handler()
{
	//Normally the CPU should will setup the based on the value from the first entry in the vector table.
	//If you encounter problems with accessing stack variables during initialization, ensure the line below is enabled.
	#ifdef sram_layout
	asm ("ldr sp, =_estack");
	#endif

	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	SystemInit();
	__libc_init_array();
	(void)main();
	for (;;) ;
}

void __attribute__((naked, noreturn)) Default_Handler()
{
	//If you get stuck here, your code is missing a handler for some interrupt.
	//Define a 'DEBUG_DEFAULT_INTERRUPT_HANDLERS' macro via VisualGDB Project Properties and rebuild your project.
	//This will pinpoint a specific missing vector.
	for (;;) ;
}
