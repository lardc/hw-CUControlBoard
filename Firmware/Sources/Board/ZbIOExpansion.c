// ----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZbIOExpansion.h"
//
#include "SysConfig.h"
#include "ZwDSP.h"
#include "CommutationTable.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"


// Constants
//
#define IOE_OUT_CL					16
#define IO_REGISTER_WRITE_DELAY_US	10
#define MAX_OUT_BOARDS				COMMUTATION6_TABLE_SIZE


// Variables
//
static Int16U CurrentOutputValues[MAX_OUT_BOARDS];
static Boolean SafetyTrig = FALSE;

static CommutationTableItem *UsedCommutationTable = (CommutationTableItem *)CommutationTable2;
static Int16U UsedBoardsCount = COMMUTATION2_EXT_BOARDS;


// Functions
//
void ZbIOE_Init()
{
	// Init SPI-C
	ZwSPId_Init(TRUE, IOE_BAUDRATE, IOE_OUT_CL, IOE_PLR, IOE_PHASE, ZW_SPI_INIT_TX | ZW_SPI_INIT_CS, FALSE, FALSE);
	ZwSPId_InitFIFO(0, 0);
	ZwSPId_ConfigInterrupts(FALSE, FALSE);
	
	// Configure /OE
	ZwGPIO_WritePin(IOE_OE, FALSE);
	ZwGPIO_PinToOutput(IOE_OE);

	// Set values in the register to zero
	ZbIOE_RegisterReset();

	// Enable /OE
	DELAY_US(IO_REGISTER_WRITE_DELAY_US);
	ZwGPIO_WritePin(IOE_OE, TRUE);
}
// ----------------------------------------

void ZbIOE_ExternalOutput(Boolean Enable)
{
	ZwGPIO_WritePin(IOE_OE, Enable);
}
// ----------------------------------------

void ZbIOE_RegisterReset()
{
	// Set values to zero
	ZbIOE_OutputValuesReset();
	// Flush to physical register
	ZbIOE_RegisterFlushWrite();
}
// ----------------------------------------

void ZbIOE_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	if (TurnOn)
		CurrentOutputValues[UsedCommutationTable[TableID].BoardNum] |= UsedCommutationTable[TableID].Bit;
	else
		CurrentOutputValues[UsedCommutationTable[TableID].BoardNum] &= ~UsedCommutationTable[TableID].Bit;
}
// ----------------------------------------

void ZbIOE_OutputValuesDirect(Int16U BoardID, Int16U Mask)
{
	if (BoardID >= MAX_OUT_BOARDS)
		return;

	CurrentOutputValues[BoardID] = Mask;
}
// ----------------------------------------

void ZbIOE_SafetyTrigFlag()
{
	SafetyTrig = TRUE;
}
// ----------------------------------------

void ZbIOE_OutputValuesReset()
{
	Int16U i;
	for (i = 0; i < MAX_OUT_BOARDS; ++i)
		CurrentOutputValues[i] = 0;

	if(SafetyTrig)
		SafetyTrig = FALSE;
	else
	{
		if(DataTable[REG_PCB_V22_AND_LOWER])
			ZbIOE_OutputValuesCompose(T2_OLD_SAFETY_RELAY, TRUE);
	}
}
// ----------------------------------------

void ZbIOE_RegisterFlushWrite()
{
	Int16U i, CurrentOutputValuesCopy[MAX_OUT_BOARDS];

	// Change bytes order
	for (i = 0; i < UsedBoardsCount; ++i)
		CurrentOutputValuesCopy[i] = CurrentOutputValues[UsedBoardsCount - 1 - i];

	ZwSPId_Send(CurrentOutputValuesCopy, sizeof(Int16U) * UsedBoardsCount, IOE_OUT_CL, STTNormal);
}
// ----------------------------------------


