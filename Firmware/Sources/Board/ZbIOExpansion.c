// ----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZbIOExpansion.h"
//
#include "SysConfig.h"
#include "ZwDSP.h"
#include "CommutationTable.h"


// Constants
//
#define IOE_OUT_CL					16
#define IO_REGISTER_WRITE_DELAY_US	10


// Variables
//
static Int16U CurrentOutputValues[COMMUTATION_EXT_BOARDS];


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
		CurrentOutputValues[CommutationTable[TableID].BoardNum] |= CommutationTable[TableID].Bit;
	else
		CurrentOutputValues[CommutationTable[TableID].BoardNum] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------

void ZbIOE_OutputValuesDirect(Int16U BoardID, Int16U Mask)
{
	if (BoardID >= COMMUTATION_EXT_BOARDS)
		return;

	CurrentOutputValues[BoardID] = Mask;
}
// ----------------------------------------

void ZbIOE_OutputValuesReset()
{
	Int16U i;

	for (i = 0; i < COMMUTATION_EXT_BOARDS; ++i)
		CurrentOutputValues[i] = 0;
}
// ----------------------------------------

void ZbIOE_RegisterFlushWrite()
{
	Int16U i, CurrentOutputValuesCopy[COMMUTATION_EXT_BOARDS];

	// Change bytes order
	for (i = 0; i < COMMUTATION_EXT_BOARDS; ++i)
		CurrentOutputValuesCopy[i] = CurrentOutputValues[COMMUTATION_EXT_BOARDS - 1 - i];

	ZwSPId_Send(CurrentOutputValuesCopy, sizeof(Int16U) * COMMUTATION_EXT_BOARDS, IOE_OUT_CL, STTNormal);
}
// ----------------------------------------


