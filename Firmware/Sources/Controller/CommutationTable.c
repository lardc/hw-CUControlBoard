// ----------------------------------------
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

#define BOARD1	0
#define BOARD2	1
#define BOARD3	2

// Constants
//
const CommutationTableItem CommutationTable2[COMMUTATION2_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// BVT:		HV2 to POWER_A
						{BOARD1, PIN_A2},			// 1	// BVT:		HV1 to POWER_A
						{BOARD1, PIN_A4},			// 2	// GTU:		Power Anode to POWER_A
						{BOARD1, PIN_A5},			// 3
						{BOARD1, PIN_B1},			// 4	// BVT:		HV2 to POWER_C
						{BOARD1, PIN_B2},			// 5	// BVT:		HV1 to POWER_C
						{BOARD1, PIN_B4},			// 6	// GTU+SL:	Power and Control Cathode to POWER_C
						{BOARD1, PIN_B5},			// 7
						{BOARD1, PIN_C1},			// 8
						{BOARD1, PIN_C2},			// 9
						{BOARD1, PIN_C4},			// 10	// GTU:		GTU Control Anode to CTRL_A
						{BOARD1, PIN_C5},			// 11	// SL: 		SL Control Anode to CTRL_A
						{BOARD1, PIN_D1},			// 12
						{BOARD1, PIN_D2},			// 13
						{BOARD1, PIN_D4},			// 14	// GTU		GTU Potential Control Anode to POTENTIAL_CTRL_A
						{BOARD1, PIN_D5},			// 15	// SL:		SL control Cathode to CTRL_C (для двухпроводной схемы Vgt)

						{BOARD2, PIN_A1},			// 16
						{BOARD2, PIN_A2},			// 17
						{BOARD2, PIN_A4},			// 18
						{BOARD2, PIN_A5},			// 19	// BB:		Упраление реле в BlackBox в зависимости от типа (НО / НЗ)
						{BOARD2, PIN_B1},			// 20
						{BOARD2, PIN_B2},			// 21
						{BOARD2, PIN_B4},			// 22	// SL:		HC POWER (REVERSE)
						{BOARD2, PIN_B5},			// 23	// SL:		HC POWER
						{BOARD2, PIN_C1},			// 24
						{BOARD2, PIN_C2},			// 25
						{BOARD2, PIN_C4},			// 26	// SL: 		Potential Anode to POTENTIAL_A
						{BOARD2, PIN_C5},			// 27	// SL:		Potential Anode to POTENTIAL_A (REVERSE)
						{BOARD2, PIN_D1},			// 28
						{BOARD2, PIN_D2},			// 29
						{BOARD2, PIN_D4},			// 30	// SL: 		Potential Cathode to POTENTIAL_C
						{BOARD2, PIN_D5},			// 31	// GTU		GTU Potential Control Cathode to POTENTIAL_CTRL_C
															// SL: 		Potential Cathode to POTENTIAL_C (REVERSE)
				};

const CommutationTableItem CommutationTable4[COMMUTATION4_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// BVT:		HV+ to POW_A
						{BOARD1, PIN_A2},			// 1	// BVT:		HV+ to POW_C
						{BOARD1, PIN_A4},			// 2	// GTU:		Power Anode to POW_A
						{BOARD1, PIN_A5},			// 3	// GTU:		Power Anode to POW_C
						{BOARD1, PIN_B1},			// 4	// BVT:		HV- to POW_C
						{BOARD1, PIN_B2},			// 5	// BVT:		HV- to POW_A
						{BOARD1, PIN_B4},			// 6	// GTU: 	Power and Control Cathode to POW_A
						{BOARD1, PIN_B5},			// 7	// GTU: 	Power and Control Cathode to POW_C
						{BOARD1, PIN_C1},			// 8	// SL: 		Control Cathode (C-) to POW_A
						{BOARD1, PIN_C2},			// 9	// SL: 		Control Cathode	(C-) to POW_C
						{BOARD1, PIN_C4},			// 10	// SL: 		Potential Anode to POT_A
						{BOARD1, PIN_C5},			// 11	// SL: 		Potential Anode to POT_C
						{BOARD1, PIN_D1},			// 12	// SL: 		Potential Cathode to POT_A
						{BOARD1, PIN_D2},			// 13	// SL: 		Potential Cathode to POT_C
						{BOARD1, PIN_D4},			// 14	// GTU: 	Potential Control Cathode to POT_A
						{BOARD1, PIN_D5},			// 15	// GTU: 	Potential Control Cathode to POT_C

						{BOARD2, PIN_A1},			// 16
						{BOARD2, PIN_A2},			// 17
						{BOARD2, PIN_A4},			// 18
						{BOARD2, PIN_A5},			// 19	// BB:		Disconnect control
						{BOARD2, PIN_B1},			// 20
						{BOARD2, PIN_B2},			// 21
						{BOARD2, PIN_B4},			// 22	// BCUHC4:	IN+/IN- to OUI-/OUT+
						{BOARD2, PIN_B5},			// 23	// BCUHC4:	IN+/IN- to OUT+/OUT-
						{BOARD2, PIN_C1},			// 24
						{BOARD2, PIN_C2},			// 25
						{BOARD2, PIN_C4},			// 26	// GTU:	Control Anode to CTRL_A
						{BOARD2, PIN_C5},			// 27	// GTU:	Potential Control Anode to POT_CTRL_A
						{BOARD2, PIN_D1},			// 28
						{BOARD2, PIN_D2},			// 29
						{BOARD2, PIN_D4},			// 30	// SL:		Control Anode (C+) to CTRL_A
						{BOARD2, PIN_D5},			// 31
				};

