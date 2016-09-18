/*
 * @brief LPC11125 System Control functions
 *
 * Copyright(C) NXP Semiconductors, 2015
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

/* PDSLEEPCFG register mask */
#define PDSLEEPUSEMASK 0x000018FF
#define PDSLEEPMASKTMP (SYSCON_DEEPSLP_BOD_PD | SYSCON_DEEPSLP_WDTOSC_PD)
#define PDSLEEPMASK ((PDSLEEPUSEMASK) &~(PDSLEEPMASKTMP))

/* PDWAKECFG register mask */
#define PDWAKEUPUSEMASK 0x0000ED00
#define PDWAKEUPMASKTMP 0x000000FF

/* PDRUNCFG register mask */
#define PDRUNCFGUSEMASK 0x0000ED00
#define PDRUNCFGMASKTMP 0x000000FF

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Setup deep sleep behaviour for power down */
void Chip_SYSCON_SetDeepSleepPD(uint32_t sleepmask)
{
	/* Update new value */
	LPC_SYSCON->PDSLEEPCFG = PDSLEEPMASK | (sleepmask & PDSLEEPMASKTMP);
}

/* Setup wakeup behaviour from deep sleep */
void Chip_SYSCON_SetWakeup(uint32_t wakeupmask)
{
	/* Update new value */
	LPC_SYSCON->PDWAKECFG = PDWAKEUPUSEMASK | (wakeupmask & PDWAKEUPMASKTMP);
}

/* Power down one or more blocks or peripherals */
void Chip_SYSCON_PowerDown(uint32_t powerdownmask)
{
	uint32_t pdrun;

	pdrun = LPC_SYSCON->PDRUNCFG & PDRUNCFGMASKTMP;
	pdrun |= (powerdownmask & PDRUNCFGMASKTMP);

	LPC_SYSCON->PDRUNCFG = (pdrun | PDRUNCFGUSEMASK);
}

/* Power up one or more blocks or peripherals */
void Chip_SYSCON_PowerUp(uint32_t powerupmask)
{
	uint32_t pdrun;

	pdrun = LPC_SYSCON->PDRUNCFG & PDRUNCFGMASKTMP;
	pdrun &= ~(powerupmask & PDRUNCFGMASKTMP);

	LPC_SYSCON->PDRUNCFG = (pdrun | PDRUNCFGUSEMASK);
}
