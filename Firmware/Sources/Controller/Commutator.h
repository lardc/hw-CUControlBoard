// ----------------------------------------
// Commutation controller
// ----------------------------------------

#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Include
#include "stdinc.h"

// Types
typedef enum __CommutationMode
{
	CM_CUHV2,
	CM_CUHV4,
	CM_CUHV6
} CommutationMode;

// Variables
extern CommutationMode CurrentCommMode;

// Functions
//
void COMM_Init();
void COMM_CommutateNone();

void COMM2_Commutate(Int16U ActionID);
void COMM4_Commutate(Int16U ActionID, Int16U ModuleType, pInt16U pUserError);
void COMM6_Commutate(Int16U ActionID, Int16U ModuleType, Int16U ModulePosition, Int16U Case, pInt16U pUserError);
void COMM6_G4W_Commutate(Int16U ActionID, Int16U ModuleType, Int16U ModulePosition, Int16U Case, pInt16U pUserError);

#endif // __COMMUTATOR_H
