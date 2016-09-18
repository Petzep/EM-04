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
};

void __attribute__ ((weak)) HardFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HardFault_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SVC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SVC_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PendSV_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PendSV_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SysTick_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SysTick_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SPI0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SPI0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SPI1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SPI1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) UART0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) UART1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) UART2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) I2C_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SCT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SCT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) MRT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MRT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) CMP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CMP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) WDT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) BOD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BOD_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) WKT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WKT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT4_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT5_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT5_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT6_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT6_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PININT7_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PININT7_IRQHandler();
	asm("bkpt 255");
};

#else
void NMI_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()   __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void SPI0_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void UART0_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void UART1_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void UART2_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void I2C_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void SCT_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void MRT_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void CMP_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void BOD_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void WKT_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void PININT0_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT2_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT3_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT4_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT5_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT6_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void PININT7_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x30] __attribute__ ((section (".isr_vector"))) = 
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
	&SPI0_IRQHandler,
	&SPI1_IRQHandler,
	NULL,
	&UART0_IRQHandler,
	&UART1_IRQHandler,
	&UART2_IRQHandler,
	NULL,
	NULL,
	&I2C_IRQHandler,
	&SCT_IRQHandler,
	&MRT_IRQHandler,
	&CMP_IRQHandler,
	&WDT_IRQHandler,
	&BOD_IRQHandler,
	NULL,
	&WKT_IRQHandler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&PININT0_IRQHandler,
	&PININT1_IRQHandler,
	&PININT2_IRQHandler,
	&PININT3_IRQHandler,
	&PININT4_IRQHandler,
	&PININT5_IRQHandler,
	&PININT6_IRQHandler,
	&PININT7_IRQHandler,
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
