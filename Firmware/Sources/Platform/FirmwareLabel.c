// Header
#include "FirmwareLabel.h"

// Include
#include "LabelDescription.h"

// Variables
static Int16U LabelReadPointer = 0;
static SelectorIndex LabelSelector = SID_None;

// Forward functions
Boolean FWLB_AreNamesEqual(char *a, char *b);

// Functions
//
void FWLB_LoadBoardLabel()
{
	// Чтение сохранённой метки
	Int16U i;
	char CurrentLabel[LABEL_NAME_MAX_LENGTH] = {0};
	for(i = 0; i < LABEL_NAME_MAX_LENGTH; i++)
	{
		Int16U Symbol = *((pInt16U)(i + LABEL_START_ADDRESS));

		// Проверка на попадание в диапазон ASCII
		if(0x20 <= Symbol && Symbol <= 0x7E)
			CurrentLabel[i] = Symbol;
		else
			break;
	}

	// Определение индекса метки
	for(i = 0; i < BoardLabelsSize; i++)
	{
		if(FWLB_AreNamesEqual(CurrentLabel, (char *)BoardLabels[i].Name))
		{
			LabelSelector = BoardLabels[i].Index;
			break;
		}
	}
}
// ----------------------------------------

Boolean FWLB_AreNamesEqual(char *a, char *b)
{
	Int16U i;
	for(i = 0; i < LABEL_NAME_MAX_LENGTH; i++)
	{
		if(a[i] != b[i])
			return FALSE;
	}

	return TRUE;
}
// ----------------------------------------

SelectorIndex FWLB_GetSelector()
{
	return LabelSelector;
}
// ----------------------------------------

void FWLB_PrepareLabelRead()
{
	LabelReadPointer = 0;
}
// ----------------------------------------

Int16U FWLB_ReadLabelSymbol()
{
	if(LabelReadPointer < LABEL_NAME_MAX_LENGTH)
	{
		Int16U Symbol = *((pInt16U)(LABEL_START_ADDRESS + LabelReadPointer++));
		return (0x20 <= Symbol && Symbol <= 0x7E) ? Symbol : 0;
	}
	else
		return 0;
}
// ----------------------------------------
