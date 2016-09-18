/*
 * @brief LPC1125 System Control registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2015
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

#ifndef __SYSCON_1125_H_
#define __SYSCON_1125_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SYSCON_1125 CHIP: LPC1125 System Control block driver
 * @ingroup CHIP_1125_Drivers
 * @{
 */

/**
 * @brief LPC1125 System Control block structure
 */
typedef struct {					/*!< SYSCON Structure */
	__IO uint32_t  SYSMEMREMAP;		/*!< System Memory remap register */
	__IO uint32_t  PRESETCTRL;		/*!< Peripheral reset Control register */
	__IO uint32_t  SYSPLLCTRL;		/*!< System PLL control register */
	__I  uint32_t  SYSPLLSTAT;		/*!< System PLL status register */
	__I  uint32_t  RESERVED1[4];
	__IO uint32_t  SYSOSCCTRL;		/*!< System Oscillator control register */
	__IO uint32_t  WDTOSCCTRL;		/*!< Watchdog Oscillator control register */
	__IO uint32_t  IRCCTRL;			/*!< IRC control register, not on LPC11UXX and LPC11EXX */
	__IO uint32_t  RESERVED2;		/*!< LF oscillator control, LPC11AXX only */
	__IO uint32_t  SYSRSTSTAT;		/*!< System Reset Status register           */
	__I  uint32_t  RESERVED3[3];
	__IO uint32_t  SYSPLLCLKSEL;	/*!< System PLL clock source select register */
	__IO uint32_t  SYSPLLCLKUEN;	/*!< System PLL clock source update enable register*/
	__I  uint32_t  RESERVED4[10];
	__IO uint32_t  MAINCLKSEL;		/*!< Main clock source select register		*/
	__IO uint32_t  MAINCLKUEN;		/*!< Main clock source update enable register	*/
	__IO uint32_t  SYSAHBCLKDIV;	/*!< System Clock divider register */
	__I  uint32_t  RESERVED5;
	__IO uint32_t  SYSAHBCLKCTRL;	/*!< System clock control register */
	__I  uint32_t  RESERVED6[4];
	__IO uint32_t  SSP0CLKDIV;		/*!< SSP0 clock divider register   */
	__IO uint32_t  UART0CLKDIV;		/*!< UART #0 clock divider register   */
	__IO uint32_t  SSP1CLKDIV;		/*!< SSP1 clock divider register, not on CHIP_LPC110X, CHIP_LPC11XXLV */
	__IO uint32_t  UART1CLKDIV;		/*!< UART #1 clock divider register   */
	__IO uint32_t  UART2CLKDIV;		/*!< UART #2 clock divider register   */
	__I  uint32_t  RESERVED7[10];
	__IO uint32_t  WDTCLKSEL;		/*!< WDT clock source select register, some parts only */
	__IO uint32_t  WDTCLKUEN;		/*!< WDT clock source update enable register, some parts only */
	__IO uint32_t  WDTCLKDIV;		/*!< WDT clock divider register, some parts only */
	__I  uint32_t  RESERVED8;	
	__IO uint32_t  CLKOUTSEL;		/*!< Clock out source select register, not on LPC1102/04 */
	__IO uint32_t  CLKOUTUEN;		/*!< Clock out source update enable register, not on LPC1102/04 */
	__IO uint32_t  CLKOUTDIV;		/*!< Clock out divider register, not on LPC1102/04 */
	__I  uint32_t  RESERVED9[5];
	__I  uint32_t  PIOPORCAP[2];	/*!< POR captured PIO status registers, index 1 on LPC1102/04 */
	__I  uint32_t  RESERVED10[18];
	__IO uint32_t  BODCTRL;			/*!< Brown Out Detect register */
	__IO uint32_t  SYSTCKCAL;		/*!< System tick counter calibration register */
	__I  uint32_t  RESERVED11[6];
	__IO uint32_t  IRQLATENCY;		/*!< IRQ delay register, on LPC11UXX and LPC11EXX only */
	__IO uint32_t  NMISRC;			/*!< NMI source control register,some parts only */
	__IO uint32_t  RESERVED12[34];
	__IO uint32_t  STARTAPRP0;		/*!< Start logic 0 interrupt wake up enable register 0, on CHIP_LPC110X, CHIP_LPC11XXLV, CHIP_LPC11CXX */
	__IO uint32_t  STARTERP0;		/*!< Start logic signal enable register 0, not on LPC11AXX */
	__IO uint32_t  STARTRSRP0CLR;	/*!< Start logic reset register 0, on CHIP_LPC110X, CHIP_LPC11XXLV, CHIP_LPC11CXX */
	__IO uint32_t  STARTSRP0;		/*!< Start logic status register 0, on CHIP_LPC110X, CHIP_LPC11XXLV, CHIP_LPC11CXX */
	__I  uint32_t  RESERVED13[8];
	__IO uint32_t  PDSLEEPCFG;		/*!< Power down states in deep sleep mode register, not on LPC11AXX */
	__IO uint32_t  PDWAKECFG;		/*!< Power down states in wake up from deep sleep register, not on LPC11AXX */
	__IO uint32_t  PDRUNCFG;		/*!< Power configuration register*/
} LPC_SYSCON_T;

