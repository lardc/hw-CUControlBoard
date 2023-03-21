#ifndef __FIRMWARE_LABEL_H
#define __FIRMWARE_LABEL_H

// Include
#include "stdinc.h"

// Definitions
#define LABEL_NAME_MAX_LENGTH		64

// Types
typedef enum __SelectorIndex
{
	SID_None = -1,
	SID_PCB2_4_Manuf = 0,
	SID_PCB2_3_Manuf,
	SID_PCB2_3
} SelectorIndex;

typedef struct __Label
{
	char Name[LABEL_NAME_MAX_LENGTH];
	SelectorIndex Index;
} Label;

// Functions
void FWLB_LoadBoardLabel();
SelectorIndex FWLB_GetSelector();

void FWLB_PrepareLabelRead();
Int16U FWLB_ReadLabelSymbol();

#endif // __FIRMWARE_LABEL_H
