// ----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"

// Definitions
#define COMMUTATION2_EXT_BOARDS		2
#define COMMUTATION4_EXT_BOARDS		2
#define COMMUTATION6_EXT_BOARDS		3

#define COMMUTATION2_TABLE_SIZE		(COMMUTATION2_EXT_BOARDS * 16)
#define COMMUTATION4_TABLE_SIZE		(COMMUTATION4_EXT_BOARDS * 16)
#define COMMUTATION6_TABLE_SIZE		(COMMUTATION6_EXT_BOARDS * 16)


// Commutation type 2
//
#define T2_SL_POT_A				26
#define T2_SL_POT_C				30
#define T2_SL_CTL_A				11
#define T2_SL_CTL_C				6
#define T2_SL_CTL_C_2WIRE		15
#define T2_SL_PWR				23
//
#define T2_GATE_POW_A			2
#define T2_GATE_POW_CTRL_C		6
#define T2_GATE_CTL_A			10
#define T2_GATE_POT_CTL_A		14
#define T2_GATE_POT_CTL_C		31
#define T2_GATE_CTL_C_2WIRE		14
//
#define T2_BV_POS_POW_A			0
#define T2_BV_NEG_POW_A			1
//
#define T2_BV_POS_POW_C			4
#define T2_BV_NEG_POW_C			5
//
#define T2_BB_RELAY_ACTIVATE	19
//
// Для PCB v.2.2 и ниже
#define T2_OLD_BB_RELAY			18
#define T2_OLD_SAFETY_RELAY		19


// Commutation type 4
//
#define T4_SL_POT_A_1			10
#define T4_SL_POT_A_2			11
#define T4_SL_POT_C_1			12
#define T4_SL_POT_C_2			13
#define T4_SL_CTL_A				30
#define T4_SL_CTL_C_1			8
#define T4_SL_CTL_C_2			9
#define T4_SL_CUHC_DIR			23
#define T4_SL_CUHC_REV			22
//
#define T4_GATE_POW_A_1			2
#define T4_GATE_POW_A_2			3
#define T4_GATE_POW_CTRL_C_1	6
#define T4_GATE_POW_CTRL_C_2	7
#define T4_GATE_CTL_A			26
#define T4_GATE_POT_CTL_A		27
#define T4_GATE_POT_CTL_C_1		14
#define T4_GATE_POT_CTL_C_2		15
//
#define T4_BV_POS_POW_1			0
#define T4_BV_NEG_POW_1			5
//
#define T4_BV_POS_POW_2			1
#define T4_BV_NEG_POW_2			4
//
#define T4_BB_DISCONNECT		19


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
#define T6_BV_POS_POW_1			28
#define T6_BV_POS_POW_2			16
#define T6_BV_POS_POW_3			20


// Types
typedef struct __CommutationTableItem
{
	Int16U BoardNum;
	Int16U Bit;
} CommutationTableItem;


// Variables
extern const CommutationTableItem CommutationTable2[];
extern const CommutationTableItem CommutationTable4[];
extern const CommutationTableItem CommutationTable6[];

#endif // __COMMTABLE_H
