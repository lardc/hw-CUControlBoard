// -----------------------------------------
// Controller logic
// ----------------------------------------

// Header
#include "Controller.h"
//
// Includes
#include "SysConfig.h"
#include "ZwDSP.h"
#include "ZbBoard.h"
#include "DataTable.h"
#include "CommutationTable.h"
#include "DeviceObjectDictionary.h"
#include "SCCISlave.h"
#include "DeviceProfile.h"
#include "CommutationTable.h"
#include "Commutator.h"


// Types
//
typedef void (*FUNC_AsyncDelegate)();


// Variables
//
static Int16U PressureFilterCounter = 0;
static volatile FUNC_AsyncDelegate DPCDelegate = NULL;
//
static volatile Boolean CycleActive = FALSE;
volatile Int64U CONTROL_TimeCounter = 0;
volatile DeviceState CONTROL_State = DS_None;
//
// Boot-loader flag
#pragma DATA_SECTION(CONTROL_BootLoaderRequest, "bl_flag");
volatile Int16U CONTROL_BootLoaderRequest = 0;


// Forward functions
//
static void CONTROL_SafetyCircuitTrigger();
static void CONTROL_PressureTrigger();
static void CONTROL_FillWPPartDefault();
static void CONTROL_SetDeviceState(DeviceState NewState);
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
static Boolean CONTROL_FilterPressure(Boolean Triggered);


// Functions
//
void CONTROL_Init()
{
	// Data-table EPROM service configuration
	EPROMServiceConfig EPROMService = { NULL, NULL };

	// Init data table
	DT_Init(EPROMService, TRUE);
	DT_SaveFirmwareInfo(DEVICE_CAN_ADDRESS, 0);
	// Fill state variables with default values
	CONTROL_FillWPPartDefault();

	// Device profile initialization
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	// Reset control values
	DEVPROFILE_ResetControlSection();

	if(ZwSystem_GetDogAlarmFlag())
	{
		DataTable[REG_WARNING] = WARNING_WATCHDOG_RESET;
		ZwSystem_ClearDogAlarmFlag();
	}
}
// ----------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();

	// Update CAN bus status
	DEVPROFILE_UpdateCANDiagStatus();

	// Process deferred procedures
	if(DPCDelegate)
	{
		FUNC_AsyncDelegate del = DPCDelegate;
		DPCDelegate = NULL;
		del();
	}
}
// ----------------------------------------

void CONTROL_SelectSafetyConfiguration()
{
	ZbGPIO_SetSafetyLine1(DataTable[REG_EN_SFTY_IN1]);
	ZbGPIO_SetSafetyLine2(DataTable[REG_EN_SFTY_IN2]);
	ZbGPIO_SetSafetyLine3(DataTable[REG_EN_SFTY_IN3]);
	ZbGPIO_SetSafetyLine4(DataTable[REG_EN_SFTY_IN4]);
}
// ----------------------------------------

void inline CONTROL_RequestDPC(FUNC_AsyncDelegate Action)
{
	DPCDelegate = Action;
}
// ----------------------------------------

#ifdef BOOT_FROM_FLASH
	#pragma CODE_SECTION(CONTROL_UpdateLow, "ramfuncs");
#endif
void CONTROL_UpdateLow()
{
	// Check safety circuit
	if(CONTROL_State == DS_SafetyActive)
	{
		CONTROL_SelectSafetyConfiguration();
		if(ZbGPIO_GetSafetyState(FALSE))
			CONTROL_RequestDPC(&CONTROL_SafetyCircuitTrigger);
	}

	// Check pressure
	if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
		if(CONTROL_FilterPressure(ZbGPIO_GetPressureState(FALSE)))
			CONTROL_RequestDPC(&CONTROL_PressureTrigger);

	DataTable[REG_PRES_SEN_STATE] = ZbGPIO_GetPressureState(TRUE);
	DataTable[REG_SC_STATE] = ZbGPIO_GetSafetyState(TRUE);
}
// ----------------------------------------

#ifdef BOOT_FROM_FLASH
	#pragma CODE_SECTION(CONTROL_NotifyCANFault, "ramfuncs");
#endif
void CONTROL_NotifyCANFault(ZwCAN_SysFlags Flag)
{
	DEVPROFILE_NotifyCANFault(Flag);
}
// ----------------------------------------

#ifdef BOOT_FROM_FLASH
	#pragma CODE_SECTION(CONTROL_FilterPressure, "ramfuncs");
#endif
static Boolean CONTROL_FilterPressure(Boolean Triggered)
{
	if(Triggered)
		PressureFilterCounter++;
	else
		PressureFilterCounter = 0;

	if(PressureFilterCounter > PRESSURE_FILTER_T)
		PressureFilterCounter = PRESSURE_FILTER_T;

	return (PressureFilterCounter >= PRESSURE_FILTER_T);
}
// ----------------------------------------

static void CONTROL_CommutateNone()
{
	#ifdef COMM_MODE_2
		COMM2_CommutateNone();
	#else
		COMM6_CommutateNone();
	#endif
}
// ----------------------------------------

