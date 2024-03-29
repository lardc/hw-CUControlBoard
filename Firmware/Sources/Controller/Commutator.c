// ----------------------------------------
// Commutation logic
// ----------------------------------------

// Header
#include "Commutator.h"
//
#include "ZwDSP.h"
#include "ZbBoard.h"
#include "DeviceObjectDictionary.h"
#include "CommutationTable.h"
#include "Global.h"
#include "DataTable.h"


// Variables
//
static Int16U OldActionID = ACT_COMM2_4_NONE;
CommutationMode CurrentCommMode = CM_CUHV2;


// Forward functions
//
void COMM_CommDelay(Int16U ActionID);
void COMM_CommutateNone();


// Functions
//
void COMM_Init()
{
	switch(DataTable[REG_COMM_NUM])
	{
		case 0:
		case 2:
			CurrentCommMode = CM_CUHV2;
			break;

		case 4:
			CurrentCommMode = CM_CUHV4;
			break;

		case 6:
			CurrentCommMode = CM_CUHV6;
			break;
	}
	OldActionID = (CurrentCommMode == CM_CUHV6) ? ACT_COMM6_NONE : ACT_COMM2_4_NONE;

	// Привязка таблиц коммутации и переопределение ограничений
	ZbIOE_MakeTablesBinding(CurrentCommMode);
}
// ----------------------------------------

void COMM_CommutateNone()
{
	ZbIOE_RegisterReset();
	if (OldActionID == ACT_COMM2_4_NONE || OldActionID == ACT_COMM6_NONE)
		return;

	Int16U Action = CurrentCommMode == CM_CUHV6 ? ACT_COMM6_NONE : ACT_COMM2_4_NONE;
	COMM_CommDelay(Action);

	ZbGPIO_ConnectProtectiveEarth(TRUE);
	DELAY_US(COMM_DELAY_NONE_MS * 1000L);

	OldActionID = Action;
}
// ----------------------------------------

