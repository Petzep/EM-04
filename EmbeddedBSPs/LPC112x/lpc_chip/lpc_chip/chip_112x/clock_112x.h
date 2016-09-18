/*
 * @brief LPC11XX Clock control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CLOCK_1125_H_
#define __CLOCK_1125_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CLOCK_11XX CHIP: LPC11xx Clock Control block driver
 * @ingroup CHIP_1125_Drivers
 * @{
 */

/** Internal oscillator frequency */
#define SYSCON_IRC_FREQ (12000000)

/**
 * @brief	Set System PLL divider values
 * @param	msel    : PLL feedback divider value. M = msel + 1.
 * @param	psel    : PLL post divider value. P =  (1<<psel).
 * @return	Nothing
 * @note	See the user manual for how to setup the PLL.
 */
STATIC INLINE void Chip_Clock_SetupSystemPLL(uint8_t msel, uint8_t psel)
{
	LPC_SYSCON->SYSPLLCTRL = (msel & 0x1F) | ((psel & 0x3) << 5);
}

/**
 * @brief	Read System PLL lock status
 * @return	true of the PLL is locked. false if not locked
 */
STATIC INLINE bool Chip_Clock_IsSystemPLLLocked(void)
{
	return (bool) ((LPC_SYSCON->SYSPLLSTAT & 1) != 0);
}

/**
 * Clock sources for system and USB PLLs
 */
typedef enum CHIP_SYSCON_PLLCLKSRC {
	SYSCON_PLLCLKSRC_IRC = 0,		/*!< Internal oscillator in */
	SYSCON_PLLCLKSRC_MAINOSC,		/*!< Crystal (main) oscillator in */
	SYSCON_PLLCLKSRC_RESERVED1,		/*!< Reserved */
	SYSCON_PLLCLKSRC_RESERVED2,		/*!< Reserved */
} CHIP_SYSCON_PLLCLKSRC_T;

/**
 * @brief	Set System PLL clock source
 * @param	src	: Clock source for system PLL
 * @return	Nothing
 * @note	This function will also toggle the clock source update register
 * to update the clock source.
 */
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCON_PLLCLKSRC_T src);

/**
 * @brief	Bypass System Oscillator and set oscillator frequency range
 * @param	bypass	: Flag to bypass oscillator
 * @param	highfr	: Flag to set oscillator range from 15-25 MHz
 * @return	Nothing
 * @note	Sets the PLL input to bypass the oscillator. This would be
 * used if an external clock that is not an oscillator is attached
 * to the XTALIN pin.
 */
void Chip_Clock_SetPLLBypass(bool bypass, bool highfr);

/**
 * Watchdog and low frequency oscillator frequencies plus or minus 40%
 */
typedef enum CHIP_WDTLFO_OSC {
	WDTLFO_OSC_ILLEGAL,
	WDTLFO_OSC_0_60,	/*!< 0.6 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_05,	/*!< 1.05 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_40,	/*!< 1.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_75,	/*!< 1.75 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_10,	/*!< 2.1 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_40,	/*!< 2.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_70,	/*!< 2.7 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_00,	/*!< 3.0 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_25,	/*!< 3.25 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_50,	/*!< 3.5 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_75,	/*!< 3.75 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_00,	/*!< 4.0 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_20,	/*!< 4.2 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_40,	/*!< 4.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_4_60		/*!< 4.6 MHz watchdog/LFO rate */
} CHIP_WDTLFO_OSC_T;

/**
 * @brief	Setup Watchdog oscillator rate and divider
 * @param	wdtclk	: Selected watchdog clock rate
 * @param	div		: Watchdog divider value, even value between 2 and 64
 * @return	Nothing
 * @note	Watchdog rate = selected rate divided by divider rate
 */
STATIC INLINE void Chip_Clock_SetWDTOSC(CHIP_WDTLFO_OSC_T wdtclk, uint8_t div)
{
	LPC_SYSCON->WDTOSCCTRL  = (((uint32_t) wdtclk) << 5) | ((div >> 1) - 1);
}

/**
 * Clock sources for main system clock
 */
