#This file is generated by VisualGDB.
#It contains GCC settings automatically derived from the board support package (BSP).
#DO NOT EDIT MANUALLY. THE FILE WILL BE OVERWRITTEN. 
#Use VisualGDB Project Properties dialog or modify Makefile or per-configuration .mak files instead.

#VisualGDB provides BSP_ROOT and TOOLCHAIN_ROOT via environment when running Make. The line below will only be active if GNU Make is started manually.
BSP_ROOT ?= ../../EmbeddedBSPs
EFP_BASE ?= $(LOCALAPPDATA)/VisualGDB/EmbeddedEFPs
TOOLCHAIN_ROOT ?= C:/SysGCC/arm-eabi

#Embedded toolchain
CC := $(TOOLCHAIN_ROOT)/bin/arm-eabi-gcc.exe
CXX := $(TOOLCHAIN_ROOT)/bin/arm-eabi-g++.exe
LD := $(CXX)
AR := $(TOOLCHAIN_ROOT)/bin/arm-eabi-ar.exe
OBJCOPY := $(TOOLCHAIN_ROOT)/bin/arm-eabi-objcopy.exe

#Additional flags
PREPROCESSOR_MACROS += ARM_MATH_CM0 CHIP_LPC11CXX CORE_M0 flash_layout LPC11C24
INCLUDE_DIRS += $(BSP_ROOT)/LPC11xx/lpc_chip/CMSIS/CMSIS/Include $(BSP_ROOT)/LPC11xx/lpc_chip/CMSIS/CMSIS/RTOS $(BSP_ROOT)/LPC11xx/lpc_chip/lpcusbsio $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_110x $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_1125 $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_11axx $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_11cxx $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_11exx $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_11uxx $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_11xx/config_11xxlv $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/chip_common $(BSP_ROOT)/LPC11xx/lpc_chip/lpc_chip/usbd_rom $(BSP_ROOT)/Common
LIBRARY_DIRS += 
LIBRARY_NAMES += 
ADDITIONAL_LINKER_INPUTS += 
MACOS_FRAMEWORKS += 
LINUX_PACKAGES += 

CFLAGS += 
CXXFLAGS += 
ASFLAGS += 
LDFLAGS += --specs=nano.specs 
COMMONFLAGS += -mcpu=cortex-m0 -mthumb
LINKER_SCRIPT := $(BSP_ROOT)/LPC11xx/LinkerScripts/LPC11C24_flash.lds

