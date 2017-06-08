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

void __attribute__ ((weak)) MemManage_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MemManage_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) BusFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BusFault_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UsageFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UsageFault_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SVC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SVC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DebugMon_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DebugMon_Handler();
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

void __attribute__ ((weak)) WDT_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDT_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TIMER3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TIMER3_IRQHandler();
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

void __attribute__ ((weak)) UART3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART3_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWM1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWM1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) IntDefaultHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void IntDefaultHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSP0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSP1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PLL0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PLL0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) RTC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RTC_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EINT3_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EINT3_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) BOD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BOD_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) USB_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USB_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) CAN_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DMA_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DMA_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2S_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2S_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ENET_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ENET_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) MCI_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MCI_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) MCPWM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MCPWM_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) QEI_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void QEI_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PLL1_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PLL1_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) USBActivity_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USBActivity_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) CANActivity_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CANActivity_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART4_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART4_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSP2_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSP2_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) LCD_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LCD_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIO_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIO_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWM0_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWM0_IRQHandler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EEPROM_IRQHandler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EEPROM_IRQHandler();
	asm("bkpt 255");
}

#else
void NMI_Handler()             __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()             __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void TIMER0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void TIMER1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void TIMER2_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void TIMER3_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void UART0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void UART1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void UART2_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void UART3_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void PWM1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void IntDefaultHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void SSP0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SSP1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void PLL0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void RTC_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void EINT0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void EINT1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void EINT2_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void EINT3_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void ADC_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BOD_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void USB_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void CAN_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void DMA_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void I2S_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void ENET_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void MCI_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void MCPWM_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void QEI_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void PLL1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void USBActivity_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void CANActivity_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void UART4_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SSP2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void LCD_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void GPIO_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void PWM0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EEPROM_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x39] __attribute__ ((section (".isr_vector"), used)) = 
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
	&TIMER0_IRQHandler,
	&TIMER1_IRQHandler,
	&TIMER2_IRQHandler,
	&TIMER3_IRQHandler,
	&UART0_IRQHandler,
	&UART1_IRQHandler,
	&UART2_IRQHandler,
	&UART3_IRQHandler,
	&PWM1_IRQHandler,
	&I2C0_IRQHandler,
	&I2C1_IRQHandler,
	&I2C2_IRQHandler,
	&IntDefaultHandler,
	&SSP0_IRQHandler,
	&SSP1_IRQHandler,
	&PLL0_IRQHandler,
	&RTC_IRQHandler,
	&EINT0_IRQHandler,
	&EINT1_IRQHandler,
	&EINT2_IRQHandler,
	&EINT3_IRQHandler,
	&ADC_IRQHandler,
	&BOD_IRQHandler,
	&USB_IRQHandler,
	&CAN_IRQHandler,
	&DMA_IRQHandler,
	&I2S_IRQHandler,
	&ENET_IRQHandler,
	&MCI_IRQHandler,
	&MCPWM_IRQHandler,
	&QEI_IRQHandler,
	&PLL1_IRQHandler,
	&USBActivity_IRQHandler,
	&CANActivity_IRQHandler,
	&UART4_IRQHandler,
	&SSP2_IRQHandler,
	&LCD_IRQHandler,
	&GPIO_IRQHandler,
	&PWM0_IRQHandler,
	&EEPROM_IRQHandler,
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