typedef enum CHIP_SYSCON_MAINCLKSRC {
	SYSCON_MAINCLKSRC_IRC = 0,		/*!< Internal oscillator */
	SYSCON_MAINCLKSRC_PLLIN,		/*!< System PLL input */
	SYSCON_MAINCLKSRC_LFOSC,		/*!< LF oscillator rate (11Axx only) */
	SYSCON_MAINCLKSRC_WDTOSC = SYSCON_MAINCLKSRC_LFOSC,	/*!< Watchdog oscillator rate */
	SYSCON_MAINCLKSRC_PLLOUT,		/*!< System PLL output */
} CHIP_SYSCON_MAINCLKSRC_T;

/**
 * @brief	Set main system clock source
 * @param	src	: Clock source for main system
 * @return	Nothing
 * @note	This function will also toggle the clock source update register
 * to update the clock source.
 */
void Chip_Clock_SetMainClockSource(CHIP_SYSCON_MAINCLKSRC_T src);

/**
 * @brief   Returns the main clock source
 * @return	Which clock is used for the core clock source?
 */
STATIC INLINE CHIP_SYSCON_MAINCLKSRC_T Chip_Clock_GetMainClockSource(void)
{
	return (CHIP_SYSCON_MAINCLKSRC_T) (LPC_SYSCON->MAINCLKSEL);
}

/**
 * @brief	Set system clock divider
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetSysClockDiv(uint32_t div)
{
	LPC_SYSCON->SYSAHBCLKDIV  = div;
}

/**
 * System and peripheral clocks
 */
typedef enum CHIP_SYSCON_CLOCK {
	SYSCON_CLOCK_SYS = 0,				/*!< 0: System clock */
	SYSCON_CLOCK_ROM,					/*!< 1: ROM clock */
	SYSCON_CLOCK_RAM,					/*!< 2: RAM clock */
	SYSCON_CLOCK_FLASHREG,				/*!< 3: FLASH register interface clock */
	SYSCON_CLOCK_FLASHARRAY,			/*!< 4: FLASH array access clock */
	SYSCON_CLOCK_I2C,					/*!< 5: I2C clock, not on LPC110x */
	SYSCON_CLOCK_GPIO,					/*!< 6: GPIO clock */
	SYSCON_CLOCK_CT16B0,				/*!< 7: 16-bit Counter/timer 0 clock */
	SYSCON_CLOCK_CT16B1,				/*!< 8: 16-bit Counter/timer 1 clock */
	SYSCON_CLOCK_CT32B0,				/*!< 9: 32-bit Counter/timer 0 clock */
	SYSCON_CLOCK_CT32B1,				/*!< 10: 32-bit Counter/timer 1 clock */
	SYSCON_CLOCK_SSP0,					/*!< 11: SSP0 clock */
	SYSCON_CLOCK_UART0,					/*!< 12: UART0 clock */
	SYSCON_CLOCK_ADC,					/*!< 13: ADC clock */
	SYSCON_CLOCK_RESERVED14,			/*!< 14: Reserved */
	SYSCON_CLOCK_WDT,					/*!< 15: Watchdog timer clock */
	SYSCON_CLOCK_IOCON,					/*!< 16: IOCON block clock */
	SYSCON_CLOCK_RESERVED17,			/*!< 17: Reserved */
	SYSCON_CLOCK_SSP1,					/*!< 18: SSP1 clock, LPC11A/C/E/Uxx//1125 only */
} CHIP_SYSCON_CLOCK_T;

/**
 * @brief	Enable a system or peripheral clock
 * @param	clk	: Clock to enable
 * @return	Nothing
 */
STATIC INLINE void Chip_Clock_EnablePeriphClock(CHIP_SYSCON_CLOCK_T clk)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << clk);
}

/**
 * @brief	Disable a system or peripheral clock
 * @param	clk	: Clock to disable
 * @return	Nothing
 */
STATIC INLINE void Chip_Clock_DisablePeriphClock(CHIP_SYSCON_CLOCK_T clk)
{
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << clk);
}

