// ----------------------------------------
// Commutation controller
// ----------------------------------------

#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Include
#include "stdinc.h"


// Functions
//
// Switch commutation to none
void COMM2_CommutateNone();
void COMM6_CommutateNone();
// Switch in commutation mode 2
void COMM2_Commutate(Int16U ActionID);
// Switch in commutation mode 6
void COMM6_Commutate(Int16U ActionID, Int16U ModuleType, Int16U ModulePosition, pInt16U pUserError);

#endif // __COMMUTATOR_H
