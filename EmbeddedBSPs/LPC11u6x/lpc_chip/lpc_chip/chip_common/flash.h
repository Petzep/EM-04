/*
 * @brief Common FLASH support functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
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

#ifndef __FLASH_H_
#define __FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

// FIXME - Needs review for API and result[]

/** @defgroup COMMON_FLASH CHIP: Common Chip FLASH commands
 * @ingroup CHIP_Common
 * @{
 */

/**
 * @brief	Prepare sector for write operation
 * @param	strSector	: Start sector number
 * @param	endSector	: End sector number
 * @return	Status code to indicate the command is executed successfully or not
 * @note	This command must be executed before executing "Copy RAM to flash"
 *			or "Erase Sector" command.
 *			The end sector must be greater than or equal to start sector number
 */
uint8_t Chip_FLASH_PreSectorForReadWrite(uint32_t strSector, uint32_t endSector);

/**
 * @brief	Copy RAM to flash
 * @param	dstAdd		: Destination flash address where data bytes are to be written
 * @param	srcAdd		: Source flash address where data bytes are to be read
 * @param	byteswrt	: Number of bytes to be written
 * @return	Status code to indicate the command is executed successfully or not
 * @note	The addresses should be a 256 byte boundary and the number of bytes
 *			should be 256 | 512 | 1024 | 4096
 */
uint8_t Chip_FLASH_CopyRamToFlash(uint32_t dstAdd, uint32_t *srcAdd, uint32_t byteswrt);

/**
 * @brief	Erase sector
 * @param	strSector	: Start sector number
 * @param	endSector	: End sector number
 * @return	Status code to indicate the command is executed successfully or not
 * @note	The end sector must be greater than or equal to start sector number
 */
uint8_t Chip_FLASH_EraseSector(uint32_t strSector, uint32_t endSector);

/**
 * @brief Blank check a sector or multiples sector of on-chip flash memory
 * @param	strSector	: Start sector number
 * @param	endSector	: End sector number
 * @return	Offset of the first non blank word location if the status code is SECTOR_NOT_BLANK
 * @note	The end sector must be greater than or equal to start sector number
 */
// FIXME - There are two return value (result[0] & result[1]
// Result0:Offset of the first non blank word location if the Status Code is
// SECTOR_NOT_BLANK.
// Result1:Contents of non blank word location.
uint8_t Chip_FLASH_BlankCheckSector(uint32_t strSector, uint32_t endSector);

/**
 * @brief	Read part identification number
 * @return	Part identification number
 */
uint32_t Chip_FLASH_ReadPID(void);

/**
 * @brief	Read boot code version number
 * @return	Boot code version number
 */
uint8_t Chip_FLASH_ReadBootCode(void);

/**
 * @brief	Compare the memory contents at two locations
 * @param	dstAdd		: Destination of the RAM address of data bytes to be compared
 * @param	srcAdd		: Source of the RAM address of data bytes to be compared
 * @param	bytescmp	: Number of bytes to be compared
 * @return	Offset of the first mismatch of the status code is COMPARE_ERROR
 * @note	The addresses should be a word boundary and number of bytes should be
 *			a multiply of 4
 */
uint8_t Chip_FLASH_Compare(uint32_t dstAdd, uint32_t srcAdd, uint32_t bytescmp);

/**
 * @brief	IAP reinvoke ISP to invoke the bootloader in ISP mode
 * @return	none
 */
uint8_t Chip_FLASH_ReinvokeISP(void);

/**
 * @brief	Read the unique ID
 * @return	Status code to indicate the command is executed successfully or not
 */
uint32_t Chip_FLASH_ReadUID(void);

/**
 * @brief	Erase a page or multiple papers of on-chip flash memory
 * @param	strPage	: Start page number
 * @param	endPage	: End page number
 * @return	Status code to indicate the command is executed successfully or not
 * @note	The page number must be greater than or equal to start page number
 */
// FIXME - There are four return value
// Result0:The first 32-bit word (at the lowest address)
// Result1:The second 32-bit word.
// Result2:The third 32-bit word.
// Result3:The fourth 32-bit word.
uint8_t Chip_FLASH_ErasePage(uint32_t strPage, uint32_t endPage);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __FLASH_H_ */
