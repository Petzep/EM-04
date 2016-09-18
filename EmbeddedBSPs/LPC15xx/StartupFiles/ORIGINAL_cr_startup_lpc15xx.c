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

void __attribute__ ((weak)) MemManage_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MemManage_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) BusFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BusFault_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) UsageFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UsageFault_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SVC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SVC_Handler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) DebugMon_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DebugMon_Handler();
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

void __attribute__ ((weak)) EEPROM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EEPROM_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) DMA_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DMA_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GINT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GINT0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GINT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GINT1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT4_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT5_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT5_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT6_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT6_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) PIN_INT7_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PIN_INT7_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) RIT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RIT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SCT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SCT0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SCT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SCT1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SCT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SCT2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SCT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SCT3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) MRT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MRT_IRQHandler();
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

void __attribute__ ((weak)) I2C0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C0_IRQHandler();
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

void __attribute__ ((weak)) CAN_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN_IRQHandler();
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

void __attribute__ ((weak)) USBWakeup_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USBWakeup_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC0A_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC0A_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC0B_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC0B_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC0_THCMP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC0_THCMP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC0_OVR_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC0_OVR_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC1A_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1A_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC1B_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1B_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC1_THCMP_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1_THCMP_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC1_OVR_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1_OVR_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) DAC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DAC_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ACMP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ACMP1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ACMP2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ACMP3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ACMP3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) QEI_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void QEI_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) RTC_ALARM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RTC_ALARM_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) RTC_WAKE_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RTC_WAKE_IRQHandler();
	asm("bkpt 255");
};

#else
void NMI_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void BOD_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void FMC_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EEPROM_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void DMA_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GINT0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void GINT1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT0_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT1_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT2_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT3_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT4_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT5_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT6_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void PIN_INT7_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void RIT_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SCT0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SCT1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SCT2_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SCT3_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void MRT_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void UART0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void UART1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void UART2_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void I2C0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SPI0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void CAN_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void USB_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void USB_FIQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void USBWakeup_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void ADC0A_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC0B_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC0_THCMP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void ADC0_OVR_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void ADC1A_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC1B_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_THCMP_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_OVR_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void DAC_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void ACMP0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ACMP1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ACMP2_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ACMP3_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void QEI_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void RTC_ALARM_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void RTC_WAKE_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x3f] __attribute__ ((section (".isr_vector"))) = 
{
	&_estack,
	&Reset_Handler,
	&NMI_Handler,
	&HardFault_Handler,
	&MemManage_Handler,
	&BusFault_Handler,
	&UsageFault_Handler,
	NULL,
	NULL,
	NULL,
	NULL,
	&SVC_Handler,
	&DebugMon_Handler,
	NULL,
	&PendSV_Handler,
	&SysTick_Handler,
	&WDT_IRQHandler,
	&BOD_IRQHandler,
	&FMC_IRQHandler,
	&EEPROM_IRQHandler,
	&DMA_IRQHandler,
	&GINT0_IRQHandler,
	&GINT1_IRQHandler,
	&PIN_INT0_IRQHandler,
	&PIN_INT1_IRQHandler,
	&PIN_INT2_IRQHandler,
	&PIN_INT3_IRQHandler,
	&PIN_INT4_IRQHandler,
	&PIN_INT5_IRQHandler,
	&PIN_INT6_IRQHandler,
	&PIN_INT7_IRQHandler,
	&RIT_IRQHandler,
	&SCT0_IRQHandler,
	&SCT1_IRQHandler,
	&SCT2_IRQHandler,
	&SCT3_IRQHandler,
	&MRT_IRQHandler,
	&UART0_IRQHandler,
	&UART1_IRQHandler,
	&UART2_IRQHandler,
	&I2C0_IRQHandler,
	&SPI0_IRQHandler,
	&SPI1_IRQHandler,
	&CAN_IRQHandler,
	&USB_IRQHandler,
	&USB_FIQHandler,
	&USBWakeup_IRQHandler,
	&ADC0A_IRQHandler,
	&ADC0B_IRQHandler,
	&ADC0_THCMP_IRQHandler,
	&ADC0_OVR_IRQHandler,
	&ADC1A_IRQHandler,
	&ADC1B_IRQHandler,
	&ADC1_THCMP_IRQHandler,
	&ADC1_OVR_IRQHandler,
	&DAC_IRQHandler,
	&ACMP0_IRQHandler,
	&ACMP1_IRQHandler,
	&ACMP2_IRQHandler,
	&ACMP3_IRQHandler,
	&QEI_IRQHandler,
	&RTC_ALARM_IRQHandler,
	&RTC_WAKE_IRQHandler,
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
