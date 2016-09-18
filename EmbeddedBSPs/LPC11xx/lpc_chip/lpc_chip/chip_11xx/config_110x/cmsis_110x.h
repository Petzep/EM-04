/*
 * @brief Basic CMSIS include file for LPC110X
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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

#ifndef __CMSIS_110X_H_
#define __CMSIS_110X_H_

#include "lpc_types.h"
#include "sys_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CMSIS_110X CHIP: LPC110x CMSIS include file
 * @ingroup CHIP_11XX_CMSIS_Drivers
 * Applies to LPC1102 and LPC1104 devices.
 * @{
 */

#if defined(__ARMCC_VERSION)
// Kill warning "#pragma push with no matching #pragma pop"
  #pragma diag_suppress 2525
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
//  #pragma push // FIXME not usable for IAR
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
#if !defined(CHIP_LPC110X)
#error Incorrect or missing device variant (CHIP_LPC110X)
#endif

/** @defgroup CMSIS_110X_IRQ CHIP_110X: LPC1102/1104 peripheral interrupt numbers
 * @{
 */

typedef enum LPC110X_IRQn {
	NonMaskableInt_IRQn           = -14,	/*!< 2 Non Maskable Interrupt                           */
	HardFault_IRQn                = -13,	/*!< 3 Cortex-M0 Hard Fault Interrupt                   */
	SVCall_IRQn                   = -5,		/*!< 11 Cortex-M0 SV Call Interrupt                     */
	PendSV_IRQn                   = -2,		/*!< 14 Cortex-M0 Pend SV Interrupt                     */
	SysTick_IRQn                  = -1,		/*!< 15 Cortex-M0 System Tick Interrupt                 */

	PIO0_0_IRQn                   = 0,		/*!< GPIO port 0, pin 0 Interrupt                      */
	RESERVED1_IRQn                = 1,
	RESERVED2_IRQn                = 2,
	RESERVED3_IRQn                = 3,
	RESERVED4_IRQn                = 4,
	RESERVED5_IRQn                = 5,
	RESERVED6_IRQn                = 6,
	RESERVED7_IRQn                = 7,
	PIO0_8_IRQn                   = 8,		/*!< GPIO port 0, pin 8 Interrupt                      */
	PIO0_9_IRQn                   = 9,		/*!< GPIO port 0, pin 9 Interrupt                      */
	PIO0_10_IRQn                  = 10,		/*!< GPIO port 0, pin 10 Interrupt                     */
	PIO0_11_IRQn                  = 11,		/*!< GPIO port 0, pin 11 Interrupt                     */
	PIO1_0_IRQn                   = 12,		/*!< GPIO port 1, pin 0 Interrupt                      */
	RESERVED13_IRQn               = 13,
	RESERVED14_IRQn               = 14,
	RESERVED15_IRQn               = 15,
	TIMER_16_0_IRQn               = 16,		/*!< 16-bit Timer0 Interrupt                          */
	TIMER_16_1_IRQn               = 17,		/*!< 16-bit Timer1 Interrupt                          */
	TIMER_32_0_IRQn               = 18,		/*!< 32-bit Timer0 Interrupt                          */
	TIMER_32_1_IRQn               = 19,		/*!< 32-bit Timer1 Interrupt                          */
	SSP0_IRQn                     = 20,		/*!< SSP0 Interrupt                                   */
	UART0_IRQn                    = 21,		/*!< UART Interrupt                                   */
	RESERVED22_IRQn               = 22,
	RESERVED23_IRQn               = 23,
	ADC_IRQn                      = 24,		/*!< A/D Converter Interrupt                          */
	WDT_IRQn                      = 25,		/*!< Watchdog timer Interrupt                         */
	BOD_IRQn                      = 26,		/*!< Brown Out Detect(BOD) Interrupt                  */
	RESERVED27_IRQn               = 27,
	RESERVED28_IRQn               = 28,
	RESERVED29_IRQn               = 29,
	PIO1_IRQn                     = 30,		/*!< GPIO interrupt status of port 1 */
	PIO0_IRQn                     = 31,		/*!< GPIO interrupt status of port 0 */
} LPC110X_IRQn_Type;

/**
 * @}
 */

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/** @defgroup CMSIS_110X_COMMON CHIP: LPC110x Cortex CMSIS definitions
 * @{
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT             0			/*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          2			/*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0			/*!< Set to 1 if different SysTick Config is used     */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CMSIS_110X_H_ */
