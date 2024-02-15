// ----------------------------------------
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
enum __SafetyState
{
	SS_Undef,
	SS_Good,
	SS_Trigged
};

// Variables
//
static Int16U PressureFilterCounter = 0;
static volatile FUNC_AsyncDelegate DPCDelegate = NULL;
//
static volatile Boolean CycleActive = FALSE;
volatile Int64U CONTROL_TimeCounter = 0;
volatile DeviceState CONTROL_State = DS_None;
volatile enum __SafetyState SafetyState = SS_Undef;
//
// Boot-loader flag
#pragma DATA_SECTION(CONTROL_BootLoaderRequest, "bl_flag");
volatile Int16U CONTROL_BootLoaderRequest = 0;


// Forward functions
//
static void CONTROL_SafetyCircuitTrigger();
static void CONTROL_PressureTrigger();
static void CONTROL_SafetyGood();
static void CONTROL_FillWPPartDefault();
static void CONTROL_SetDeviceState(DeviceState NewState);
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
static Boolean CONTROL_FilterPressure(Boolean Triggered);
static void CONTROL_SafetyHWTrigger(Boolean Enable);


// Functions
//
void CONTROL_Init()
{
	// Data-table EPROM service configuration
	EPROMServiceConfig EPROMService = { &ZbMemory_WriteValuesEPROM, &ZbMemory_ReadValuesEPROM };

	// Init data table
	DT_Init(EPROMService, FALSE);
	DT_SaveFirmwareInfo(DEVICE_CAN_ADDRESS, 0);
	// Fill state variables with default values
	CONTROL_FillWPPartDefault();

	COMM_Init();

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

Boolean CONTROL_SelectSafetyConfiguration()
{
	static Int16U PrevConfig = 0;

	if(DataTable[REG_SAFETY_HW_MODE])
	{
		ZbGPIO_SetSafetyLine1(TRUE);
		ZbGPIO_SetSafetyLine2(TRUE);
		ZbGPIO_SetSafetyLine3(!DataTable[REG_IGNORE_SAFETY_SEN3]);
		ZbGPIO_SetSafetyLine4(!DataTable[REG_IGNORE_SAFETY_SEN4]);

		return FALSE;
	}
	else
	{
		Int16U r1 = DataTable[REG_EN_SFTY_IN1];
		Int16U r2 = DataTable[REG_EN_SFTY_IN2];
		Int16U r3 = DataTable[REG_EN_SFTY_IN3];
		Int16U r4 = DataTable[REG_EN_SFTY_IN4];

		Int16U NewConfig = (r4 << 3) | (r3 << 2) | (r2 << 1) | r1;
		Boolean ConfigChanged = (NewConfig != PrevConfig);
		PrevConfig = NewConfig;

		ZbGPIO_SetSafetyLine1(r1);
		ZbGPIO_SetSafetyLine2(r2);
		ZbGPIO_SetSafetyLine3(r3);
		ZbGPIO_SetSafetyLine4(r4);

		return ConfigChanged;
	}
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
	static Int16U SafetyHysteresis = 0;
	static Int64U IgnoreSafetyTimeout = 0;

	// Аппаратный режим работы контура безопасности без возможности отключения
	if(DataTable[REG_SAFETY_HW_MODE])
	{
		CONTROL_SelectSafetyConfiguration();

		// Гистерезис на срабатывание датчика
		if(ZbGPIO_GetSafetyState(FALSE))
			SafetyHysteresis = DataTable[REG_SAFETY_RELAY_HYST_ALT] ?
					DataTable[REG_SAFETY_RELAY_HYST_ALT] : SAFETY_RELEASE_TIMEOUT;
		else if(SafetyHysteresis)
			SafetyHysteresis--;

		// Обработка события
		// Срабатывания контура
		if(SafetyHysteresis)
		{
			if(SafetyState != SS_Trigged)
				CONTROL_RequestDPC(&CONTROL_SafetyCircuitTrigger);
		}
		// Снятия срабатывания контура
		else if(SafetyState != SS_Good && CONTROL_State != DS_SafetyTrig && CONTROL_State != DS_Fault)
			CONTROL_RequestDPC(&CONTROL_SafetyGood);
	}

	// Режим работы контура безопасности с возможностью отключения
	else if(CONTROL_State == DS_SafetyActive)
	{
		if(CONTROL_SelectSafetyConfiguration())
			IgnoreSafetyTimeout = CONTROL_TimeCounter + IGNORE_ON_SFTY_CHANGE_MS;
		if((CONTROL_TimeCounter > IgnoreSafetyTimeout) && ZbGPIO_GetSafetyState(DataTable[REG_SAFETY_DISABLE]))
			CONTROL_RequestDPC(&CONTROL_SafetyCircuitTrigger);
	}

	// Проверка давления
	if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
		if(CONTROL_FilterPressure(ZbGPIO_GetPressureState(DataTable[REG_PRESSURE_DISABLE])))
			CONTROL_RequestDPC(&CONTROL_PressureTrigger);

	DataTable[REG_PRES_SEN_STATE] = ZbGPIO_GetPressureState(FALSE);
	DataTable[REG_SC_STATE] = ZbGPIO_GetSafetyState(FALSE);
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
	COMM_CommutateNone();
}
// ----------------------------------------

static void CONTROL_SafetyGood()
{
	ZbGPIO_SafetyRelay(TRUE);
	CONTROL_CommutateNone();

	ZbGPIO_LightSafetySensorTrig(FALSE);
	SafetyState = SS_Good;
}
// ----------------------------------------

static void CONTROL_SafetyCircuitTrigger()
{
	ZbGPIO_LightSafetySensorTrig(TRUE);

	ZbGPIO_SafetyRelay(FALSE);
	ZbIOE_ExternalOutput(FALSE);
	ZbIOE_SafetyTrigFlag();
	CONTROL_CommutateNone();
	ZbIOE_ExternalOutput(TRUE);

	SafetyState = SS_Trigged;

	if(!DataTable[REG_SAFETY_HW_MODE] || CONTROL_State == DS_SafetyActive)
		CONTROL_SetDeviceState(DS_SafetyTrig);
}
// ----------------------------------------

static void CONTROL_PressureTrigger()
{
	ZbGPIO_LightPressureFault(TRUE);

	DataTable[REG_FAULT_REASON] = FAULT_LOW_PRESSURE;
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
	if(!DataTable[REG_SAFETY_HW_MODE] && \
			(NewState == DS_None || NewState == DS_Enabled || NewState == DS_SafetyActive))
	{
		ZbGPIO_SafetyRelay(TRUE);
	}

	// Set new state
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
// ----------------------------------------

static void CONTROL_SafetyHWTrigger(Boolean Enable)
{
	ZbGPIO_SafetyHWTriggering(DataTable[REG_SAFETY_DISABLE] ? FALSE : Enable);
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
				CONTROL_SafetyHWTrigger(FALSE);
				CONTROL_SetDeviceState(DS_Enabled);
			}
			else if(CONTROL_State != DS_Enabled)
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				CONTROL_CommutateNone();
				CONTROL_SafetyHWTrigger(FALSE);
				if(!DataTable[REG_SAFETY_HW_MODE])
					ZbGPIO_LightSafetySensorTrig(FALSE);
				CONTROL_SetDeviceState(DS_None);
			}
			else if(CONTROL_State != DS_None)
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SET_ACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive)
			{
				CONTROL_SafetyHWTrigger(TRUE);
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

				CONTROL_SafetyHWTrigger(FALSE);
				if(!DataTable[REG_SAFETY_HW_MODE])
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

		case ACT_DBG_INDICATORS:
			if(CONTROL_State == DS_None)
			{
				ZbGPIO_LightSafetySensorTrig(TRUE);
				DELAY_US(500000);
				ZbGPIO_LightSafetySensorTrig(FALSE);
				ZbGPIO_LightPressureFault(TRUE);
				DELAY_US(500000);
				ZbGPIO_LightPressureFault(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_BLACK_BOX:
			if(CONTROL_State == DS_None)
			{
				Int16U BBRelayIndex = DataTable[REG_PCB_V22_AND_LOWER] ? T2_OLD_BB_RELAY : T2_BB_RELAY_ACTIVATE;
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
				ZbIOE_RegisterFlushWrite();
				DELAY_US(500000);
				ZbIOE_OutputValuesCompose(BBRelayIndex, FALSE);
				ZbIOE_RegisterFlushWrite();
				DELAY_US(500000);
			}
			break;

		case ACT_DBG_CS_STOP_OFF:
			if(CONTROL_State == DS_None)
			{
				if(DataTable[REG_PCB_V22_AND_LOWER])
				{
					ZbIOE_OutputValuesReset();
					ZbIOE_OutputValuesCompose(T2_OLD_SAFETY_RELAY, TRUE);
					ZbIOE_RegisterFlushWrite();
				}
				else
					ZbGPIO_SafetyRelay(TRUE);
			}
			break;

		case ACT_DBG_CS_STOP_ON:
			if(CONTROL_State == DS_None)
			{
				if(DataTable[REG_PCB_V22_AND_LOWER])
				{
					ZbIOE_OutputValuesReset();
					ZbIOE_OutputValuesCompose(T2_OLD_SAFETY_RELAY, FALSE);
					ZbIOE_RegisterFlushWrite();
				}
				else
					ZbGPIO_SafetyRelay(FALSE);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
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

		case ACT_COMM2_4_NONE:
		case ACT_COMM2_4_GATE:
		case ACT_COMM2_4_SL:
		case ACT_COMM2_4_BV_D:
		case ACT_COMM2_4_BV_R:
		case ACT_COMM2_4_NO_PE:
		case ACT_COMM2_4_GATE_SL:
		case ACT_COMM2_4_VGNT:
			if(DataTable[REG_SAFETY_HW_MODE] && SafetyState == SS_Trigged)
				*pUserError = ERR_OPERATION_BLOCKED;
			else if(CurrentCommMode == CM_CUHV6)
				return FALSE;
			else
			{
				if(CONTROL_State == DS_Fault)
					*pUserError = ERR_OPERATION_BLOCKED;
				else if(CONTROL_State == DS_None)
					*pUserError = ERR_DEVICE_NOT_READY;
				else
				{
					if(CONTROL_State == DS_SafetyTrig)
					{
						CONTROL_CommutateNone();
						ZbGPIO_LightSafetySensorTrig(FALSE);
						CONTROL_SetDeviceState(DS_SafetyActive);
					}
					else if(CurrentCommMode == CM_CUHV2)
						COMM2_Commutate(ActionID);
					else
						COMM4_Commutate(ActionID, DataTable[REG_MODULE_TYPE], pUserError);
				}
			}
			break;

		case ACT_COMM6_NONE:
		case ACT_COMM6_GATE:
		case ACT_COMM6_SL:
		case ACT_COMM6_BV_D:
		case ACT_COMM6_BV_R:
			if(DataTable[REG_SAFETY_HW_MODE] && SafetyState == SS_Trigged)
				*pUserError = ERR_OPERATION_BLOCKED;
			else if(CurrentCommMode != CM_CUHV6)
				return FALSE;
			else
			{
				if(CONTROL_State == DS_Fault)
					*pUserError = ERR_OPERATION_BLOCKED;
				else if(CONTROL_State == DS_None)
					*pUserError = ERR_DEVICE_NOT_READY;
				else
					COMM6_Commutate(ActionID, DataTable[REG_MODULE_TYPE], DataTable[REG_MODULE_POS], pUserError);
			}
			break;

		default:
			return FALSE;
	}

	return TRUE;
}
// ----------------------------------------


