﻿// ----------------------------------------
// Device object dictionary
// ----------------------------------------

#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER			1	// Enable
#define ACT_DISABLE_POWER			2	// Disable
#define ACT_CLR_FAULT				3	// Clear fault
#define ACT_CLR_WARNING				4	// Clear warning
//
#define ACT_DBG_INDICATORS			10	// Подача импульса на индикаторы Safety и Pressure
#define ACT_DBG_BLACK_BOX			11	// Подача импульса на реле BlackBox
#define ACT_DBG_CS_STOP_OFF			12	// Отключение реле остановки ЗУ
#define ACT_DBG_CS_STOP_ON			13	// Включение реле остановки ЗУ
//
#define ACT_SET_ACTIVE				100	// Switch block to active mode
#define ACT_SET_INACTIVE			101	// Switch block to inactive mode
//
#define ACT_WRITE_PIN				102	// Write raw pin value to the cache
#define ACT_RAW_ACCESS				103 // Raw access to the cache
#define ACT_FLUSH_REG				104	// Flush values to physical register
//
#define ACT_COMM2_4_NONE			110 // Disconnect all
#define ACT_COMM2_4_GATE			111 // Connect Gate tester
#define ACT_COMM2_4_SL				112 // Connect Static Losses tester
#define ACT_COMM2_4_BV_D			113 // Connect direct BV tester
#define ACT_COMM2_4_BV_R			114 // Connect reverse BV tester
#define ACT_COMM2_4_NO_PE			115	// Connect other blocks (disconnect protective earth from lines)
#define ACT_COMM2_4_GATE_SL			116	// Connect GTU and SL for Ih - GOST measurement
#define ACT_COMM2_4_VGNT			117	// Connect GTU and BVT for Vgnt/Ignt measurement
#define ACT_COMM2_4_TOU				118	// Connect TOU measurement
//
#define ACT_COMM6_NONE				120 // Disconnect all
#define ACT_COMM6_GATE				121 // Connect Gate tester
#define ACT_COMM6_SL				122 // Connect Static Losses tester
#define ACT_COMM6_BV_D				123 // Connect direct BV tester
#define ACT_COMM6_BV_R				124 // Connect reverse BV tester
#define ACT_COMM6_NO_PE				125 // Connect other blocks (disconnect protective earth from lines)
#define ACT_COMM6_GATE_SL			126	// Connect GTU and SL for Ih - GOST measurement
//
#define ACT_SAVE_TO_ROM				200	// Save parameters to EEPROM module
#define ACT_RESTORE_FROM_ROM		201	// Restore parameters from EEPROM module
#define ACT_RESET_TO_DEFAULT		202	// Reset parameters to default values (only in controller memory)
#define ACT_LOCK_NV_AREA			203	// Lock modifications of parameters area
#define ACT_UNLOCK_NV_AREA			204	// Unlock modifications of parameters area (password-protected)
//
#define ACT_BOOT_LOADER_REQUEST		320	// Request reboot to bootloader
#define ACT_READ_SYMBOL				330	// Выполнить чтение символа из памяти
#define ACT_SELECT_MEM_LABEL		331	// Переместить указатель считывания в область метки


// REGISTERS
//
// Конфигурация аппаратных особенностей блока
#define REG_BB_NC_RELAY				0	// Флаг использования НЗ-реле в BlackBox
#define REG_USE_VGT_2WIRE_MODE		1	// Использовать двухпроводную схему при измерении Vgt
#define REG_PRESSURE_DISABLE		2	// Запретить мониторинг давления
#define REG_SAFETY_DISABLE			3	// Запретить мониторинг контура безопасности
#define REG_PCB_V20					4	// Для PCB v.2.0 используется инверсия сигнала давления
#define REG_PCB_V22_AND_LOWER		5	// Для PCB v.2.2 и ниже используются особые линии реле безопасности и BlackBox
#define REG_COMM_NUM				6	// Выбор режима коммутации
										// 0 или 2 - режим CUHV2 или CUHV4 на базе ЭМ CURelyBoard v.2.x
										// 4 - режим CUHV4 на базе ЭМ CURelyBoard v.3.x
										// 6 - режим CUHV6
										// 7 - режим CUHV6 с четырёхпроводным GTU
