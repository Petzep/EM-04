/*
 * @brief LPC11XX System clock control functions
 *
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
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
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Inprecise clock rates for the watchdog oscillator */
STATIC const uint32_t wdtOSCRate[WDTLFO_OSC_4_60 + 1] = {
	0,					/* WDT_OSC_ILLEGAL */
	600000,				/* WDT_OSC_0_60 */
	1050000,			/* WDT_OSC_1_05 */
	1400000,			/* WDT_OSC_1_40 */
	1750000,			/* WDT_OSC_1_75 */
	2100000,			/* WDT_OSC_2_10 */
	2400000,			/* WDT_OSC_2_40 */
	2700000,			/* WDT_OSC_2_70 */
	3000000,			/* WDT_OSC_3_00 */
	3250000,			/* WDT_OSC_3_25 */
	3500000,			/* WDT_OSC_3_50 */
	3750000,			/* WDT_OSC_3_75 */
	4000000,			/* WDT_OSC_4_00 */
	4200000,			/* WDT_OSC_4_20 */
	4400000,			/* WDT_OSC_4_40 */
	4600000				/* WDT_OSC_4_60 */
};

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Compute a WDT or LFO rate */
STATIC uint32_t Chip_Clock_GetWDTLFORate(uint32_t reg)
{
	uint32_t div;
	CHIP_WDTLFO_OSC_T clk;

	/* Get WDT oscillator settings */
	clk = (CHIP_WDTLFO_OSC_T) ((reg >> 5) & 0xF);
	div = reg & 0x1F;

	/* Compute clock rate and divided by divde value */
	return wdtOSCRate[clk] / ((div + 1) << 1);
}

/* Compute a PLL frequency */
STATIC uint32_t Chip_Clock_GetPLLFreq(uint32_t PLLReg, uint32_t inputRate)
{
	uint32_t msel = ((PLLReg & 0x1F) + 1);

	return inputRate * msel;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set System PLL clock source */
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCON_PLLCLKSRC_T src)
{
	LPC_SYSCON->SYSPLLCLKSEL  = (uint32_t) src;
	LPC_SYSCON->SYSPLLCLKUEN  = 0;
	LPC_SYSCON->SYSPLLCLKUEN  = 1;
}

/* Bypass System Oscillator and set oscillator frequency range */
void Chip_Clock_SetPLLBypass(bool bypass, bool highfr)
{
	uint32_t ctrl = 0;

	if (bypass) {
		ctrl |= (1 << 0);
	}
	if (highfr) {
		ctrl |= (1 << 1);
	}

	LPC_SYSCON->SYSOSCCTRL = ctrl;
}

/* Set main system clock source */
void Chip_Clock_SetMainClockSource(CHIP_SYSCON_MAINCLKSRC_T src)
{
	LPC_SYSCON->MAINCLKSEL  = (uint32_t) src;
	LPC_SYSCON->MAINCLKUEN  = 0;
	LPC_SYSCON->MAINCLKUEN  = 1;
}

/* Set WDT clock source and divider */
void Chip_Clock_SetWDTClockSource(CHIP_SYSCON_WDTCLKSRC_T src, uint32_t div)
{
	LPC_SYSCON->WDTCLKSEL = (uint32_t) src;
	LPC_SYSCON->WDTCLKUEN = 0;
	LPC_SYSCON->WDTCLKUEN = 1;
	LPC_SYSCON->WDTCLKDIV = div;
}

/* Set CLKOUT clock source and divider */
void Chip_Clock_SetCLKOUTSource(CHIP_SYSCON_CLKOUTSRC_T src, uint32_t div)
{
	LPC_SYSCON->CLKOUTSEL = (uint32_t) src;
	LPC_SYSCON->CLKOUTUEN = 0;
	LPC_SYSCON->CLKOUTUEN = 1;
	LPC_SYSCON->CLKOUTDIV = div;
}


/* Return estimated watchdog oscillator rate */
uint32_t Chip_Clock_GetWDTOSCRate(void)
{
	return Chip_Clock_GetWDTLFORate(LPC_SYSCON->WDTOSCCTRL);
}

/* Return System PLL input clock rate */
uint32_t Chip_Clock_GetSystemPLLInClockRate(void)
{
	uint32_t clkRate;

	switch ((CHIP_SYSCON_PLLCLKSRC_T) (LPC_SYSCON->SYSPLLCLKSEL & 0x3)) {
	case SYSCON_PLLCLKSRC_IRC:
		clkRate = Chip_Clock_GetIntOscRate();
		break;

	case SYSCON_PLLCLKSRC_MAINOSC:
		clkRate = Chip_Clock_GetMainOscRate();
		break;

	default:
		clkRate = 0;
	}

	return clkRate;
}

/* Return System PLL output clock rate */
uint32_t Chip_Clock_GetSystemPLLOutClockRate(void)
{
	return Chip_Clock_GetPLLFreq(LPC_SYSCON->SYSPLLCTRL,
								 Chip_Clock_GetSystemPLLInClockRate());
}

/* Return main clock rate */
uint32_t Chip_Clock_GetMainClockRate(void)
{
	uint32_t clkRate = 0;

	switch ((CHIP_SYSCON_MAINCLKSRC_T) (LPC_SYSCON->MAINCLKSEL & 0x3)) {
	case SYSCON_MAINCLKSRC_IRC:
		clkRate = Chip_Clock_GetIntOscRate();
		break;

	case SYSCON_MAINCLKSRC_PLLIN:
		clkRate = Chip_Clock_GetSystemPLLInClockRate();
		break;

	case SYSCON_MAINCLKSRC_WDTOSC:
		clkRate = Chip_Clock_GetWDTOSCRate();
		break;

	case SYSCON_MAINCLKSRC_PLLOUT:
		clkRate = Chip_Clock_GetSystemPLLOutClockRate();
		break;
	}

	return clkRate;
}

/* Return system clock rate */
uint32_t Chip_Clock_GetSystemClockRate(void)
{
	/* No point in checking for divide by 0 */
	return Chip_Clock_GetMainClockRate() / LPC_SYSCON->SYSAHBCLKDIV;
}
