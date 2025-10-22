#ifndef __STORAGE_DESCRIPTION_H
#define __STORAGE_DESCRIPTION_H

// Include
#include "stdinc.h"
#include "SaveToFlash.h"

// Variables
extern const RecordDescription StorageDescription[];
extern Int32U TablePointers[];
extern const Int16U StorageSize;

extern const CounterDescription *CounterStorageDescription;
extern CounterData *CounterTablePointers;
extern Int16U CounterStorageSize;

extern const CounterDescription CounterStorageDescription2[];
extern const CounterDescription CounterStorageDescription4[];
extern const CounterDescription CounterStorageDescription6[];
extern const CounterDescription CounterStorageDescription6Gate4Wire[];
extern CounterData CounterTablePointers2[];
extern CounterData CounterTablePointers4[];
extern CounterData CounterTablePointers6[];
extern CounterData CounterTablePointers6Gate4Wire[];
extern const Int16U CounterStorageSize2;
extern const Int16U CounterStorageSize4;
extern const Int16U CounterStorageSize6;
extern const Int16U CounterStorageSize6Gate4Wire;

#endif // __STORAGE_DESCRIPTION_H
