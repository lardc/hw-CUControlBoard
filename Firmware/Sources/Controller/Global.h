﻿// ----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __GLOBAL_H
#define __GLOBAL_H


// Include
#include "stdinc.h"


// Constants
//
// Password to unlock non-volatile area for write
#define ENABLE_LOCKING				FALSE
#define UNLOCK_PWD_1				1
#define UNLOCK_PWD_2				1
#define UNLOCK_PWD_3				1
#define UNLOCK_PWD_4				1
//
#define DT_EPROM_ADDRESS			0
#define EP_COUNT					1
#define	SCCI_TIMEOUT_TICKS  		1000
#define COMM_DELAY_LONG_MS			500
#define COMM_DELAY_NONE_MS			100
#define COMM_DELAY_SHORT_MS			20
#define PRESSURE_FILTER_T			750
#define IGNORE_ON_SFTY_CHANGE_MS	100		// Таймаут игнорирования входа безопасности после переконфигурации, мс
#define SAFETY_RELEASE_TIMEOUT		300		// Время до снятия сигнала безопасности, мс


#endif // __GLOBAL_H
