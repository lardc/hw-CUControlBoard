// ----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

#ifndef __ZBIOEXPANSION_H
#define __ZBIOEXPANSION_H

// Include
#include "stdinc.h"
#include "Commutator.h"

// Functions
//
// Initialize module
void ZbIOE_Init();
void ZbIOE_MakeTablesBinding(CommutationMode Mode);
// Enable external boards output
void ZbIOE_ExternalOutput(Boolean Enable);
// Reset output register to zero
void ZbIOE_RegisterReset();
// Write cache to physical register
void ZbIOE_RegisterFlushWrite();
// Compose cached values
void ZbIOE_OutputValuesCompose(Int16U TableID, Boolean TurnOn);
// Reset cached values to zero
void ZbIOE_OutputValuesReset();
void ZbIOE_SafetyTrigFlag();
// Direct access to the cached values
void ZbIOE_OutputValuesDirect(Int16U BoardID, Int16U Mask);

#endif // __ZBIOEXPANSION_H
