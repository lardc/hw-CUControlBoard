// -----------------------------------------
// System parameters
// ----------------------------------------

#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

// Include
#include <ZwBase.h>
#include <BoardConfig.h>

// CPU & System
//--------------------------------------------------------
#define CPU_PLL				10          // OSCCLK * PLL div 2 = CPUCLK: 20 * 10 / 2 = 100
#define CPU_CLKINDIV		0           // "div 2" in previous equation
#define SYS_HISPCP       	0x01   		// SYSCLKOUT / 2
#define SYS_LOSPCP       	0x02    	// SYSCLKOUT / 4
//--------------------------------------------------------

// Boot-loader
//--------------------------------------------------------
#define BOOT_LOADER_REQUEST	0xABCD
//--------------------------------------------------------

// Power control
//--------------------------------------------------------
#define SYS_PUMOD			ZW_POWER_SPID_CLK | \
							ZW_POWER_CANA_CLK | ZW_POWER_SCIB_CLK

#define SYS_WD_PRESCALER	0x07
//--------------------------------------------------------

// GPIO
//--------------------------------------------------------
// Input filters
#define GPIO_TSAMPLE		0xFF		// T[sample_A] = (1/ 100MHz) * (2 * 255) = 5.1 uS
#define GPIO_NSAMPLE		6			// 6 samples: T = 5.1uS * 6 = 31 uS

// Flash
//--------------------------------------------------------
#define FLASH_FWAIT			3
#define FLASH_OTPWAIT		5
//--------------------------------------------------------

// TIMERs
//--------------------------------------------------------
#define CS_MONITORING_FREQ	1000		// 1000 Hz
#define TIMER2_PERIOD		(1000000L / CS_MONITORING_FREQ)

#define DBG_FREQ			2			// 2 Hz
#define DBG_COUNTER_PERIOD	(CS_MONITORING_FREQ / (DBG_FREQ * 2))
//--------------------------------------------------------

// IO Expansion
//--------------------------------------------------------
#define IOE_BAUDRATE		1562500L	// SPI clock = 1.5625 MHz
#define IOE_PLR				FALSE		// CLK low in idle state (SPI MODE 0)		
#define IOE_PHASE			TRUE		// data output on rising edge (SPI MODE 0)
//--------------------------------------------------------

// CAN-A
//--------------------------------------------------------
#define CANA_BR				1000000L
#define CANA_BRP			9
#define CANA_TSEG1			6
#define CANA_TSEG2			1
#define CANA_SJW			1
//--------------------------------------------------------

// SCI-B
//--------------------------------------------------------
#define SCIB_BR				115200L
#define SCIB_DB				8
#define SCIB_SB				FALSE
#define SCIB_PARITY			ZW_PAR_NONE
//--------------------------------------------------------

#endif // __SYSCONFIG_H