/**
 * System memory remap modes used to remap interrupt vectors
 */
typedef enum CHIP_SYSCON_BOOT_MODE_REMAP {
	REMAP_BOOT_LOADER_MODE,	/*!< Interrupt vectors are re-mapped to Boot ROM */
	REMAP_USER_RAM_MODE,	/*!< Interrupt vectors are re-mapped to Static RAM */
	REMAP_USER_FLASH_MODE	/*!< Interrupt vectors are not re-mapped and reside in Flash */
} CHIP_SYSCON_BOOT_MODE_REMAP_T;

/**
 * @brief	Re-map interrupt vectors
 * @param	remap	: system memory map value
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_Map(CHIP_SYSCON_BOOT_MODE_REMAP_T remap)
{
	LPC_SYSCON->SYSMEMREMAP = (uint32_t) remap;
}

/**
 * Peripheral reset identifiers, not available on all devices
 */
typedef enum {
	RESET_SSP0,			/*!< SSP0 reset control */
	RESET_I2C0,			/*!< I2C0 reset control */
	RESET_SSP1,			/*!< SSP1 reset control */
} CHIP_SYSCON_PERIPH_RESET_T;

/**
 * @brief	Assert reset for a peripheral
 * @param	periph	: Peripheral to assert reset for
 * @return	Nothing
 * @note	The peripheral will stay in reset until reset is de-asserted. Call
 * Chip_SYSCON_DeassertPeriphReset() to de-assert the reset.
 */
STATIC INLINE void Chip_SYSCON_AssertPeriphReset(CHIP_SYSCON_PERIPH_RESET_T periph)
{
	LPC_SYSCON->PRESETCTRL &= ~(1 << (uint32_t) periph);
}

/**
 * @brief	De-assert reset for a peripheral
 * @param	periph	: Peripheral to de-assert reset for
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_DeassertPeriphReset(CHIP_SYSCON_PERIPH_RESET_T periph)
{
	LPC_SYSCON->PRESETCTRL |= (1 << (uint32_t) periph);
}

/**
 * @brief	Resets a peripheral
 * @param	periph	:	Peripheral to reset
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_PeriphReset(CHIP_SYSCON_PERIPH_RESET_T periph)
{
	Chip_SYSCON_AssertPeriphReset(periph);
	Chip_SYSCON_DeassertPeriphReset(periph);
}

/**
 * System reset status
 */
#define SYSCON_RST_POR    (1 << 0)	/*!< POR reset status */
#define SYSCON_RST_EXTRST (1 << 1)	/*!< External reset status */
#define SYSCON_RST_WDT    (1 << 2)	/*!< Watchdog reset status */
#define SYSCON_RST_BOD    (1 << 3)	/*!< Brown-out detect reset status */
#define SYSCON_RST_SYSRST (1 << 4)	/*!< software system reset status */

/**
 * Non-Maskable Interrupt Enable/Disable value
 */
#define SYSCON_NMISRC_ENABLE   ((uint32_t) 1 << 31)	/*!< Enable the Non-Maskable Interrupt (NMI) source */

