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
static Int16U OldActionID2 = ACT_COMM2_NONE, OldActionID6 = ACT_COMM6_NONE;


// Forward functions
//
void COMM2_CommDelay(Int16U ActionID);


// Functions
//
void COMM2_CommutateNone()
{
	// Reset registers anyway
	ZbIOE_RegisterReset();

	if (OldActionID2 == ACT_COMM2_NONE) return;

	COMM2_CommDelay(ACT_COMM2_NONE);

	ZbGPIO_ConnectProtectiveEarth(TRUE);
	DELAY_US(COMM_DELAY_NONE_MS * 1000L);

	OldActionID2 = ACT_COMM2_NONE;
}
// ----------------------------------------

void COMM6_CommutateNone()
{
	// Reset registers anyway
	ZbIOE_RegisterReset();

	if (OldActionID6 == ACT_COMM6_NONE) return;

	DELAY_US(((OldActionID6 == ACT_COMM6_SL) ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);

	ZbGPIO_ConnectProtectiveEarth(TRUE);
	DELAY_US(COMM_DELAY_NONE_MS * 1000L);

	OldActionID6 = ACT_COMM6_NONE;
}
// ----------------------------------------

void COMM2_CommDelay(Int16U ActionID)
{
	DELAY_US((( \
			ActionID == ACT_COMM2_SL || \
			ActionID == ACT_COMM2_GATE_SL || \
			OldActionID2 == ACT_COMM2_SL || \
			OldActionID2 == ACT_COMM2_GATE_SL) ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);
}
// ----------------------------------------

void COMM2_Commutate(Int16U ActionID)
{
	if (ActionID == OldActionID2) return;

	if (ActionID != ACT_COMM2_NONE && OldActionID2 != ACT_COMM2_NONE)
		COMM2_CommutateNone();

	if (ActionID != ACT_COMM2_NONE)
		ZbGPIO_ConnectProtectiveEarth(FALSE);

	Boolean BlackBoxNCRelay = DataTable[REG_BB_NC_RELAY];
	switch(ActionID)
	{
		case ACT_COMM2_GATE:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_GATE_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POW_CTRL_C, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POT_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POT_CTL_C, TRUE);
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_SL:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_SL_PWR, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_POT_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_POT_C, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_CTL_C, TRUE);
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_BV_D:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_BV_POS_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_BV_NEG_POW_C, TRUE);
				if(BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_BV_R:
			{
				ZbIOE_OutputValuesReset();
				ZbIOE_OutputValuesCompose(T2_BV_NEG_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_BV_POS_POW_C, TRUE);
				if(BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_NO_PE:
			{
				ZbIOE_OutputValuesReset();
				if(BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_GATE_SL:
			{
				ZbIOE_OutputValuesReset();
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);

				// GTU
				ZbIOE_OutputValuesCompose(T2_GATE_POW_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_GATE_POW_CTRL_C, TRUE);

				// SL
				ZbIOE_OutputValuesCompose(T2_SL_PWR, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_POT_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_POT_C, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_CTL_A, TRUE);
				ZbIOE_OutputValuesCompose(T2_SL_CTL_C, TRUE);
				ZbIOE_RegisterFlushWrite();
			}
			break;

		case ACT_COMM2_VGNT:
			{
				ZbIOE_OutputValuesReset();
				if(!BlackBoxNCRelay)
					ZbIOE_OutputValuesCompose(T2_BB_RELAY_ACTIVATE, TRUE);

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

		case ACT_COMM2_NONE:
		default:
			COMM2_CommutateNone();
			break;
	}

	COMM2_CommDelay(ActionID);
	OldActionID2 = ActionID;
}
// ----------------------------------------

void COMM6_Commutate(Int16U ActionID, Int16U ModuleType, Int16U ModulePosition, pInt16U pUserError)
{
	if (ActionID == OldActionID6) return;

	if (ActionID != ACT_COMM6_NONE && OldActionID6 != ACT_COMM6_NONE)
		COMM6_CommutateNone();

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

				DELAY_US(((OldActionID6 == ACT_COMM6_SL) ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);
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
				DELAY_US(COMM_DELAY_LONG_MS * 1000L);
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

				DELAY_US(((OldActionID6 == ACT_COMM6_SL) ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);
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

				DELAY_US(((OldActionID6 == ACT_COMM6_SL) ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);
			}
			break;

#ifdef BVT_LP
		case ACT_COMM6_ISO:
			{
				ZbIOE_OutputValuesReset();

				switch(ModuleType)
				{
					case MODULE_MT1:
						{
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_3, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_A_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_C_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_NEG_ISO, TRUE);
						}
						break;
					case MODULE_MD1:
						{
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_3, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_NEG_ISO, TRUE);
						}
						break;
					case MODULE_MT3:
					case MODULE_MT4:
					case MODULE_MT5:
						{
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_3, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_A_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_C_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_A_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_C_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_NEG_ISO, TRUE);
						}
						break;
					case MODULE_MD3:
					case MODULE_MD4:
					case MODULE_MD5:
						{
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_3, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_NEG_ISO, TRUE);
						}
						break;
					case MODULE_MTD3:
					case MODULE_MTD4:
					case MODULE_MTD5:
						{
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_3, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_A_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_C_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_NEG_ISO, TRUE);
						}
						break;
					case MODULE_MDT3:
					case MODULE_MDT4:
					case MODULE_MDT5:
						{
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_1, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_POW_3, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_A_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_POS_C_2, TRUE);
							ZbIOE_OutputValuesCompose(T6_ISOL_NEG_ISO, TRUE);
						}
						break;
					default:
						{
							ZbIOE_OutputValuesReset();
							*pUserError = ERR_WRONG_CMD;
						}
						break;
				}

				ZbIOE_RegisterFlushWrite();

				DELAY_US(((OldActionID6 == ACT_COMM6_SL) ? COMM_DELAY_LONG_MS : COMM_DELAY_SHORT_MS) * 1000L);
			}
			break;
#endif

		case ACT_COMM6_NONE:
		default:
			COMM6_CommutateNone();
			break;
	}

	OldActionID6 = ActionID;
}
// ----------------------------------------


