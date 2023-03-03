// Header
#include "SaveToFlash.h"

// Includes
#include "Flash.h"
#include "ZwSysCtrl.h"
#include "SysConfig.h"

// Definitions
#define FLASH_SECTOR				SECTORF
#define FLASH_START_ADDR			0x3E0000
#define MAX_DESCRIPTION_LEN			64

// Types
typedef enum __DataType
{
	DT_Int16U = 0,
	DT_Int16S,
	DT_Int32U,
	DT_Int32S,
	DT_Float,
	DT_Char
} DataType;

typedef struct __RecordDescription
{
	char Description[MAX_DESCRIPTION_LEN];
	DataType Type;
	Int16U Length;
	Boolean LoadOnBoot;
} RecordDescription;

// Variables
static const RecordDescription StorageDescription[] =
{
		{"Register 192",	DT_Int16U, 1,	FALSE},
		{"Switch1 cycles",	DT_Int32U, 1,	TRUE},
		{"Voltage EP1",		DT_Int16U, 100, FALSE}
};
static Int32U TablePointers[sizeof(StorageDescription) / sizeof(StorageDescription[0])] = {0};
static const Int16U StorageSize = sizeof(StorageDescription) / sizeof(StorageDescription[0]);

// Forward functions


// Functions
//
void STF_AssignPointer(Int16U Index, Int32U Pointer)
{
	if(Index < StorageSize)
		TablePointers[Index] = Pointer;
}
// ----------------------------------------

void STF_SaveToFlash()
{
	ZwSystem_DisableDog();
	DINT;

	Status = Flash_Erase(FLASH_SECTOR, (FLASH_ST *)&FlashStatus);

	Int16U i;
	for(i = 0; i < StorageSize; i++)
	{
		if(TablePointers[i])
		{
			Int16U BufferSize = StorageDescription[i].Length * \
					(StorageDescription[i].Type == DT_Int32U || StorageDescription[i].Type == DT_Int32S) ? 2 : 1;
			Status = Flash_Program((pInt16U)FLASH_START_ADDR, (pInt16U)TablePointers[i], BufferSize, (FLASH_ST *)&FlashStatus);
		}
	}

	EINT;
	ZwSystem_EnableDog(SYS_WD_PRESCALER);
}
// ----------------------------------------

void STF_LoadFromFlash()
{
}
// ----------------------------------------
