// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"


// Constants
//
#ifdef COMM_MODE_2
	#define COMMUTATION_EXT_BOARDS	2
#else
	#define COMMUTATION_EXT_BOARDS	4
#endif

#define COMMUTATION_TABLE_SIZE	(COMMUTATION_EXT_BOARDS * 16)
//
// Commutation type 2
//
#define T2_SL_POT_A				26
#define T2_SL_POT_C				30
#define T2_SL_CTL_A				11
#define T2_SL_CTL_C				6
#define T2_SL_PWR				23
//
#define T2_GATE_POW_A			2
#define T2_GATE_POW_CTRL_C		6
#define T2_GATE_CTL_A			10
#define T2_GATE_POT_CTL_A		14
#define T2_GATE_POT_CTL_C		31
//
#define T2_BV_POS_POW_A			0
#define T2_BV_NEG_POW_A			1
//
#define T2_BV_POS_POW_C			4
#define T2_BV_NEG_POW_C			5
//
#define T2_BB_DISCONNECT		18
#define T2_SAFETY_RELAY			19
//
// Commutation type 6
//
#define T6_SL_POT_A_1			10
#define T6_SL_POT_A_2			14
#define T6_SL_POT_A_3			26
#define T6_SL_POT_C_1			11
#define T6_SL_POT_C_2			15
#define T6_SL_POT_C_3			27
#define T6_SL_CTL_A_1			42
#define T6_SL_CTL_A_2			34
#define T6_SL_CTL_C_1			46
#define T6_SL_CTL_C_2			38
#define T6_SL_POW_A_1			2
#define T6_SL_POW_A_2			0
#define T6_SL_POW_A_3			1
#define T6_SL_POW_C_1			3
#define T6_SL_POW_C_2			6
#define T6_SL_POW_C_3			7
//
#define T6_GATE_POW_A_1			30
#define T6_GATE_POW_A_2			18
#define T6_GATE_POW_A_3			22
#define T6_GATE_POW_C_1			31
#define T6_GATE_POW_C_2			19
#define T6_GATE_POW_C_3			23
#define T6_GATE_CTL_A_1			43
#define T6_GATE_CTL_A_2			35
#define T6_GATE_CTL_C_1			47
#define T6_GATE_CTL_C_2			39
//
#define T6_BV_POS_POW_1			28
#define T6_BV_POS_POW_2			16
#define T6_BV_POS_POW_3			20
//
#define T6_BV_NEG_POW_1			29
#define T6_BV_NEG_POW_2			17
#define T6_BV_NEG_POW_3			21
//
#if defined(BVT_HP) && defined(BVT_LP)
	#define T6_ISOL_POS_POW_1		8
	#define T6_ISOL_POS_POW_2		12
	#define T6_ISOL_POS_POW_3		24
#else
	#define T6_BV_POS_POW_1			28
	#define T6_BV_POS_POW_2			16
	#define T6_BV_POS_POW_3			20
#endif
#define T6_ISOL_POS_A_1			40
#define T6_ISOL_POS_A_2			32
#define T6_ISOL_POS_C_1			44
#define T6_ISOL_POS_C_2			36
#define T6_ISOL_NEG_ISO			4


// Types
//
typedef struct __CommutationTableItem
{
	Int16U BoardNum;
	Int16U Bit;
} CommutationTableItem;


// Variables
//
extern const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE];


#endif // __COMMTABLE_H