/**
 * @brief	Get system reset status
 * @return	An Or'ed value of SYSCON_RST_*
 * @note	This function returns the detected reset source(s).
 */
STATIC INLINE uint32_t Chip_SYSCON_GetSystemRSTStatus(void)
{
	return LPC_SYSCON->SYSRSTSTAT;
}

/**
 * @brief	Clear system reset status
 * @param	reset	: An Or'ed value of SYSCON_RST_* status to clear
 * @return	Nothing
 * @note	This function returns the detected reset source(s).
 */
STATIC INLINE void Chip_SYSCON_ClearSystemRSTStatus(uint32_t reset)
{
	LPC_SYSCON->SYSRSTSTAT = reset;
}

/**
 * @brief	Read POR captured PIO status
 * @param	index	: POR register index, 0 or 1
 * @return	captured POR PIO status
 * @note	Some devices only support index 0.
 */
STATIC INLINE uint32_t Chip_SYSCON_GetPORPIOStatus(int index)
{
	return LPC_SYSCON->PIOPORCAP[index];
}

/**
 * Brown-out detector reset level
 */
typedef enum CHIP_SYSCON_BODRSTLVL {
	SYSCON_BODRSTLVL_1_46V,	/*!< Brown-out reset at 1.46v */
	SYSCON_BODRSTLVL_2_06V,	/*!< Brown-out reset at 2.06v */
	SYSCON_BODRSTLVL_2_35V,	/*!< Brown-out reset at 2.35v */
	SYSCON_BODRSTLVL_2_63V,	/*!< Brown-out reset at 2.63v */
} CHIP_SYSCON_BODRSTLVL_T;

/**
 * Brown-out detector interrupt level
 */
typedef enum CHIP_SYSCON_BODRINTVAL {
	SYSCON_BODINTVAL_RESERVED1,
	SYSCON_BODINTVAL_2_22V,	/*!< Brown-out interrupt at 2.22v */
	SYSCON_BODINTVAL_2_52V,	/*!< Brown-out interrupt at 2.52v */
	SYSCON_BODINTVAL_2_80V,	/*!< Brown-out interrupt at 2.8v */
} CHIP_SYSCON_BODRINTVAL_T;

/**
 * @brief	Set brown-out detection interrupt and reset levels
 * @param	rstlvl	: Brown-out detector reset level
 * @param	intlvl	: Brown-out interrupt level
 * @return	Nothing
 * @note	Brown-out detection reset will be disabled upon exiting this function.
 * Use Chip_SYSCON_EnableBODReset() to re-enable.
 */
STATIC INLINE void Chip_SYSCON_SetBODLevels(CHIP_SYSCON_BODRSTLVL_T rstlvl,
											CHIP_SYSCON_BODRINTVAL_T intlvl)
{
	LPC_SYSCON->BODCTRL = ((uint32_t) rstlvl) | (((uint32_t) intlvl) << 2);
}

/**
 * @brief	Enable brown-out detection reset
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_EnableBODReset(void)
{
	LPC_SYSCON->BODCTRL |= (1 << 4);
}

/**
 * @brief	Disable brown-out detection reset
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_DisableBODReset(void)
{
	LPC_SYSCON->BODCTRL &= ~(1 << 4);
}


/**
 * @brief	Set System tick timer calibration value
 * @param	sysCalVal	: System tick timer calibration value
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_SetSYSTCKCAL(uint32_t sysCalVal)
{
	LPC_SYSCON->SYSTCKCAL = sysCalVal;
}

/**
 * @brief	Set System IRQ latency
 * @param	latency	: Latency in clock ticks
 * @return	Nothing
 * @note	Sets the IRQ latency, a value between 0 and 255 clocks. Lower
 * values allow better latency.
 */
STATIC INLINE void Chip_SYSCON_SetIRQLatency(uint32_t latency)
{
	LPC_SYSCON->IRQLATENCY = latency;
}

/**
 * @brief	Get System IRQ latency
 * @return	Latency in clock ticks
 */
