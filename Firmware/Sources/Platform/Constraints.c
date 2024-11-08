﻿// ----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "Constraints.h"
#include "DeviceObjectDictionary.h"
#include "CommutationTable.h"

#define NO		0	// equal to FALSE
#define YES		1	// equal to TRUE

// Constants
//
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] =
                                      {
											   {NO, YES, NO},															// 0
											   {NO, YES, NO},															// 1
											   {NO, YES, NO},															// 2
											   {NO, YES, NO},															// 3
											   {NO, YES, NO},															// 4
											   {NO, YES, NO},															// 5
											   {0, COMM_CUHV6_GATE_4WIRE, 0},											// 6
											   {NO, YES, YES},															// 7
											   {NO, YES, NO},															// 8
											   {NO, YES, NO},															// 9
											   {0, MAX_SAFETY_RELAY_HYST_ALT, 0},										// 10
											   {0, 0, 0},																// 11
											   {0, 0, 0},																// 12
											   {0, 0, 0},																// 13
											   {0, 0, 0},																// 14
											   {0, 0, 0},																// 15
											   {0, 0, 0},																// 16
											   {0, 0, 0},																// 17
											   {0, 0, 0},																// 18
											   {0, 0, 0},																// 19
											   {0, 0, 0},																// 20
											   {0, 0, 0},																// 21
											   {0, 0, 0},																// 22
											   {0, 0, 0},																// 23
											   {0, 0, 0},																// 24
											   {0, 0, 0},																// 25
											   {0, 0, 0},																// 26
											   {0, 0, 0},																// 27
											   {0, 0, 0},																// 28
											   {0, 0, 0},																// 29
											   {0, 0, 0},																// 30
											   {0, 0, 0},																// 31
											   {0, 0, 0},																// 32
											   {0, 0, 0},																// 33
											   {0, 0, 0},																// 34
											   {0, 0, 0},																// 35
											   {0, 0, 0},																// 36
											   {0, 0, 0},																// 37
											   {0, 0, 0},																// 38
											   {0, 0, 0},																// 39
											   {0, 0, 0},																// 40
											   {0, 0, 0},																// 41
											   {0, 0, 0},																// 42
											   {0, 0, 0},																// 43
											   {0, 0, 0},																// 44
											   {0, 0, 0},																// 45
											   {0, 0, 0},																// 46
											   {0, 0, 0},																// 47
											   {0, 0, 0},																// 48
											   {0, 0, 0},																// 49
											   {0, 0, 0},																// 50
											   {0, 0, 0},																// 51
											   {0, 0, 0},																// 52
											   {0, 0, 0},																// 53
											   {0, 0, 0},																// 54
											   {0, 0, 0},																// 55
											   {0, 0, 0},																// 56
											   {0, 0, 0},																// 57
											   {0, 0, 0},																// 58
											   {0, 0, 0},																// 59
											   {0, 0, 0},																// 60
											   {0, 0, 0},																// 61
											   {0, 0, 0},																// 62
                                    		   {INT16U_MAX, 0, 0}														// 63
                                      };

TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] =
                                      {
											   {0, COMMUTATION2_TABLE_SIZE - 1, 0},										// 64
											   {0, INT16U_MAX, 0},														// 65
											   {0, COMMUTATION2_TABLE_SIZE - 1, 0},										// 66
											   {0, INT16U_MAX, 0},														// 67
											   {0, 0, 0},																// 68
											   {0, 0, 0},																// 69
											   {MODULE_DIRECT, MODULE_MD3_BP, MODULE_DIRECT},							// 70
											   {1, 2, 1},																// 71
											   {0, INT16U_MAX, 0},														// 72
											   {0, 0, 0},																// 73
											   {0, 0, 0},																// 74
											   {0, 0, 0},																// 75
											   {0, 0, 0},																// 76
											   {0, 0, 0},																// 77
											   {0, 0, 0},																// 78
											   {0, 0, 0},																// 79
											   {NO, YES, YES},															// 80
											   {NO, YES, YES},															// 81
											   {NO, YES, YES},															// 82
											   {NO, YES, YES},															// 83
											   {0, 0, 0},																// 84
											   {0, 0, 0},																// 85
											   {0, 0, 0},																// 86
											   {0, 0, 0},																// 87
											   {0, 0, 0},																// 88
											   {0, 0, 0},																// 89
											   {0, 0, 0},																// 90
											   {0, 0, 0},																// 91
											   {0, 0, 0},																// 92
											   {0, 0, 0},																// 93
											   {0, 0, 0},																// 94
                                    		   {INT16U_MAX, 0, 0}														// 95
                                      };