static void CONTROL_SafetyCircuitTrigger()
{
	ZbGPIO_SafetyRelay(FALSE);
	ZbGPIO_LightSafetySensorTrig(TRUE);

	ZbIOE_ExternalOutput(FALSE);
	CONTROL_CommutateNone();
	ZbIOE_ExternalOutput(TRUE);

	CONTROL_SetDeviceState(DS_SafetyTrig);
}
// ----------------------------------------

static void CONTROL_PressureTrigger()
{
	ZbGPIO_SafetyRelay(FALSE);
	CONTROL_CommutateNone();

	DataTable[REG_FAULT_REASON] = FAULT_LOW_PRESSURE;
	ZbGPIO_LightPressureFault(TRUE);
	CONTROL_SetDeviceState(DS_Fault);
}
// ----------------------------------------

static void CONTROL_FillWPPartDefault()
{
	// Set volatile states
	DataTable[REG_DEV_STATE] = (Int16U)DS_None;
	DataTable[REG_FAULT_REASON] = FAULT_NONE;
	DataTable[REG_DISABLE_REASON] = DISABLE_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
}
// ----------------------------------------

static void CONTROL_SetDeviceState(DeviceState NewState)
{
	if (NewState == DS_None || NewState == DS_Enabled || NewState == DS_SafetyActive)
		ZbGPIO_SafetyRelay(TRUE);

	// Set new state
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
// ----------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	switch(ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
			{
				CONTROL_CommutateNone();
				ZbGPIO_SafetyHWTriggering(FALSE);
				CONTROL_SetDeviceState(DS_Enabled);
			}
			else if(CONTROL_State != DS_Enabled)
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				CONTROL_CommutateNone();
				ZbGPIO_SafetyHWTriggering(FALSE);
				ZbGPIO_LightSafetySensorTrig(FALSE);
				CONTROL_SetDeviceState(DS_None);
			}
			else if(CONTROL_State != DS_None)
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SET_ACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive)
			{
				ZbGPIO_SafetyHWTriggering(TRUE);
				CONTROL_SetDeviceState(DS_SafetyActive);
			}
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SET_INACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				if (CONTROL_State == DS_SafetyTrig)
					CONTROL_CommutateNone();

				ZbGPIO_SafetyHWTriggering(FALSE);
				ZbGPIO_LightSafetySensorTrig(FALSE);
				CONTROL_SetDeviceState(DS_Enabled);
			}
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_CLR_FAULT:
			{
				if(CONTROL_State == DS_Fault)
				{
					CONTROL_SetDeviceState(DS_None);
					ZbGPIO_LightPressureFault(FALSE);
					DataTable[REG_FAULT_REASON] = FAULT_NONE;
				}
			}
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;

		case ACT_WRITE_PIN:
			if(CONTROL_State == DS_None)
				ZbIOE_OutputValuesCompose(DataTable[REG_TABLE_INDEX], DataTable[REG_TABLE_ACTION]);
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_RAW_ACCESS:
			if(CONTROL_State == DS_None)
				ZbIOE_OutputValuesDirect(DataTable[REG_RAW_BOARD], DataTable[REG_RAW_MASK]);
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_FLUSH_REG:
			if(CONTROL_State == DS_None)
				ZbIOE_RegisterFlushWrite();
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

	#ifdef COMM_MODE_2

		case ACT_COMM2_NONE:
		case ACT_COMM2_GATE:
		case ACT_COMM2_SL:
		case ACT_COMM2_BV_D:
		case ACT_COMM2_BV_R:
		case ACT_COMM2_NO_PE:
		case ACT_COMM2_GATE_SL:
		case ACT_COMM2_VGNT:
			if(CONTROL_State == DS_Fault)
				*pUserError = ERR_OPERATION_BLOCKED;
			else if(CONTROL_State == DS_None)
				*pUserError = ERR_DEVICE_NOT_READY;
			else
			{
				COMM2_Commutate(ActionID);
				if (CONTROL_State == DS_SafetyTrig)
				{
					CONTROL_CommutateNone();
					ZbGPIO_LightSafetySensorTrig(FALSE);
					CONTROL_SetDeviceState(DS_SafetyActive);
				}
			}
			break;

	#else

		case ACT_COMM6_NONE:
		case ACT_COMM6_GATE:
		case ACT_COMM6_SL:
		case ACT_COMM6_BV_D:
		case ACT_COMM6_BV_R:
			if(CONTROL_State == DS_Fault)
				*pUserError = ERR_OPERATION_BLOCKED;
			else if(CONTROL_State == DS_None)
				*pUserError = ERR_DEVICE_NOT_READY;
			else
				COMM6_Commutate(ActionID, DataTable[REG_MODULE_TYPE], DataTable[REG_MODULE_POS], pUserError);
			break;

	#endif

		default:
			return FALSE;
	}

	return TRUE;
}
// ----------------------------------------

// No more.
