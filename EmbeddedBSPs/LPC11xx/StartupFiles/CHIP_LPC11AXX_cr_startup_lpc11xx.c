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

void __attribute__ ((weak)) PIN_INT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT3_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT4_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT5_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT5_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT6_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT6_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PIN_INT7_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT7_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GINT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GINT0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GINT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GINT1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ACMP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DAC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DAC_IRQHandler();
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

void __attribute__ ((weak)) TIMER16_0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER16_0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER16_1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER16_1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER32_0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER32_0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER32_1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER32_1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) USART_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USART_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC_IRQHandler();
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

#else
void NMI_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT0_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT1_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT2_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT3_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT4_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT5_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT6_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT7_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void GINT0_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void GINT1_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void ACMP_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void DAC_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SSP1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void I2C_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER16_0_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void TIMER16_1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void TIMER32_0_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void TIMER32_1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void SSP0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void USART_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void ADC_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void BOD_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void FMC_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
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
	&PIN_INT0_IRQHandler,
	&PIN_INT1_IRQHandler,
	&PIN_INT2_IRQHandler,
	&PIN_INT3_IRQHandler,
	&PIN_INT4_IRQHandler,
	&PIN_INT5_IRQHandler,
	&PIN_INT6_IRQHandler,
	&PIN_INT7_IRQHandler,
	&GINT0_IRQHandler,
	&GINT1_IRQHandler,
	&ACMP_IRQHandler,
	&DAC_IRQHandler,
	NULL,
	NULL,
	&SSP1_IRQHandler,
	&I2C_IRQHandler,
	&TIMER16_0_IRQHandler,
	&TIMER16_1_IRQHandler,
	&TIMER32_0_IRQHandler,
	&TIMER32_1_IRQHandler,
	&SSP0_IRQHandler,
	&USART_IRQHandler,
	NULL,
	NULL,
	&ADC_IRQHandler,
	&WDT_IRQHandler,
	&BOD_IRQHandler,
	&FMC_IRQHandler,
	NULL,
	NULL,
	NULL,
	NULL,
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