/**
 * @brief	Set SSP0 divider
 * @param	div	: divider for SSP0 clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The SSP0 clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetSSP0ClockDiv(uint32_t div)
{
	LPC_SYSCON->SSP0CLKDIV  = div;
}

/**
 * @brief	Return SSP0 divider
 * @return	divider for SSP0 clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetSSP0ClockDiv(void)
{
	return LPC_SYSCON->SSP0CLKDIV;
}

/**
 * @brief	Set UART divider clock
 * @param	div	: divider for UART clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The UART clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetUARTClockDiv(uint32_t div)
{
	LPC_SYSCON->UART0CLKDIV  = div;
}

/**
 * @brief	Return UART divider
 * @return	divider for UART clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetUARTClockDiv(void)
{
	return LPC_SYSCON->UART0CLKDIV;
}

/**
 * @brief	Set SSP1 divider clock
 * @param	div	: divider for SSP1 clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The SSP1 clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetSSP1ClockDiv(uint32_t div)
{
	LPC_SYSCON->SSP1CLKDIV  = div;
}

/**
 * @brief	Return SSP1 divider
 * @return	divider for SSP1 clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetSSP1ClockDiv(void)
{
	return LPC_SYSCON->SSP1CLKDIV;
}

/**
 * Clock sources for WDT
 */
typedef enum CHIP_SYSCON_WDTCLKSRC {
	SYSCON_WDTCLKSRC_IRC = 0,		/*!< Internal oscillator for watchdog clock */
	SYSCON_WDTCLKSRC_MAINSYSCLK,	/*!< Main system clock for watchdog clock */
	SYSCON_WDTCLKSRC_WDTOSC,		/*!< Watchdog oscillator for watchdog clock */
} CHIP_SYSCON_WDTCLKSRC_T;

/**
 * @brief	Set WDT clock source and divider
 * @param	src	: Clock source for WDT
 * @param	div	: divider for WDT clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The WDT clock
 * rate is the clock source divided by the divider. This function will
 * also toggle the clock source update register to update the clock
 * source.
 */
void Chip_Clock_SetWDTClockSource(CHIP_SYSCON_WDTCLKSRC_T src, uint32_t div);

/**
 * Clock sources for CLKOUT
 */
typedef enum CHIP_SYSCON_CLKOUTSRC {
	SYSCON_CLKOUTSRC_IRC = 0,		/*!< Internal oscillator for CLKOUT */
	SYSCON_CLKOUTSRC_MAINOSC,		/*!< Main oscillator for CLKOUT */
	SYSCON_CLKOUTSRC_WDTOSC,		/*!< Watchdog oscillator for CLKOUT */
	SYSCON_CLKOUTSRC_LFOSC = SYSCON_CLKOUTSRC_WDTOSC,	/*!< LF oscillator rate (LPC11A/Exx only) for CLKOUT */
	SYSCON_CLKOUTSRC_MAINSYSCLK,	/*!< Main system clock for CLKOUT */
} CHIP_SYSCON_CLKOUTSRC_T;

/**
 * @brief	Set CLKOUT clock source and divider
 * @param	src	: Clock source for CLKOUT
 * @param	div	: divider for CLKOUT clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The CLKOUT clock
 * rate is the clock source divided by the divider. This function will
 * also toggle the clock source update register to update the clock
 * source.
 */
void Chip_Clock_SetCLKOUTSource(CHIP_SYSCON_CLKOUTSRC_T src, uint32_t div);

/**
 * @brief	Returns the main oscillator clock rate
 * @return	main oscillator clock rate
 */
STATIC INLINE uint32_t Chip_Clock_GetMainOscRate(void)
{
	return OscRateIn;
}

/**
 * @brief	Returns the internal oscillator (IRC) clock rate
 * @return	internal oscillator (IRC) clock rate
 */
STATIC INLINE uint32_t Chip_Clock_GetIntOscRate(void)
{
	return SYSCON_IRC_FREQ;
}

/**
 * @brief	Return estimated watchdog oscillator rate
 * @return	Estimated watchdog oscillator rate
 * @note	This rate is accurate to plus or minus 40%.
 */
uint32_t Chip_Clock_GetWDTOSCRate(void);

/**
 * @brief	Return System PLL input clock rate
 * @return	System PLL input clock rate
 */
uint32_t Chip_Clock_GetSystemPLLInClockRate(void);

/**
 * @brief	Return System PLL output clock rate
 * @return	System PLL output clock rate
 */
uint32_t Chip_Clock_GetSystemPLLOutClockRate(void);

/**
 * @brief	Return main clock rate
 * @return	main clock rate
 */
uint32_t Chip_Clock_GetMainClockRate(void);

/**
 * @brief	Return system clock rate
 * @return	system clock rate
 */
uint32_t Chip_Clock_GetSystemClockRate(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_1125_H_ */
