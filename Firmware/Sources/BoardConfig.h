// -----------------------------------------
// Board parameters
// ----------------------------------------

#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H

// Include
#include <ZwBase.h>

// Program build mode
//
#define BOOT_FROM_FLASH					// normal mode
//
#define RAM_CACHE_SPI_ABCD				// cache SPI-A(BCD) functions

// Board options
#define DSP28_2809							// on-board CPU
#define OSC_FRQ				(20MHz)			// on-board oscillator
#define CPU_FRQ_MHZ			100				// CPU frequency = 100MHz
#define CPU_FRQ				(CPU_FRQ_MHZ * 1000000L) 
#define SYS_HSP_FREQ		(CPU_FRQ / 2) 	// High-speed bus freq = 50MHz
#define SYS_LSP_FREQ		(CPU_FRQ / 4) 	// Low-speed bus freq = 50MHz
//
#define ZW_PWM_DUTY_BASE	1024

// Mode
//
// Select commutation mode
// define for CU_HV2
// undefine for CU_HV6
//#define COMM_MODE_2
#define COMM_MODE_4
//
// Select BVT configuration
// define if presented
// undefine if unrepresented
#define BVT_HP
// define if presented
// undefine if unrepresented
#undef BVT_LP
//
// Invert behavior of pressure sensing pin
// TRUE for PCB v.2.0
// FALSE for PCB v.2.1, v.2.2, v.2.4
#define PRESSURE_SEN_INVERT FALSE

// Peripheral options
#define HWUSE_SPI_D
#define HWUSE_SCI_B

// IO placement
#define SPI_D_QSEL			GPAQSEL1
#define SPI_D_MUX			GPAMUX1
#define SPI_D_SIMO			GPIO1	
#define SPI_D_SOMI			GPIO3		
#define SPI_D_CLK			GPIO5
#define SPI_D_CS			GPIO7
//
#define SCI_B_QSEL			GPAQSEL1
#define SCI_B_MUX			GPAMUX1
#define SCI_B_RX			GPIO11
#define SCI_B_TX			GPIO9
#define SCI_B_MUX_SELECTOR	2
//
#define IOE_OE				2
#define IOE_RCK				7
#define SAFETY_PIN			0
#define HW_SAFE_SW_PIN		25
#define PE_CTRL_PIN			4
#define PRESSURE_PIN		21
#define PIN_WD_RST			34
#define PIN_LED				26
#define CS_RELAY			14
#define SAFETY_CTRL1		19
#define SAFETY_CTRL2		23
#define SAFETY_CTRL3		22
#define SAFETY_CTRL4		20
//
#define MOSFET_P6			3
#define MOSFET_P8			6
#define MOSFET_P11			8
#define MOSFET_P13			10


#endif // __BOARD_CONFIG_H
