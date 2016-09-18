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

void __attribute__ ((weak)) WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_17_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_17_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_18_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_18_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_19_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_19_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_20_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_20_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_21_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_21_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_22_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_22_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_23_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_23_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_24_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_24_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_25_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_25_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_26_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_26_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_27_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_27_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_28_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_28_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_29_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_29_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_30_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_30_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_31_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_31_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_32_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_32_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_33_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_33_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_34_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_34_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_35_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_35_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_36_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_36_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_37_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_37_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_38_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_38_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_39_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_39_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_40_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_40_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_41_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_41_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_42_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_42_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_43_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_43_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_44_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_44_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_45_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_45_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_46_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_46_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_47_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_47_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_48_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_48_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_49_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_49_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_50_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_50_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_51_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_51_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_52_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_52_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_53_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_53_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_54_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_54_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) INT_55_WAKEUP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void INT_55_WAKEUP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) I2C_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER16_0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER16_0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER16_1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER16_1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER32_0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER32_0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER32_1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER32_1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SSP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) UART_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) USB_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USB_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) USB_FIQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USB_FIQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC_IRQHandler();
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

void __attribute__ ((weak)) FMC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FMC_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIOINT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIOINT3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIOINT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIOINT2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIOINT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIOINT1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIOINT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIOINT0_IRQHandler();
	asm("bkpt 255");
};

#else
void NMI_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void INT_17_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_18_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_19_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_20_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_21_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_22_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_23_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_24_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_25_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_26_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_27_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_28_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_29_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_30_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_31_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_32_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_33_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_34_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_35_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_36_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_37_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_38_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_39_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_40_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_41_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_42_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_43_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_44_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_45_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_46_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_47_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_48_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_49_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_50_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_51_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_52_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_53_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_54_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void INT_55_WAKEUP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void I2C_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void TIMER16_0_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void TIMER16_1_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void TIMER32_0_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void TIMER32_1_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void SSP0_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void UART_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void USB_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void USB_FIQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void ADC_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void BOD_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void FMC_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void PIOINT3_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void PIOINT2_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void PIOINT1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void PIOINT0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x49] __attribute__ ((section (".isr_vector"))) = 
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
	&WAKEUP_IRQHandler,
	&INT_17_WAKEUP_IRQHandler,
	&INT_18_WAKEUP_IRQHandler,
	&INT_19_WAKEUP_IRQHandler,
	&INT_20_WAKEUP_IRQHandler,
	&INT_21_WAKEUP_IRQHandler,
	&INT_22_WAKEUP_IRQHandler,
	&INT_23_WAKEUP_IRQHandler,
	&INT_24_WAKEUP_IRQHandler,
	&INT_25_WAKEUP_IRQHandler,
	&INT_26_WAKEUP_IRQHandler,
	&INT_27_WAKEUP_IRQHandler,
	&INT_28_WAKEUP_IRQHandler,
	&INT_29_WAKEUP_IRQHandler,
	&INT_30_WAKEUP_IRQHandler,
	&INT_31_WAKEUP_IRQHandler,
	&INT_32_WAKEUP_IRQHandler,
	&INT_33_WAKEUP_IRQHandler,
	&INT_34_WAKEUP_IRQHandler,
	&INT_35_WAKEUP_IRQHandler,
	&INT_36_WAKEUP_IRQHandler,
	&INT_37_WAKEUP_IRQHandler,
	&INT_38_WAKEUP_IRQHandler,
	&INT_39_WAKEUP_IRQHandler,
	&INT_40_WAKEUP_IRQHandler,
	&INT_41_WAKEUP_IRQHandler,
	&INT_42_WAKEUP_IRQHandler,
	&INT_43_WAKEUP_IRQHandler,
	&INT_44_WAKEUP_IRQHandler,
	&INT_45_WAKEUP_IRQHandler,
	&INT_46_WAKEUP_IRQHandler,
	&INT_47_WAKEUP_IRQHandler,
	&INT_48_WAKEUP_IRQHandler,
	&INT_49_WAKEUP_IRQHandler,
	&INT_50_WAKEUP_IRQHandler,
	&INT_51_WAKEUP_IRQHandler,
	&INT_52_WAKEUP_IRQHandler,
	&INT_53_WAKEUP_IRQHandler,
	&INT_54_WAKEUP_IRQHandler,
	&INT_55_WAKEUP_IRQHandler,
	&I2C_IRQHandler,
	&TIMER16_0_IRQHandler,
	&TIMER16_1_IRQHandler,
	&TIMER32_0_IRQHandler,
	&TIMER32_1_IRQHandler,
	&SSP0_IRQHandler,
	&UART_IRQHandler,
	&USB_IRQHandler,
	&USB_FIQHandler,
	&ADC_IRQHandler,
	&WDT_IRQHandler,
	&BOD_IRQHandler,
	&FMC_IRQHandler,
	&PIOINT3_IRQHandler,
	&PIOINT2_IRQHandler,
	&PIOINT1_IRQHandler,
	&PIOINT0_IRQHandler,
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
