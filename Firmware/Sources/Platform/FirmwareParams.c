// Header
#include "FirmwareParams.h"

// Definitions
#define LABEL_START_ADDRESS			0x3DC000	// Sector G
#define LABEL_NAME_MAX_LENGTH		64

// Types
typedef struct __Label
{
	char Name[LABEL_NAME_MAX_LENGTH];
	SelectorIndex Index;
} Label;

// Variables
static SelectorIndex LabelSelector = SID_None;
const Label BoardLabels[] =
{
		{"CUControlBoard v.2.4 [Manufacturing]",	SID_PCB2_4_Manuf},
		{"CUControlBoard v.2.3 [Manufacturing]",	SID_PCB2_3_Manuf},
		{"CUControlBoard v.2.3",					SID_PCB2_3}
};

// Forward functions
Boolean FWPAR_AreNamesEqual(char *a, char *b);

// Functions
//
void FWPAR_LoadBoardLabel()
{
	// ������ ���������� �����
	Int16U i;
	char CurrentLabel[LABEL_NAME_MAX_LENGTH] = {0};
	for(i = 0; i < LABEL_NAME_MAX_LENGTH; i++)
	{
		Int16U Symbol = *((pInt16U)(i + LABEL_START_ADDRESS));

		// �������� �� ��������� � �������� ASCII
		if(0x20 <= Symbol && Symbol <= 0x7E)
			CurrentLabel[i] = Symbol;
	}

	// ����������� ������� �����
	for(i = 0; i < sizeof(BoardLabels) / sizeof(BoardLabels[0]); i++)
		if(FWPAR_AreNamesEqual(CurrentLabel, (char *)BoardLabels[i].Name))
		{
			LabelSelector = BoardLabels[i].Index;
			break;
		}
}
// ----------------------------------------

Boolean FWPAR_AreNamesEqual(char *a, char *b)
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

SelectorIndex FWPAR_GetSelector()
{
	return LabelSelector;
}
// ----------------------------------------