const CommutationTableItem CommutationTable6[COMMUTATION6_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// SL:		HC+ to POWER_2		// 2-top
						{BOARD1, PIN_A2},			// 1	// SL:		HC+ to POWER_3		// 3-top
						{BOARD1, PIN_A4},			// 2	// SL:		HC+ to POWER_1		// 1-top
						{BOARD1, PIN_A5},			// 3	// SL:		HC- to POWER_1		// 1-bottom
						{BOARD1, PIN_B1},			// 4	// BVTLP:	HV- to Isolation
						{BOARD1, PIN_B2},			// 5
						{BOARD1, PIN_B4},			// 6	// SL:		HC- to POWER_2		// 2-bottom
						{BOARD1, PIN_B5},			// 7	// SL:		HC- to POWER_3		// 3-bottom
						{BOARD1, PIN_C1},			// 8	// BVTLP:	LPHV+ to POTENTIAL_1
						{BOARD1, PIN_C2},			// 9	// BVTLP:	LPHV- to POTENTIAL_1
						{BOARD1, PIN_C4},			// 10	// SL: 		Potential Anode to POTENTIAL_1
						{BOARD1, PIN_C5},			// 11	// SL: 		Potential Cathode to POTENTIAL_1
						{BOARD1, PIN_D1},			// 12	// BVTLP:	LPHV+ to POTENTIAL_2
						{BOARD1, PIN_D2},			// 13	// BVTLP:	LPHV- to POTENTIAL_2
						{BOARD1, PIN_D4},			// 14	// SL: 		Potential Anode to POTENTIAL_2
						{BOARD1, PIN_D5},			// 15	// SL:		Potential Cathode to POTENTIAL_2

						{BOARD2, PIN_A1},			// 16	// BVT:		HV+ to POWER_2
						{BOARD2, PIN_A2},			// 17	// BVT:		HV- to POWER_2
						{BOARD2, PIN_A4},			// 18	// GTU:		Power Anode to POWER_2
						{BOARD2, PIN_A5},			// 19	// GTU:		Power Cathode to POWER_2
						{BOARD2, PIN_B1},			// 20	// BVT:		HV+ to POWER_3
						{BOARD2, PIN_B2},			// 21	// BVT:		HV- to POWER_3
						{BOARD2, PIN_B4},			// 22	// GTU:		Power Anode to POWER_3
						{BOARD2, PIN_B5},			// 23	// GTU:		Power Cathode to POWER_3
						{BOARD2, PIN_C1},			// 24	// BVTLP:	LPHV+ to POTENTIAL_3
						{BOARD2, PIN_C2},			// 25	// BVTLP:	LPHV- to POTENTIAL_3
						{BOARD2, PIN_C4},			// 26	// SL: 		Potential Anode to POTENTIAL_3
						{BOARD2, PIN_C5},			// 27	// SL:		Potential Cathode to POTENTIAL_3
						{BOARD2, PIN_D1},			// 28	// BVT:		HV+ to POWER_1
						{BOARD2, PIN_D2},			// 29	// BVT:		HV- to POWER_1
						{BOARD2, PIN_D4},			// 30	// GTU:		Power Anode to POWER_1
						{BOARD2, PIN_D5},			// 31	// GTU:		Power Cathode to POWER_1

						{BOARD3, PIN_A1},			// 32	// BVTLP:	HV+ to CTRL_A2
						{BOARD3, PIN_A2},			// 33
						{BOARD3, PIN_A4},			// 34	// SL:		Control Anode to CTRL_A2
						{BOARD3, PIN_A5},			// 35	// GTU:		Control Anode to CTRL_A2
						{BOARD3, PIN_B1},			// 36	// BVTLP:	HV+ to CTRL_C2
						{BOARD3, PIN_B2},			// 37
						{BOARD3, PIN_B4},			// 38	// SL:		Control Cathode to CTRL_C2
						{BOARD3, PIN_B5},			// 39	// GTU:		Control Cathode to CTRL_C2
						{BOARD3, PIN_C1},			// 40	// BVTLP:	HV+ to CTRL_A1
						{BOARD3, PIN_C2},			// 41
						{BOARD3, PIN_C4},			// 42	// SL:		Control Anode to CTRL_A1
						{BOARD3, PIN_C5},			// 43	// GTU:		Control Anode to CTRL_A1
						{BOARD3, PIN_D1},			// 44	// BVTLP:	HV+ to CTRL_C1
						{BOARD3, PIN_D2},			// 45
						{BOARD3, PIN_D4},			// 46	// SL:		Control Cathode to CTRL_C1
						{BOARD3, PIN_D5}			// 47	// GTU:		Control Cathode to CTRL_C1
				};

