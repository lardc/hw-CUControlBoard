// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "CommutationTable.h"

// Output pins bindings
//
#define PIN_A1	BIT5
#define PIN_A2	BIT4
#define PIN_A4	BIT6
#define PIN_A5	BIT7
//
#define PIN_B1	BIT1
#define PIN_B2	BIT0
#define PIN_B4	BIT2
#define PIN_B5	BIT3
//
#define PIN_C1	BIT13
#define PIN_C2	BIT12
#define PIN_C4	BIT14
#define PIN_C5	BIT15
//
#define PIN_D1	BIT9
#define PIN_D2	BIT8
#define PIN_D4	BIT10
#define PIN_D5	BIT11

// Extension board indexes
//---------------------------------
// Board 0 is the most distant extension board
// to the control board
//---------------------------------
//
#define BOARD1	0
#define BOARD2	1
#define BOARD3	2

// Constants
//
#ifdef COMM_MODE_2
const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// BV:		HV2 to POWER_A
						{BOARD1, PIN_A2},			// 1	// BV:		HV1 to POWER_A
						{BOARD1, PIN_A4},			// 2	// Gate:	Power Anode to POWER_A
						{BOARD1, PIN_A5},			// 3
						{BOARD1, PIN_B1},			// 4	// BV:		HV2 to POWER_C
						{BOARD1, PIN_B2},			// 5	// BV:		HV1 to POWER_C
						{BOARD1, PIN_B4},			// 6	// Gate+SL:	Power and Control Cathode to POWER_C
						{BOARD1, PIN_B5},			// 7
						{BOARD1, PIN_C1},			// 8
						{BOARD1, PIN_C2},			// 9
						{BOARD1, PIN_C4},			// 10	// SL: 		SL Control Anode to CTRL_A
						{BOARD1, PIN_C5},			// 11	// Gate:	Gate Control Anode to CTRL_A
						{BOARD1, PIN_D1},			// 12
						{BOARD1, PIN_D2},			// 13
						{BOARD1, PIN_D4},			// 14	// Gate		Gate Potential Control Anode to POTENTIAL_CTRL_A
						{BOARD1, PIN_D5},			// 15
						{BOARD2, PIN_A1},			// 16
						{BOARD2, PIN_A2},			// 17
						{BOARD2, PIN_A4},			// 18
						{BOARD2, PIN_A5},			// 19	// BB:		Disconnect control
						{BOARD2, PIN_B1},			// 20
						{BOARD2, PIN_B2},			// 21
						{BOARD2, PIN_B4},			// 22
						{BOARD2, PIN_B5},			// 23	// SL:		HC POWER
						{BOARD2, PIN_C1},			// 24
						{BOARD2, PIN_C2},			// 25
						{BOARD2, PIN_C4},			// 26	// SL: 		Potential Anode to POTENTIAL_A
						{BOARD2, PIN_C5},			// 27
						{BOARD2, PIN_D1},			// 28
						{BOARD2, PIN_D2},			// 29
						{BOARD2, PIN_D4},			// 30	// SL: 		Potential Cathode to POTENTIAL_C
						{BOARD2, PIN_D5},			// 31	// Gate		Gate Potential Control Cathode to POTENTIAL_CTRL_C
				};
