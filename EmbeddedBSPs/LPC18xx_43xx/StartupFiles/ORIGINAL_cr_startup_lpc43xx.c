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

void __attribute__ ((weak)) DAC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DAC_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) M0CORE_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void M0CORE_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) DMA_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DMA_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) FLASH_EEPROM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FLASH_EEPROM_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ETH_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ETH_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SDIO_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SDIO_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) LCD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LCD_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) USB0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USB0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) USB1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USB1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SCT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SCT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) RIT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RIT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) TIMER3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) MCPWM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MCPWM_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) I2C0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) I2C1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SPI_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SPI_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ADC1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SSP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SSP1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP1_IRQHandler();
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

void __attribute__ ((weak)) UART3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) I2S0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2S0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) I2S1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2S1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SPIFI_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SPIFI_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) SGPIO_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SGPIO_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO2_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO3_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO4_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO5_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO5_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO6_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO6_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) GPIO7_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO7_IRQHandler();
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

void __attribute__ ((weak)) EVRT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EVRT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) CAN1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN1_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) VADC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void VADC_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) ATIMER_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ATIMER_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) RTC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RTC_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) WDT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDT_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) M0SUB_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void M0SUB_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) CAN0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN0_IRQHandler();
	asm("bkpt 255");
};

void __attribute__ ((weak)) QEI_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void QEI_IRQHandler();
	asm("bkpt 255");
};

#else
void NMI_Handler()              __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()              __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void DAC_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void M0CORE_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_EEPROM_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void ETH_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void SDIO_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void LCD_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void USB0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void USB1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void SCT_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void RIT_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIMER0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER2_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER3_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void MCPWM_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void ADC0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void I2C0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void SPI_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void SSP0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void SSP1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void UART0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void UART1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void UART2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void UART3_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void I2S0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void I2S1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void SPIFI_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SGPIO_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO3_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO4_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO5_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO6_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIO7_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GINT0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void GINT1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EVRT_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void VADC_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void ATIMER_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void RTC_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void M0SUB_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void CAN0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void QEI_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x45] __attribute__ ((section (".isr_vector"))) = 
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
	&DAC_IRQHandler,
	&M0CORE_IRQHandler,
	&DMA_IRQHandler,
	NULL,
	&FLASH_EEPROM_IRQHandler,
	&ETH_IRQHandler,
	&SDIO_IRQHandler,
	&LCD_IRQHandler,
	&USB0_IRQHandler,
	&USB1_IRQHandler,
	&SCT_IRQHandler,
	&RIT_IRQHandler,
	&TIMER0_IRQHandler,
	&TIMER1_IRQHandler,
	&TIMER2_IRQHandler,
	&TIMER3_IRQHandler,
	&MCPWM_IRQHandler,
	&ADC0_IRQHandler,
	&I2C0_IRQHandler,
	&I2C1_IRQHandler,
	&SPI_IRQHandler,
	&ADC1_IRQHandler,
	&SSP0_IRQHandler,
	&SSP1_IRQHandler,
	&UART0_IRQHandler,
	&UART1_IRQHandler,
	&UART2_IRQHandler,
	&UART3_IRQHandler,
	&I2S0_IRQHandler,
	&I2S1_IRQHandler,
	&SPIFI_IRQHandler,
	&SGPIO_IRQHandler,
	&GPIO0_IRQHandler,
	&GPIO1_IRQHandler,
	&GPIO2_IRQHandler,
	&GPIO3_IRQHandler,
	&GPIO4_IRQHandler,
	&GPIO5_IRQHandler,
	&GPIO6_IRQHandler,
	&GPIO7_IRQHandler,
	&GINT0_IRQHandler,
	&GINT1_IRQHandler,
	&EVRT_IRQHandler,
	&CAN1_IRQHandler,
	NULL,
	&VADC_IRQHandler,
	&ATIMER_IRQHandler,
	&RTC_IRQHandler,
	NULL,
	&WDT_IRQHandler,
	&M0SUB_IRQHandler,
	&CAN0_IRQHandler,
	&QEI_IRQHandler,
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
