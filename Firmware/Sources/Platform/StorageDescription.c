// Header
#include "StorageDescription.h"

// Variables
const RecordDescription StorageDescription[] =
{
		{"Register 192",	DT_Int16U, 1,		FALSE},
		{"Voltage EP1",		DT_Int16U, 100,		FALSE},
		{"Max current",		DT_Int32U, 1,		TRUE},
		{"Max voltage",		DT_Int16U, 1,		TRUE}
};

Int32U TablePointers[sizeof(StorageDescription) / sizeof(StorageDescription[0])] = {0};
const Int16U StorageSize = sizeof(StorageDescription) / sizeof(StorageDescription[0]);