const CommutationTableItem CommutationTable6Gate4Wire[COMMUTATION6_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// SL:		HC+ to POWER_2		// 2-top
						{BOARD1, PIN_A2},			// 1	// SL:		HC+ to POWER_3		// 3-top
						{BOARD1, PIN_A4},			// 2	// SL:		HC+ to POWER_1		// 1-top
						{BOARD1, PIN_A5},			// 3	// SL:		HC- to POWER_1		// 1-bottom
						{BOARD1, PIN_B1},			// 4	// PE:		Special PE to POWER_1 (inverted)
						{BOARD1, PIN_B2},			// 5	// PE:		Special PE to POWER_2 (inverted)
						{BOARD1, PIN_B4},			// 6	// PE:		Special PE to POWER_3 (inverted)
						{BOARD1, PIN_B5},			// 7
						{BOARD1, PIN_C1},			// 8	// SL:		HC- to POWER_2		// 2-bottom
						{BOARD1, PIN_C2},			// 9	// SL:		HC- to POWER_3		// 3-bottom
						{BOARD1, PIN_C4},			// 10	// SL: 		Potential Anode to POTENTIAL_1
						{BOARD1, PIN_C5},			// 11	// SL+GTU:	Potential Cathode to POTENTIAL_1
						{BOARD1, PIN_D1},			// 12
						{BOARD1, PIN_D2},			// 13
						{BOARD1, PIN_D4},			// 14	// SL: 		Potential Anode to POTENTIAL_2
						{BOARD1, PIN_D5},			// 15	// SL+GTU:	Potential Cathode to POTENTIAL_2

						{BOARD2, PIN_A1},			// 16	// BVT:		HV+ to POWER_2
						{BOARD2, PIN_A2},			// 17	// BVT:		HV- to POWER_2
						{BOARD2, PIN_A4},			// 18	// GTU:		Power Anode to POWER_2
						{BOARD2, PIN_A5},			// 19	// GTU:		Power and Control Cathode to POWER_2
						{BOARD2, PIN_B1},			// 20	// BVT:		HV+ to POWER_3
						{BOARD2, PIN_B2},			// 21	// BVT:		HV- to POWER_3
						{BOARD2, PIN_B4},			// 22	// GTU:		Power Anode to POWER_3
						{BOARD2, PIN_B5},			// 23	// GTU:		Power and Control Cathode to POWER_3
						{BOARD2, PIN_C1},			// 24
						{BOARD2, PIN_C2},			// 25
						{BOARD2, PIN_C4},			// 26	// SL: 		Potential Anode to POTENTIAL_3
						{BOARD2, PIN_C5},			// 27	// SL+GTU:	Potential Cathode to POTENTIAL_3
						{BOARD2, PIN_D1},			// 28	// BVT:		HV+ to POWER_1
						{BOARD2, PIN_D2},			// 29	// BVT:		HV- to POWER_1
						{BOARD2, PIN_D4},			// 30	// GTU:		Power Anode to POWER_1
						{BOARD2, PIN_D5},			// 31	// GTU:		Power and Control Cathode to POWER_1

						{BOARD3, PIN_A1},			// 32
						{BOARD3, PIN_A2},			// 33
						{BOARD3, PIN_A4},			// 34	// SL:		Control Anode to CTRL_A2
						{BOARD3, PIN_A5},			// 35	// GTU:		Control Anode to CTRL_A2
						{BOARD3, PIN_B1},			// 36
						{BOARD3, PIN_B2},			// 37
						{BOARD3, PIN_B4},			// 38	// GTU:		Potential Control to CTRL_A2_POT
						{BOARD3, PIN_B5},			// 39
						{BOARD3, PIN_C1},			// 40
						{BOARD3, PIN_C2},			// 41
						{BOARD3, PIN_C4},			// 42	// SL:		Control Anode to CTRL_A1
						{BOARD3, PIN_C5},			// 43	// GTU:		Control Anode to CTRL_A1
						{BOARD3, PIN_D1},			// 44
						{BOARD3, PIN_D2},			// 45
						{BOARD3, PIN_D4},			// 46	// GTU:		Potential Control to CTRL_A1_POT
						{BOARD3, PIN_D5}			// 47
				};