void COMM_CommDelay(Int16U ActionID)
{
	Boolean LongDelay = \
			ActionID == ACT_COMM2_4_SL || \
			ActionID == ACT_COMM2_4_GATE_SL || \
			ActionID == ACT_COMM6_SL || \

			OldActionID == ACT_COMM2_4_SL || \
			OldActionID == ACT_COMM2_4_GATE_SL || \
			OldActionID == ACT_COMM6_SL;

	DELAY_US((LongDelay ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);
}
// ----------------------------------------

void COMM2_Commutate(Int16U ActionID)
{
	if (ActionID == OldActionID) return;

	if (ActionID != ACT_COMM2_4_NONE && OldActionID != ACT_COMM2_4_NONE)
		COMM_CommutateNone();

	if (ActionID != ACT_COMM2_4_NONE)
		ZbGPIO_ConnectProtectiveEarth(FALSE);

	Boolean BlackBoxNCRelay = DataTable[REG_BB_NC_RELAY];
	Boolean Vgt2WireMode = DataTable[REG_USE_VGT_2WIRE_MODE];
	Int16U BBRelayIndex = DataTable[REG_PCB_V22_AND_LOWER] ? T2_OLD_BB_RELAY : T2_BB_RELAY_ACTIVATE;

	switch(ActionID)
	{
		case ACT_COMM2_4_GATE:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_GATE_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POW_CTRL_C, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_CTL_A, TRUE);
				if(Vgt2WireMode)
				{
					ZbIOE_OutputValuesCompose(T2_GATE_CTL_C_2WIRE, TRUE);
				}
				else
				{
					ZbIOE_OutputValuesCompose(T2_GATE_POT_CTL_A, TRUE);
					ZbIOE_OutputValuesCompose(T2_GATE_POT_CTL_C, TRUE);
				}
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_4_SL:
			{
				if(DataTable[REG_MODULE_TYPE] == MODULE_DIRECT)
				{
					ZbIOE_OutputValuesReset();
					ZbIOE_OutputValuesCompose(T2_SL_PWR, TRUE);
					ZbIOE_OutputValuesCompose(T2_SL_POT_A, TRUE);
					ZbIOE_OutputValuesCompose(T2_SL_POT_C, TRUE);
					ZbIOE_OutputValuesCompose(T2_SL_CTL_A, TRUE);
					ZbIOE_OutputValuesCompose(Vgt2WireMode ? T2_SL_CTL_C_2WIRE : T2_SL_CTL_C, TRUE);
					if(!BlackBoxNCRelay)
						ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
					ZbIOE_RegisterFlushWrite();
				}
				else if(DataTable[REG_MODULE_TYPE] == MODULE_REVERSE)
				{
					ZbIOE_OutputValuesReset();
					ZbIOE_OutputValuesCompose(T2_SL_PWR_R, TRUE);
					ZbIOE_OutputValuesCompose(T2_SL_POT_A_R, TRUE);
					ZbIOE_OutputValuesCompose(T2_SL_POT_C_R, TRUE);
					if(!BlackBoxNCRelay)
						ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
					ZbIOE_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM2_4_BV_D:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_BV_POS_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_BV_NEG_POW_C, TRUE);
				if(BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_4_BV_R:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_BV_NEG_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_BV_POS_POW_C, TRUE);
				if(BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_4_NO_PE:
			{
				ZbIOE_OutputValuesReset();
				if(BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_4_GATE_SL:
			{
				ZbIOE_OutputValuesReset();
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);

				// GTU
				ZbIOE_OutputValuesCompose(T2_GATE_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POW_CTRL_C, TRUE);

				// SL
				ZbIOE_OutputValuesCompose(T2_SL_PWR, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_POT_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_POT_C, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(Vgt2WireMode ? T2_SL_CTL_C_2WIRE : T2_SL_CTL_C, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_4_VGNT:
			{
				ZbIOE_OutputValuesReset();
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(BBRelayIndex, TRUE);

				// GTU
				ZbIOE_OutputValuesCompose(T2_GATE_POW_CTRL_C, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POT_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POT_CTL_C, TRUE);
				// BVT direct
				ZbIOE_OutputValuesCompose(T2_BV_POS_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_BV_NEG_POW_C, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_4_NONE:
		default:
			COMM_CommutateNone();
			break;
	}

	COMM_CommDelay(ActionID);
	OldActionID = ActionID;
}
// ----------------------------------------

void COMM4_Commutate(Int16U ActionID, Int16U ModuleType, pInt16U pUserError)
{
	if (ActionID == OldActionID) return;

	if (ActionID != ACT_COMM2_4_NONE && OldActionID != ACT_COMM2_4_NONE)
		COMM_CommutateNone();

	if (ActionID != ACT_COMM2_4_NONE)
		ZbGPIO_ConnectProtectiveEarth(FALSE);

	switch(ActionID)
	{
		case ACT_COMM2_4_GATE:
		{
			switch(ModuleType)
			{
				case MODULE_DIRECT:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_GATE_POW_A_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POW_CTRL_C_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_C_2, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				case MODULE_REVERSE:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_GATE_POW_A_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POW_CTRL_C_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_C_1, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				default:
					{
						ZbIOE_OutputValuesReset();
						*pUserError = ERR_WRONG_CMD;
					}
					break;
			}
		}
		break;

		case ACT_COMM2_4_SL:
		{
			switch(ModuleType)
			{
				case MODULE_DIRECT:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_SL_CUHC_DIR, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_A_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_C_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_C_2, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				case MODULE_REVERSE:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_SL_CUHC_REV, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_A_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_C_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_C_1, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				default:
					{
						ZbIOE_OutputValuesReset();
						*pUserError = ERR_WRONG_CMD;
					}
					break;
			}
		}
		break;

		case ACT_COMM2_4_BV_D:
		{
			switch(ModuleType)
			{
				case MODULE_DIRECT:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_BV_POS_POW_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_BV_NEG_POW_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_BB_DISCONNECT, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				case MODULE_REVERSE:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_BV_POS_POW_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_BV_NEG_POW_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_BB_DISCONNECT, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				default:
					{
						ZbIOE_OutputValuesReset();
						*pUserError = ERR_WRONG_CMD;
					}
					break;
			}
		}
		break;

		case ACT_COMM2_4_BV_R:
		{
			switch(ModuleType)
			{
				case MODULE_DIRECT:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_BV_NEG_POW_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_BV_POS_POW_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_BB_DISCONNECT, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;
				case MODULE_REVERSE:
					{
						ZbIOE_OutputValuesReset();
						ZbIOE_OutputValuesCompose(T4_BV_NEG_POW_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_BV_POS_POW_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_BB_DISCONNECT, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				default:
					{
						ZbIOE_OutputValuesReset();
						*pUserError = ERR_WRONG_CMD;
					}
					break;
			}
		}
		break;

		case ACT_COMM2_4_NO_PE:
		{
			ZbIOE_OutputValuesReset();
			ZbIOE_OutputValuesCompose(T4_BB_DISCONNECT, TRUE);
			ZbIOE_RegisterFlushWrite();
		}
		break;

		case ACT_COMM2_4_GATE_SL:
		{
			switch(ModuleType)
			{
				case MODULE_DIRECT:
					{
						ZbIOE_OutputValuesReset();
						// GTU
						ZbIOE_OutputValuesCompose(T4_GATE_POW_A_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POW_CTRL_C_2, TRUE);

						// SL
						ZbIOE_OutputValuesCompose(T4_SL_CUHC_DIR, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_A_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_C_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_C_2, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				case MODULE_REVERSE:
					{
						ZbIOE_OutputValuesReset();
						// GTU
						ZbIOE_OutputValuesCompose(T4_GATE_POW_A_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POW_CTRL_C_1, TRUE);

						// SL
						ZbIOE_OutputValuesCompose(T4_SL_CUHC_REV, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_A_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_POT_C_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_SL_CTL_C_1, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;
				default:
					{
						ZbIOE_OutputValuesReset();
						*pUserError = ERR_WRONG_CMD;
					}
					break;

			}
		}
		break;

		case ACT_COMM2_4_VGNT:
		{
			switch(ModuleType)
			{
				case MODULE_DIRECT:
					{
						ZbIOE_OutputValuesReset();
						// GTU
						ZbIOE_OutputValuesCompose(T4_GATE_POW_CTRL_C_2, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_C_2, TRUE);
						// BVT direct
						ZbIOE_OutputValuesCompose(T4_BV_POS_POW_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_BV_NEG_POW_2, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;

				case MODULE_REVERSE:
					{
						ZbIOE_OutputValuesReset();
						// GTU
						ZbIOE_OutputValuesCompose(T4_GATE_POW_CTRL_C_1, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_A, TRUE);
						ZbIOE_OutputValuesCompose(T4_GATE_POT_CTL_C_1, TRUE);
						// BVT direct
						ZbIOE_OutputValuesCompose(T2_BV_POS_POW_C, TRUE);
						ZbIOE_OutputValuesCompose(T2_BV_NEG_POW_A, TRUE);
						ZbIOE_RegisterFlushWrite();
					}
					break;
				default:
					{
						ZbIOE_OutputValuesReset();
						*pUserError = ERR_WRONG_CMD;
					}
					break;

			}
		}
		break;

		case ACT_COMM2_4_NONE:
		default:
			COMM_CommutateNone();
			break;
	}

	COMM_CommDelay(ActionID);
	OldActionID = ActionID;
}
// ----------------------------------------

void COMM6_Commutate(Int16U ActionID, Int16U ModuleType, Int16U ModulePosition, pInt16U pUserError)
{
	if (ActionID == OldActionID) return;

	if (ActionID != ACT_COMM6_NONE && OldActionID != ACT_COMM6_NONE)
		COMM_CommutateNone();

	if (ActionID != ACT_COMM6_NONE)
		ZbGPIO_ConnectProtectiveEarth(FALSE);

	switch(ActionID)
	{
		case ACT_COMM6_GATE:
			{
				ZbIOE_OutputValuesReset();

				if(ModulePosition == 1)
				{
					ZbIOE_OutputValuesCompose(T6_GATE_CTL_A_1, TRUE);
					ZbIOE_OutputValuesCompose(T6_GATE_CTL_C_1, TRUE);
				}
				else
				{
					ZbIOE_OutputValuesCompose(T6_GATE_CTL_A_2, TRUE);
					ZbIOE_OutputValuesCompose(T6_GATE_CTL_C_2, TRUE);
				}

				if(ModulePosition == 1)
				{
					switch(ModuleType)
					{
						case MODULE_MT1:
							{
								ZbIOE_OutputValuesCompose(T6_GATE_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_GATE_POW_C_3, TRUE);
							}
							break;
						case MODULE_MT3:
						case MODULE_MT5:
						case MODULE_MTD3:
						case MODULE_MTD5:
							{
								ZbIOE_OutputValuesCompose(T6_GATE_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_GATE_POW_C_2, TRUE);
							}
							break;
						case MODULE_MT4:
						case MODULE_MTD4:
							{
								ZbIOE_OutputValuesCompose(T6_GATE_POW_A_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_GATE_POW_C_1, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				else
				{
					switch(ModuleType)
					{
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MDT3:
						case MODULE_MDT4:
							{
								ZbIOE_OutputValuesCompose(T6_GATE_POW_A_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_GATE_POW_C_1, TRUE);
							}
							break;
						case MODULE_MT5:
						case MODULE_MDT5:
							{
								ZbIOE_OutputValuesCompose(T6_GATE_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_GATE_POW_C_3, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM6_SL:
			{
				ZbIOE_OutputValuesReset();

				// Commutate gate lines
				if(ModulePosition == 1)
				{
					switch(ModuleType)
					{
						case MODULE_MT1:
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MT5:
						case MODULE_MTD3:
						case MODULE_MTD4:
						case MODULE_MTD5:
							{
								ZbIOE_OutputValuesCompose(T6_SL_CTL_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_CTL_C_1, TRUE);
							}
							break;
					}
				}
				else
				{
					switch(ModuleType)
					{
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MT5:
						case MODULE_MDT3:
						case MODULE_MDT4:
						case MODULE_MDT5:
							{
								ZbIOE_OutputValuesCompose(T6_SL_CTL_A_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_CTL_C_2, TRUE);
							}
							break;
					}
				}

				// Commutate power lines
				if(ModulePosition == 1)
				{
					switch(ModuleType)
					{
						case MODULE_MT1:
						case MODULE_MD1:
							{
								ZbIOE_OutputValuesCompose(T6_SL_POT_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POT_C_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_C_3, TRUE);
							}
							break;
						case MODULE_MT3:
						case MODULE_MT5:
						case MODULE_MD3:
						case MODULE_MD3_BP:
						case MODULE_MD5:
						case MODULE_MDT3:
						case MODULE_MDT5:
						case MODULE_MTD3:
						case MODULE_MTD5:
							{
								ZbIOE_OutputValuesCompose(T6_SL_POT_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POT_C_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_C_2, TRUE);
							}
							break;
						case MODULE_MT4:
						case MODULE_MD4:
						case MODULE_MTD4:
						case MODULE_MDT4:
							{
								ZbIOE_OutputValuesCompose(T6_SL_POT_A_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POT_C_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_A_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_C_1, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				else
				{
					switch(ModuleType)
					{
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MD3:
						case MODULE_MD3_BP:
						case MODULE_MD4:
						case MODULE_MDT3:
						case MODULE_MDT4:
						case MODULE_MTD3:
						case MODULE_MTD4:
							{
								ZbIOE_OutputValuesCompose(T6_SL_POT_A_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POT_C_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_A_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_C_1, TRUE);
							}
							break;
						case MODULE_MT5:
						case MODULE_MD5:
						case MODULE_MTD5:
						case MODULE_MDT5:
							{
								ZbIOE_OutputValuesCompose(T6_SL_POT_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POT_C_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_SL_POW_C_3, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM6_BV_D:
			{
				ZbIOE_OutputValuesReset();

				if(ModulePosition == 1)
				{
					switch(ModuleType)
					{
						case MODULE_MT1:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_3, TRUE);
							}
							break;
						case MODULE_MT3:
						case MODULE_MT5:
						case MODULE_MTD3:
						case MODULE_MTD5:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_2, TRUE);
							}
							break;
						case MODULE_MT4:
						case MODULE_MTD4:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_1, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				else
				{
					switch(ModuleType)
					{
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MDT3:
						case MODULE_MDT4:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_1, TRUE);
							}
							break;
						case MODULE_MT5:
						case MODULE_MDT5:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_3, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM6_BV_R:
			{
				ZbIOE_OutputValuesReset();

				if(ModulePosition == 1)
				{
					switch(ModuleType)
					{
						case MODULE_MT1:
						case MODULE_MD1:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_1, TRUE);
							}
							break;
						case MODULE_MT3:
						case MODULE_MT5:
						case MODULE_MD3:
						case MODULE_MD3_BP:
						case MODULE_MD5:
						case MODULE_MDT3:
						case MODULE_MDT5:
						case MODULE_MTD3:
						case MODULE_MTD5:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_1, TRUE);
							}
							break;
						case MODULE_MT4:
						case MODULE_MD4:
						case MODULE_MTD4:
						case MODULE_MDT4:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_2, TRUE);
							}
							break;
					}
				}
				else
				{
					switch(ModuleType)
					{
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MD3:
						case MODULE_MD3_BP:
						case MODULE_MD4:
						case MODULE_MDT3:
						case MODULE_MDT4:
						case MODULE_MTD3:
						case MODULE_MTD4:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_3, TRUE);
							}
							break;
						case MODULE_MT5:
						case MODULE_MD5:
						case MODULE_MTD5:
						case MODULE_MDT5:
							{
								ZbIOE_OutputValuesCompose(T6_BV_POS_POW_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_BV_NEG_POW_1, TRUE);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM6_NONE:
		default:
			COMM_CommutateNone();
			break;
	}

	COMM_CommDelay(ActionID);
	OldActionID = ActionID;
}
// ----------------------------------------

void COMM6_G4W_CathodPE(Int16U TableID)
{
	switch(TableID)
	{
		case T6_G4W_PE_POW_1:
			ZbIOE_OutputValuesCompose(T6_G4W_PE_POW_2, TRUE);
			ZbIOE_OutputValuesCompose(T6_G4W_PE_POW_3, TRUE);
			break;
		case T6_G4W_PE_POW_2:
			ZbIOE_OutputValuesCompose(T6_G4W_PE_POW_1, TRUE);
			ZbIOE_OutputValuesCompose(T6_G4W_PE_POW_3, TRUE);
			break;
		case T6_G4W_PE_POW_3:
			ZbIOE_OutputValuesCompose(T6_G4W_PE_POW_1, TRUE);
			ZbIOE_OutputValuesCompose(T6_G4W_PE_POW_2, TRUE);
			break;
		default:
			break;
	}
}
// ----------------------------------------

void COMM6_G4W_Commutate(Int16U ActionID, Int16U ModuleType, Int16U ModulePosition, pInt16U pUserError)
{
	if (ActionID == OldActionID) return;

	if (ActionID != ACT_COMM6_NONE && OldActionID != ACT_COMM6_NONE)
		COMM_CommutateNone();

	if (ActionID != ACT_COMM6_NONE)
		ZbGPIO_ConnectProtectiveEarth(FALSE);

	switch(ActionID)
	{
		case ACT_COMM6_GATE:
			{
				ZbIOE_OutputValuesReset();

				if(ModulePosition == 1)
				{
					ZbIOE_OutputValuesCompose(T6_G4W_GATE_CTL_A_1, TRUE);
					ZbIOE_OutputValuesCompose(T6_G4W_GATE_CTL_A_POT_1, TRUE);
				}
				else
				{
					ZbIOE_OutputValuesCompose(T6_G4W_GATE_CTL_A_2, TRUE);
					ZbIOE_OutputValuesCompose(T6_G4W_GATE_CTL_A_POT_2, TRUE);
				}

				if(ModulePosition == 1)
				{
					switch(ModuleType)
					{
						case MODULE_MT1:
							{
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_C_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_SL_GTU_POT_C_3, TRUE);
								COMM6_G4W_CathodPE(T6_G4W_PE_POW_3);
							}
							break;
						case MODULE_MT3:
						case MODULE_MT5:
						case MODULE_MTD3:
						case MODULE_MTD5:
							{
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_C_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_SL_GTU_POT_C_2, TRUE);
								COMM6_G4W_CathodPE(T6_G4W_PE_POW_2);
							}
							break;
						case MODULE_MT4:
						case MODULE_MTD4:
							{
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_A_2, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_C_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_SL_GTU_POT_C_1, TRUE);
								COMM6_G4W_CathodPE(T6_G4W_PE_POW_1);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				else
				{
					switch(ModuleType)
					{
						case MODULE_MT3:
						case MODULE_MT4:
						case MODULE_MDT3:
						case MODULE_MDT4:
							{
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_A_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_C_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_SL_GTU_POT_C_1, TRUE);
								COMM6_G4W_CathodPE(T6_G4W_PE_POW_1);
							}
							break;
						case MODULE_MT5:
						case MODULE_MDT5:
							{
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_A_1, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_GATE_POW_C_3, TRUE);
								ZbIOE_OutputValuesCompose(T6_G4W_SL_GTU_POT_C_3, TRUE);
								COMM6_G4W_CathodPE(T6_G4W_PE_POW_3);
							}
							break;
						default:
							{
								ZbIOE_OutputValuesReset();
								*pUserError = ERR_WRONG_CMD;
							}
							break;
					}
				}
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM6_NONE:
		default:
			COMM_CommutateNone();
			break;
	}

	COMM_CommDelay(ActionID);
	OldActionID = ActionID;
}
// ----------------------------------------