#else
const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// SL:		HC+ to POWER_2		// 2-top
						{BOARD1, PIN_A2},			// 1	// SL:		HC+ to POWER_3		// 3-top
						{BOARD1, PIN_A4},			// 2	// SL:		HC+ to POWER_1		// 1-top
						{BOARD1, PIN_A5},			// 3	// SL:		HC- to POWER_1		// 1-bottom
						{BOARD1, PIN_B1},			// 4	// BVLP:	HV- to Isolation
						{BOARD1, PIN_B2},			// 5
						{BOARD1, PIN_B4},			// 6	// SL:		HC- to POWER_2		// 2-bottom
						{BOARD1, PIN_B5},			// 7	// SL:		HC- to POWER_3		// 3-bottom
						{BOARD1, PIN_C1},			// 8	// BVLP:	LPHV+ to POTENTIAL_1
						{BOARD1, PIN_C2},			// 9	// BVLP:	LPHV- to POTENTIAL_1
						{BOARD1, PIN_C4},			// 10	// SL: 		Potential Anode to POTENTIAL_1
						{BOARD1, PIN_C5},			// 11	// SL: 		Potential Cathode to POTENTIAL_1
						{BOARD1, PIN_D1},			// 12	// BVLP:	LPHV+ to POTENTIAL_2
						{BOARD1, PIN_D2},			// 13	// BVLP:	LPHV- to POTENTIAL_2
						{BOARD1, PIN_D4},			// 14	// SL: 		Potential Anode to POTENTIAL_2
						{BOARD1, PIN_D5},			// 15	// SL:		Potential Cathode to POTENTIAL_2
						{BOARD2, PIN_A1},			// 16	// BV:		HV+ to POWER_2
						{BOARD2, PIN_A2},			// 17	// BV:		HV- to POWER_2
						{BOARD2, PIN_A4},			// 18	// Gate:	Power Anode to POWER_2
						{BOARD2, PIN_A5},			// 19	// Gate:	Power Cathode to POWER_2
						{BOARD2, PIN_B1},			// 20	// BV:		HV+ to POWER_3
						{BOARD2, PIN_B2},			// 21	// BV:		HV- to POWER_3
						{BOARD2, PIN_B4},			// 22	// Gate:	Power Anode to POWER_3
						{BOARD2, PIN_B5},			// 23	// Gate:	Power Cathode to POWER_3
						{BOARD2, PIN_C1},			// 24	// BVLP:	LPHV+ to POTENTIAL_3
						{BOARD2, PIN_C2},			// 25	// BVLP:	LPHV- to POTENTIAL_3
						{BOARD2, PIN_C4},			// 26	// SL: 		Potential Anode to POTENTIAL_3
						{BOARD2, PIN_C5},			// 27	// SL:		Potential Cathode to POTENTIAL_3
						{BOARD2, PIN_D1},			// 28	// BV:		HV+ to POWER_1
						{BOARD2, PIN_D2},			// 29	// BV:		HV- to POWER_1
						{BOARD2, PIN_D4},			// 30	// Gate:	Power Anode to POWER_1
						{BOARD2, PIN_D5},			// 31	// Gate:	Power Cathode to POWER_1
						{BOARD3, PIN_A1},			// 32	// BVLP:	HV+ to CTRL_A2
						{BOARD3, PIN_A2},			// 33
						{BOARD3, PIN_A4},			// 34	// SL:		Control Anode to CTRL_A2
						{BOARD3, PIN_A5},			// 35	// Gate:	Control Anode to CTRL_A2
						{BOARD3, PIN_B1},			// 36	// BVLP:	HV+ to CTRL_C2
						{BOARD3, PIN_B2},			// 37
						{BOARD3, PIN_B4},			// 38	// SL:		Control Cathode to CTRL_C2
						{BOARD3, PIN_B5},			// 39	// Gate:	Control Cathode to CTRL_C2
						{BOARD3, PIN_C1},			// 40	// BVLP:	HV+ to CTRL_A1
						{BOARD3, PIN_C2},			// 41
						{BOARD3, PIN_C4},			// 42	// SL:		Control Anode to CTRL_A1
						{BOARD3, PIN_C5},			// 43	// Gate:	Control Anode to CTRL_A1
						{BOARD3, PIN_D1},			// 44	// BVLP:	HV+ to CTRL_C1
						{BOARD3, PIN_D2},			// 45
						{BOARD3, PIN_D4},			// 46	// SL:		Control Cathode to CTRL_C1
						{BOARD3, PIN_D5}			// 47	// Gate:	Control Cathode to CTRL_C1
				};
#endif

// No more
