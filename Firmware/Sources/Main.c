// ----------------------------------------
// Program entry point
// ----------------------------------------

// Include
#include <stdinc.h>
//
#include "ZwDSP.h"
#include "ZbBoard.h"
//
#include "SysConfig.h"
//
#include "Controller.h"
#include "Flash.h"

// FORWARD FUNCTIONS
// ----------------------------------------
Boolean InitializeCPU();
void InitializeTimers();
void InitializeSPI();
void InitializeSCI();
void InitializeCAN();
void InitializeBoard();
void InitializeController();
// ----------------------------------------

// FORWARD ISRs
// ----------------------------------------
// CPU Timer 2 ISR
ISRCALL Timer2_ISR();
// CAN Line 0 ISR
ISRCALL CAN0_ISR();
// ILLEGAL ISR
ISRCALL IllegalInstruction_ISR();
// ----------------------------------------

// FUNCTIONS
// ----------------------------------------
// Program main function
void main()
{
	// Boot process
	InitializeCPU();
	FLASH_Init();

	// Init peripheral modules
	InitializeTimers();
	InitializeSPI();
	InitializeSCI();
	InitializeCAN();
	InitializeBoard();

	// Setup ISRs
	BEGIN_ISR_MAP
		ADD_ISR(TINT2, Timer2_ISR);
		ADD_ISR(ECAN0INTA, CAN0_ISR);
		ADD_ISR(ILLEGAL, IllegalInstruction_ISR);
	END_ISR_MAP
	
	// Initialize controller logic
	InitializeController();

	// Enable interrupts
	EINT;
	ERTM;

	// Set watch-dog as WDRST
	ZwSystem_EnableDog(SYS_WD_PRESCALER);

	// Start timers
	ZwTimer_StartT2();
	
	// Background cycle
	while(TRUE)
		CONTROL_Idle();
}
// ----------------------------------------

// Initialize and prepare DSP
Boolean InitializeCPU()
{
    Boolean clockInitResult;

	// Init clock and peripherals
    clockInitResult = ZwSystem_Init(CPU_PLL, CPU_CLKINDIV, SYS_LOSPCP, SYS_HISPCP, SYS_PUMOD);

    if(clockInitResult)
    {
		// Do default GPIO configuration
		ZwGPIO_Init(GPIO_TSAMPLE, GPIO_TSAMPLE, GPIO_TSAMPLE, GPIO_TSAMPLE, GPIO_TSAMPLE);
		// Initialize PIE
		ZwPIE_Init();
		// Prepare PIE vectors
		ZwPIE_Prepare();
    }

	// Config flash
	ZW_FLASH_CODE_SHADOW;
	ZW_FLASH_OPTIMIZE(FLASH_FWAIT, FLASH_OTPWAIT);

   	return clockInitResult;
}
// ----------------------------------------

// Initialize CPU timers
void InitializeTimers()
{
    ZwTimer_InitT2();
 	ZwTimer_SetT2(TIMER2_PERIOD);
	ZwTimer_EnableInterruptsT2(TRUE);
}
// ----------------------------------------

// Initialize and prepare SCI modules
void InitializeSCI()
{
	// Initialize and prepare SCI modules
	ZwSCIb_Init(SCIB_BR, SCIB_DB, SCIB_PARITY, SCIB_SB, FALSE);
	ZwSCIb_InitFIFO(16, 0);
	ZwSCIb_EnableInterrupts(FALSE, FALSE);

	ZwSCI_EnableInterruptsGlobal(FALSE);
}
// ----------------------------------------

void InitializeSPI()
{
	// Common (ABCD)
	ZwSPI_EnableInterruptsGlobal(FALSE);
}
// ----------------------------------------

void InitializeCAN()
{
	// Init CAN
	ZwCANa_Init(CANA_BR, CANA_BRP, CANA_TSEG1, CANA_TSEG2, CANA_SJW);

	// Register system handler
	ZwCANa_RegisterSysEventHandler(&CONTROL_NotifyCANFault);

    // Allow interrupts for CAN
    ZwCANa_InitInterrupts(TRUE);
    ZwCANa_EnableInterrupts(TRUE);
}
// ----------------------------------------

void InitializeBoard()
{
	// Init board GPIO
   	ZbGPIO_Init();
   	// Init IO expansion
   	ZbIOE_Init();
   	// Init on-board watch-dog
   	ZbWatchDog_Init();
}
// ----------------------------------------

void InitializeController()
{
	CONTROL_Init();
}
// ----------------------------------------

// ISRs
// ----------------------------------------
#ifdef BOOT_FROM_FLASH
	#pragma CODE_SECTION(Timer2_ISR, "ramfuncs");
	#pragma CODE_SECTION(CAN0_ISR, "ramfuncs");
	#pragma CODE_SECTION(IllegalInstruction_ISR, "ramfuncs");
#endif

// timer 2 ISR
ISRCALL Timer2_ISR(void)
{
	static Int16U dbgCounter = 0;

	// Update tick counter
	++CONTROL_TimeCounter;
	// Update low-priority tasks
	CONTROL_UpdateLow();

	// Service watch-dogs
	if (CONTROL_BootLoaderRequest != BOOT_LOADER_REQUEST)
	{
		ZwSystem_ServiceDog();
		ZbWatchDog_Strobe();
	}

   ++dbgCounter;
   if(dbgCounter == DBG_COUNTER_PERIOD)
   {
	  ZbGPIO_ToggleLED();
	  dbgCounter = 0;
   }

	// no PIE
	TIMER2_ISR_DONE;
}
// ----------------------------------------

// Line 0 ISR
ISRCALL CAN0_ISR(void)
{
    // handle CAN system events
	ZwCANa_DispatchSysEvent();
	// allow other interrupts from group 9
	CAN_ISR_DONE;
}
// ----------------------------------------

// ILLEGAL ISR
ISRCALL IllegalInstruction_ISR(void)
{
	// Disable interrupts
	DINT;

	// Close gates
	GpioDataRegs.GPASET.bit.GPIO4 = 0;

	// Try set IOE to default state
	ZbIOE_RegisterReset();

	// Reset system using WD
	ZwSystem_ForceDog();
}
// ----------------------------------------


