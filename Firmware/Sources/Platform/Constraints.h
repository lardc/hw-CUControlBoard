// ----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
//
#include "DataTable.h"
#include "Global.h"


// Definitions
#define MAX_SAFETY_RELAY_HYST_ALT	2000
#define COMM_CUHV6_GATE_4WIRE		7


// Types
//
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;


// Variables
//
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];


#endif // __CONSTRAINTS_H