#define REG_SAFETY_HW_MODE			7	// Аппаратный режим контура безопасности без возможности отключения (игнорирует регистр 3)
#define REG_IGNORE_SAFETY_SEN3		8	// Отключение обработки входа безопасности 3 (используется при заданном регистре 7)
#define REG_IGNORE_SAFETY_SEN4		9	// Отключение обработки входа безопасности 4 (используется при заданном регистре 7)
#define REG_SAFETY_RELAY_HYST_ALT	10	// Альтернативная уставка по гистерезису реле безопасности (в мс)
//
#define REG_TABLE_INDEX				64	// Commutation table index
#define REG_TABLE_ACTION			65	// Boolean variable for action
#define REG_RAW_BOARD				66	// Raw value for board number
#define REG_RAW_MASK				67	// Raw value for board mask
//
#define REG_MODULE_TYPE				70	// Module type
#define REG_MODULE_POS				71	// Active module position
#define REG_MODULE_CASE				72	// Module case
//
#define REG_EN_SFTY_IN1				80	// Enable safety input #1
#define REG_EN_SFTY_IN2				81	// Enable safety input #2
#define REG_EN_SFTY_IN3				82	// Enable safety input #3
#define REG_EN_SFTY_IN4				83	// Enable safety input #4
//
#define REG_PWD_1					91	// Unlock password location 1
#define REG_PWD_2					92	// Unlock password location 2
#define REG_PWD_3					93	// Unlock password location 3
#define REG_PWD_4					94	// Unlock password location 4
//
// ----------------------------------------
//
#define REG_DEV_STATE				96	// Device state
#define REG_FAULT_REASON			97	// Fault reason in the case DeviceState -> FAULT
#define REG_DISABLE_REASON			98	// Fault reason in the case DeviceState -> DISABLED
#define REG_WARNING					99	// Warning if present
#define REG_PROBLEM					100	// Problem reason
//
#define REG_PRES_SEN_STATE			110	// Current state of pressure sensor output
#define REG_SC_STATE				111	// Current state of safety circuit output
//
#define REG_CAN_BUSOFF_COUNTER		120 // Counter of bus-off states
#define REG_CAN_STATUS_REG			121	// CAN status register (32 bit)
#define REG_CAN_STATUS_REG_32		122
#define REG_CAN_DIAG_TEC			123	// CAN TEC
#define REG_CAN_DIAG_REC			124	// CAN REC
//
// ----------------------------------------
//
#define REG_FWINFO_SLAVE_NID		256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID		257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN			260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN		261	// Begining of the information string record
//
#define REG_MEM_SYMBOL				299	// Считанный по адресу памяти символ

// MODULE TYPES
//
#define MODULE_DIRECT				0
#define MODULE_MT1					1
#define MODULE_MD1					2
#define MODULE_MT3					3
#define MODULE_MT4					4
#define MODULE_MT5					5
#define MODULE_MD3					6
#define MODULE_MD4					7
#define MODULE_MD5					8
#define MODULE_MTD3					9
#define MODULE_MDT3					10
#define MODULE_MTD4					11
#define MODULE_MDT4					12
#define MODULE_MTD5					13
#define MODULE_MDT5					14
#define MODULE_REVERSE				15
#define MODULE_MD3_BP				22

// MODULE CASES
//
#define MODULE_CASE_A2				1001
#define MODULE_CASE_B1				1006
#define MODULE_CASE_C1				1002
#define MODULE_CASE_D0				1005
#define MODULE_CASE_E0				1003
#define MODULE_CASE_F1				1004
#define MODULE_CASE_ADAP			1007

// FAULT CODES
//
#define FAULT_NONE					0	// No fault
// 301
#define FAULT_LOW_PRESSURE			302	// Low pressure detected

// DISABLE CODES
//
#define DISABLE_NONE				0	// No fault
//
#define DISABLE_BAD_CLOCK			1001	// Problem with main oscillator

// WARNING CODES
//
#define WARNING_NONE				0	// No warning
//
#define WARNING_WATCHDOG_RESET		1001	// System has been reseted by WD

// USER ERROR CODES
//
#define ERR_NONE					0	// No error
#define ERR_CONFIGURATION_LOCKED	1	// Device is locked for writing
#define ERR_OPERATION_BLOCKED		2	// Operation can't be done due to current device state
#define ERR_DEVICE_NOT_READY		3	// Device isn't ready to switch state
#define ERR_WRONG_PWD				4	// Wrong password - unlock failed
#define ERR_WRONG_CMD				5	// Wrong command

#endif // __DEV_OBJ_DIC_H
