// ----------------------------------------
// Board-specific GPIO functions
// ----------------------------------------

#ifndef __ZBGPIO_H
#define __ZBGPIO_H

// Include
#include "stdinc.h"
#include "ZwDSP.h"


// Functions
//
// Init module
void ZbGPIO_Init();
// Toggle LED
void ZbGPIO_ToggleLED();
void ZbGPIO_SafetyHWTriggering(Boolean Enabled);
void ZbGPIO_ConnectProtectiveEarth(Boolean Enabled);
// Get pin state
Boolean ZbGPIO_GetSafetyState(Boolean DisableSafety);
Boolean ZbGPIO_GetPressureState(Boolean DisablePressure);
// Indication switches
void ZbGPIO_LightPressureFault(Boolean Enabled);
void ZbGPIO_LightSafetySensorTrig(Boolean Enabled);
// Safety relay
void ZbGPIO_SafetyRelay(Boolean Enabled);
//
// Enable safety lines
void ZbGPIO_SetSafetyLine1(Boolean Enabled);
void ZbGPIO_SetSafetyLine2(Boolean Enabled);
void ZbGPIO_SetSafetyLine3(Boolean Enabled);
void ZbGPIO_SetSafetyLine4(Boolean Enabled);


#endif // __ZBGPIO_H