STATIC INLINE uint32_t Chip_SYSCON_GetIRQLatency(void)
{
	return LPC_SYSCON->IRQLATENCY;
}

/**
 * @brief	Set source for non-maskable interrupt (NMI)
 * @param	intsrc	: IRQ number to assign to the NMI
 * @return	Nothing
 * @note	The NMI source will be disabled upon exiting this function. use the
 * Chip_SYSCON_EnableNMISource() function to enable the NMI source.
 */
STATIC INLINE void Chip_SYSCON_SetNMISource(uint32_t intsrc)
{
	LPC_SYSCON->NMISRC = intsrc;
}

/**
 * @brief	Enable interrupt used for NMI source
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_EnableNMISource(void)
{
	LPC_SYSCON->NMISRC |= SYSCON_NMISRC_ENABLE;
}

/**
 * @brief	Disable interrupt used for NMI source
 * @return	Nothing
 */
STATIC INLINE void Chip_SYSCON_DisableNMISource(void)
{
	LPC_SYSCON->NMISRC &= ~(SYSCON_NMISRC_ENABLE);
}

/**
 * @brief	Set edge for PIO start logic
 * @param	pin		: PIO pin number
 * @param	edge	: 0 for falling edge, 1 for rising edge
 * @return	Nothing
 * @note	Different devices support different pins, see the user manual for supported pins.
 */
STATIC INLINE void Chip_SYSCON_SetStartPin(uint32_t pin, uint32_t edge)
{
	if (edge) {
		LPC_SYSCON->STARTAPRP0 |= (1 << pin);
	}
	else {
		LPC_SYSCON->STARTAPRP0 &= ~(1 << pin);
	}
}

/**
 * @brief	Enable PIO start logic for a pin
 * @param	pin	: PIO pin number
 * @return	Nothing
 * @note	Different devices support different pins, see the user manual for supported pins.
 */
STATIC INLINE void Chip_SYSCON_EnableStartPin(uint32_t pin)
{
	LPC_SYSCON->STARTERP0 |= (1 << pin);
}

/**
 * @brief	Disable PIO start logic for a pin
 * @param	pin	: PIO pin number
 * @return	Nothing
 * @note	Different devices support different pins, see the user manual for supported pins.
 */
STATIC INLINE void Chip_SYSCON_DisableStartPin(uint32_t pin)
{
	LPC_SYSCON->STARTERP0 &= ~(1 << pin);
}

/**
 * @brief	Clear PIO start logic state
 * @param	pin	: PIO pin number
 * @return	Nothing
 * @note	Different devices support different pins, see the user manual for supported pins.
 */
STATIC INLINE void Chip_SYSCON_ResetStartPin(uint32_t pin)
{
	LPC_SYSCON->STARTRSRP0CLR = (1 << pin);
}

/**
 * @brief	Returns status of pin wakeup
 * @param	pin	: PIO pin number
 * @return	true if a pin start signal is pending, otherwise false
 * @note	Different devices support different pins, see the user manual for supported pins.
 */
STATIC INLINE bool Chip_SYSCON_GetStartPinStatus(uint32_t pin)
{
	return (bool) ((LPC_SYSCON->STARTSRP0 & (1 << pin)) != 0);
}

/**
 * Deep sleep setup values
 */
#define SYSCON_DEEPSLP_BOD_PD    (1 << 3)	/*!< BOD power-down control in Deep-sleep mode, powered down */
#define SYSCON_DEEPSLP_WDTOSC_PD (1 << 6)	/*!< Watchdog oscillator power control in Deep-sleep, powered down */

/**
 * @brief	Setup deep sleep behaviour for power down
 * @param	sleepmask	: OR'ed values of SYSCON_DEEPSLP_* values (high to powerdown on deepsleep)
 * @return	Nothing
 * @note	This must be setup prior to using deep sleep. See the user manual
 ****(PDSLEEPCFG register) for more info on setting this up. This function selects
 * which peripherals are powered down on deep sleep.
 * This function should only be called once with all options for power-down
 * in that call.
 */
void Chip_SYSCON_SetDeepSleepPD(uint32_t sleepmask);

