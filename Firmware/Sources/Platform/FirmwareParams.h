#ifndef __FIRMWARE_PARAMS_H
#define __FIRMWARE_PARAMS_H

// Include
#include "stdinc.h"

// Types
typedef enum __SelectorIndex
{
	SID_None = -1,
	SID_PCB2_4_Manuf = 0,
	SID_PCB2_3_Manuf,
	SID_PCB2_3
} SelectorIndex;

// Functions
void FWPAR_LoadBoardLabel();
SelectorIndex FWPAR_GetSelector();

#endif // __FIRMWARE_PARAMS_H
