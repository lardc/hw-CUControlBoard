// ----------------------------------------
// Board-specific GPIO functions
// ----------------------------------------

// Header
#include "Global.h"
#include "ZbGPIO.h"
#include "SysConfig.h"
#include "BoardConfig.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"

// Functions
//
void ZbGPIO_Init()
{
	// Reset to default state
	// Output pins
	ZwGPIO_WritePin(PE_CTRL_PIN, FALSE);
	ZwGPIO_WritePin(HW_SAFE_SW_PIN, TRUE);
	ZwGPIO_WritePin(MOSFET_P6, FALSE);
	ZwGPIO_WritePin(MOSFET_P8, FALSE);
	ZwGPIO_WritePin(MOSFET_P11, FALSE);
	ZwGPIO_WritePin(MOSFET_P13, FALSE);
	ZwGPIO_WritePin(PIN_LED, FALSE);
	ZwGPIO_WritePin(CS_RELAY, FALSE);
	ZwGPIO_WritePin(SAFETY_CTRL1, FALSE);
	ZwGPIO_WritePin(SAFETY_CTRL2, FALSE);
	ZwGPIO_WritePin(SAFETY_CTRL3, FALSE);
	ZwGPIO_WritePin(SAFETY_CTRL4, FALSE);

   	ZwGPIO_PinToOutput(PE_CTRL_PIN);
   	ZwGPIO_PinToOutput(HW_SAFE_SW_PIN);
   	ZwGPIO_PinToOutput(MOSFET_P6);
   	ZwGPIO_PinToOutput(MOSFET_P8);
   	ZwGPIO_PinToOutput(MOSFET_P11);
   	ZwGPIO_PinToOutput(MOSFET_P13);
   	ZwGPIO_PinToOutput(PIN_LED);
   	ZwGPIO_PinToOutput(CS_RELAY);
   	ZwGPIO_PinToOutput(SAFETY_CTRL1);
   	ZwGPIO_PinToOutput(SAFETY_CTRL2);
   	ZwGPIO_PinToOutput(SAFETY_CTRL3);
   	ZwGPIO_PinToOutput(SAFETY_CTRL4);

   	// Input pins
   	ZwGPIO_PinToInput(SAFETY_PIN, FALSE, GPIO_NSAMPLE);
   	ZwGPIO_PinToInput(PRESSURE_PIN, TRUE, GPIO_NSAMPLE);
}
// ----------------------------------------

void ZbGPIO_SetSafetyLine1(Boolean Enabled)
{
	ZwGPIO_WritePin(SAFETY_CTRL1, !Enabled);
}
// ----------------------------------------

void ZbGPIO_SetSafetyLine2(Boolean Enabled)
{
	ZwGPIO_WritePin(SAFETY_CTRL2, !Enabled);
}
// ----------------------------------------

void ZbGPIO_SetSafetyLine3(Boolean Enabled)
{
	ZwGPIO_WritePin(SAFETY_CTRL3, !Enabled);
}
// ----------------------------------------

void ZbGPIO_SetSafetyLine4(Boolean Enabled)
{
	ZwGPIO_WritePin(SAFETY_CTRL4, !Enabled);
}
// ----------------------------------------

void ZbGPIO_SafetyRelay(Boolean Enabled)
{
	ZwGPIO_WritePin(CS_RELAY, Enabled);
}
// ----------------------------------------

void ZbGPIO_ToggleLED()
{
	ZwGPIO_TogglePin(PIN_LED);
}
// ----------------------------------------

void ZbGPIO_SafetyHWTriggering(Boolean Enabled)
{
	ZwGPIO_WritePin(HW_SAFE_SW_PIN, !Enabled);
}
// ----------------------------------------

void ZbGPIO_ConnectProtectiveEarth(Boolean Enabled)
{
   	ZwGPIO_WritePin(PE_CTRL_PIN, !Enabled);
}
// ----------------------------------------

Boolean ZbGPIO_GetSafetyState(Boolean DisableSafety)
{
	return DisableSafety ? FALSE : !ZwGPIO_ReadPin(SAFETY_PIN);
}
// ----------------------------------------

Boolean ZbGPIO_GetPressureState(Boolean DisablePressure)
{
	if(DisablePressure)
		return FALSE;
	else
	{
		Boolean InputValue = ZwGPIO_ReadPin(PRESSURE_PIN);
		return DataTable[REG_PCB_V20] ? !InputValue : InputValue;
	}
}
// ----------------------------------------

void ZbGPIO_LightPressureFault(Boolean Enabled)
{
   	ZwGPIO_WritePin(MOSFET_P13, Enabled);
}
// ----------------------------------------

void ZbGPIO_LightSafetySensorTrig(Boolean Enabled)
{
   	ZwGPIO_WritePin(MOSFET_P11, Enabled);
}
// ----------------------------------------


