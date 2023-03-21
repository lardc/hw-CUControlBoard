#ifndef __FIRMWARE_LABEL_H
#define __FIRMWARE_LABEL_H

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
void FWLB_LoadBoardLabel();
SelectorIndex FWLB_GetSelector();

void FWLB_PrepareLabelRead();
Int16U FWLB_ReadLabelSymbol();

#endif // __FIRMWARE_LABEL_H
