/*
 * @brief LPC11xx basic chip inclusion file
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

#ifndef __CHIP_H_
#define __CHIP_H_

#include "lpc_types.h"
#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CORE_M0
#error CORE_M0 is not defined for the LPC1125 architecture
#error CORE_M0 should be defined as part of your compiler define list
#endif

/* Peripheral mapping per device
   Peripheral	Address
   ----------	------------
   I2C			0x40000000
   WDT			0x40004000
   UART0		0x40008000
   UART1		0x40020000
   UART2		0x40024000
   TIMER0_16	0x4000C000
   TIMER1_16	0x40010000
   TIMER0_32	0x40014000
   TIMER1_32	0x40018000
   ADC			0x4001C000
   PMU			0x40038000
   FLASH_CTRL	0x4003C000
   SSP0			0x40040000
   IOCONF		0x40044000
   SYSCON		0x40048000
   SSP1			0x40058000
   GPIO_PIO0	0x50000000
   GPIO_PIO1	0x50010000
   GPIO_PIO2	0x50020000
   GPIO_PIO3	0x50030000
 */

/** @defgroup PERIPH_1125_BASE CHIP: LPC11xx Peripheral addresses and register set declarations
 * @ingroup CHIP_1125_Drivers
 * @{
 */

#define LPC_I2C_BASE              0x40000000
#define LPC_WWDT_BASE             0x40004000
#define LPC_UART0_BASE            0x40008000
#define LPC_UART1_BASE            0x40020000
#define LPC_UART2_BASE            0x40024000
#define LPC_TIMER16_0_BASE        0x4000C000
#define LPC_TIMER16_1_BASE        0x40010000
#define LPC_TIMER32_0_BASE        0x40014000
#define LPC_TIMER32_1_BASE        0x40018000
#define LPC_ADC_BASE              0x4001C000
#define LPC_PMU_BASE              0x40038000
#define LPC_FLASH_BASE            0x4003C000
#define LPC_SSP0_BASE             0x40040000
#define LPC_IOCON_BASE            0x40044000
#define LPC_SYSCON_BASE           0x40048000
#define LPC_SSP1_BASE             0x40058000
#define LPC_GPIO_PORT0_BASE       0x50000000
#define LPC_GPIO_PORT1_BASE       0x50010000
#define LPC_GPIO_PORT2_BASE       0x50020000
#define LPC_GPIO_PORT3_BASE       0x50030000

#define LPC_I2C                   ((LPC_I2C_T	*) LPC_I2C_BASE)
#define LPC_WWDT                  ((LPC_WWDT_T  *) LPC_WWDT_BASE)
#define LPC_UART0                 ((LPC_UART_T  *) LPC_UART0_BASE)
#define LPC_UART1                 ((LPC_UART_T  *) LPC_UART1_BASE)
#define LPC_UART2                 ((LPC_UART_T  *) LPC_UART2_BASE)
#define LPC_TIMER16_0             ((LPC_TIMER_T *) LPC_TIMER16_0_BASE)
#define LPC_TIMER16_1             ((LPC_TIMER_T *) LPC_TIMER16_1_BASE)
#define LPC_TIMER32_0             ((LPC_TIMER_T *) LPC_TIMER32_0_BASE)
#define LPC_TIMER32_1             ((LPC_TIMER_T *) LPC_TIMER32_1_BASE)
#define LPC_ADC                   ((LPC_ADC_T   *) LPC_ADC_BASE)
#define LPC_PMU                   ((LPC_PMU_T   *) LPC_PMU_BASE)
#define LPC_FMC                   ((LPC_FMC_T   *) LPC_FLASH_BASE)
#define LPC_SSP0                  ((LPC_SSP_T   *) LPC_SSP0_BASE)
#define LPC_IOCON                 ((LPC_IOCON_T *) LPC_IOCON_BASE)
#define LPC_SYSCON                ((LPC_SYSCON_T*) LPC_SYSCON_BASE)
#define LPC_SSP1                  ((LPC_SSP_T   *) LPC_SSP1_BASE)
#define LPC_GPIO                  ((LPC_GPIO_T  *) LPC_GPIO_PORT0_BASE)

/**
 * @}
 */

/** @ingroup CHIP_1125_DRIVER_OPTIONS
 * @{
 */

/**
 * @brief	System oscillator rate
 * This value is defined externally to the chip layer and contains
 * the value in Hz for the external oscillator for the board. If using the
 * internal oscillator, this rate can be 0.
 */
extern const uint32_t OscRateIn;

/**
 * @brief	Clock rate on the CLKIN pin
 * This value is defined externally to the chip layer and contains
 * the value in Hz for the CLKIN pin for the board. If this pin isn't used,
 * this rate can be 0.
 */
extern const uint32_t ExtRateIn;

/**
 * @}
 */

#include "i2c_112x.h"
#include "i2cm_112x.h"
#include "wwdt_112x.h"
#include "uart_112x.h"
#include "timer_112x.h"
#include "adc_112x.h"
#include "pmu_112x.h"
#include "fmc_112x.h"
#include "ssp_112x.h"
#include "iocon_112x.h"
#include "syscon_112x.h"
#include "clock_112x.h"
#include "gpio_112x.h"
#include "romapi_112x.h"


/* Common IRQ Handler Alias list */
#define UART0_IRQHanlder     UART_IRQHandler
#define I2C0_IRQHandler      I2C_IRQHandler
#define CMP_IRQHandler       ACMP_IRQHandler
#define WWDT_IRQHandler      WDT_IRQHandler

/** @defgroup SUPPORT_1125_FUNC CHIP: LPC11xx support functions
 * @ingroup CHIP_1125_Drivers
 * @{
 */

/**
 * @brief	Current system clock rate, mainly used for sysTick
 */
extern uint32_t SystemCoreClock;

/**
 * @brief	Update system core clock rate, should be called if the
 *			system has a clock rate change
 * @return	None
 */
void SystemCoreClockUpdate(void);

/**
 * @brief	Set up and initialize hardware prior to call to main()
 * @return	None
 * @note	Chip_SystemInit() is called prior to the application and sets up
 * system clocking prior to the application starting.
 */
void Chip_SystemInit(void);

/**
 * @brief	Clock and PLL initialization based on the external oscillator
 * @return	None
 * @note	This function assumes an external crystal oscillator
 * frequency of 12MHz.
 */
void Chip_SetupXtalClocking(void);

/**
 * @brief	Clock and PLL initialization based on the internal oscillator
 * @return	None
 */
void Chip_SetupIrcClocking(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_H_ */