/**
 * @brief	Returns current deep sleep mask
 * @return	OR'ed values of SYSCON_DEEPSLP_* values
 * @note	A high bit indicates the peripheral will power down on deep sleep.
 */
STATIC INLINE uint32_t Chip_SYSCON_GetDeepSleepPD(void)
{
	return LPC_SYSCON->PDSLEEPCFG;
}

/**
 * Deep sleep to wakeup setup values
 */
#define SYSCON_SLPWAKE_IRCOUT_PD (1 << 0)	/*!< IRC oscillator output wake-up configuration */
#define SYSCON_SLPWAKE_IRC_PD    (1 << 1)	/*!< IRC oscillator power-down wake-up configuration */
#define SYSCON_SLPWAKE_FLASH_PD  (1 << 2)	/*!< Flash wake-up configuration */
#define SYSCON_SLPWAKE_BOD_PD    (1 << 3)	/*!< BOD wake-up configuration */
#define SYSCON_SLPWAKE_ADC_PD    (1 << 4)	/*!< ADC wake-up configuration */
#define SYSCON_SLPWAKE_SYSOSC_PD (1 << 5)	/*!< System oscillator wake-up configuration */
#define SYSCON_SLPWAKE_WDTOSC_PD (1 << 6)	/*!< Watchdog oscillator wake-up configuration */
#define SYSCON_SLPWAKE_SYSPLL_PD (1 << 7)	/*!< System PLL wake-up configuration */

/**
 * @brief	Setup wakeup behaviour from deep sleep
 * @param	wakeupmask	: OR'ed values of SYSCON_SLPWAKE_* values (high is powered down)
 * @return	Nothing
 * @note	This must be setup prior to using deep sleep. See the user manual
 * (PDWAKECFG register) for more info on setting this up. This function selects
 * which peripherals are powered up on exit from deep sleep.
 * This function should only be called once with all options for wakeup
 * in that call.
 */
void Chip_SYSCON_SetWakeup(uint32_t wakeupmask);

/**
 * @brief	Return current wakeup mask
 * @return	OR'ed values of SYSCON_SLPWAKE_* values
 * @note	A high state indicates the peripehral will powerup on wakeup.
 */
STATIC INLINE uint32_t Chip_SYSCON_GetWakeup(void)
{
	return LPC_SYSCON->PDWAKECFG;
}

/**
 * Power down configuration values
 */
#define SYSCON_POWERDOWN_IRCOUT_PD (1 << 0)	/*!< IRC oscillator output power down */
#define SYSCON_POWERDOWN_IRC_PD    (1 << 1)	/*!< IRC oscillator power-down */
#define SYSCON_POWERDOWN_FLASH_PD  (1 << 2)	/*!< Flash power down */
#define SYSCON_POWERDOWN_BOD_PD    (1 << 3)	/*!< BOD power down */
#define SYSCON_POWERDOWN_ADC_PD    (1 << 4)	/*!< ADC power down */
#define SYSCON_POWERDOWN_SYSOSC_PD (1 << 5)	/*!< System oscillator power down */
#define SYSCON_POWERDOWN_WDTOSC_PD (1 << 6)	/*!< Watchdog oscillator power down */
#define SYSCON_POWERDOWN_SYSPLL_PD (1 << 7)	/*!< System PLL power down */

/**
 * @brief	Power down one or more blocks or peripherals
 * @param	powerdownmask	: OR'ed values of SYSCON_POWERDOWN_* values
 * @return	Nothing
 */
void Chip_SYSCON_PowerDown(uint32_t powerdownmask);

/**
 * @brief	Power up one or more blocks or peripherals
 * @param	powerupmask	: OR'ed values of SYSCON_POWERDOWN_* values
 * @return	Nothing
 */
void Chip_SYSCON_PowerUp(uint32_t powerupmask);

/**
 * @brief	Get power status
 * @return	OR'ed values of SYSCON_POWERDOWN_* values
 * @note	A high state indicates the peripheral is powered down.
 */
STATIC INLINE uint32_t Chip_SYSCON_GetPowerStates(void)
{
	return LPC_SYSCON->PDRUNCFG;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*!< __SYSCON_1125_H_ */
