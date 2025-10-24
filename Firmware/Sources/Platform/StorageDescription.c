// Header
#include "StorageDescription.h"

// Variables
const RecordDescription StorageDescription[] =
{
		{"Register 192",	DT_Int16U, 1	},
		{"Voltage EP1",		DT_Int16U, 100	},
		{"Max current",		DT_Int32U, 1	},
		{"Max voltage",		DT_Int16U, 1	}
};
Int32U TablePointers[sizeof(StorageDescription) / sizeof(StorageDescription[0])] = {0};
const Int16U StorageSize = sizeof(StorageDescription) / sizeof(StorageDescription[0]);

const CounterDescription *CounterStorageDescription;
CounterData *CounterTablePointers;
Int16U CounterStorageSize;

const CounterDescription CounterStorageDescription2[] =
{
	{"0. BVT: HV2 to POWER_A"},
	{"1. BVT: HV1 to POWER_A"},
	{"2. GTU: Power Anode to POWER_A"},
	{"3. None"},
	{"4. BVT: HV2 to POWER_C"},
	{"5. BVT: HV1 to POWER_C"},
	{"6. GTU+SL: Power and Control Cathode to POWER_C"},
	{"7. None"},
	{"8. None"},
	{"9. None"},
	{"10. GTU: GTU Control Anode to CTRL_A"},
	{"11. SL: SL Control Anode to CTRL_A"},
	{"12. None"},
	{"13. None"},
	{"14. GTU: GTU Potential Control Anode to POTENTIAL_CTRL_A"},
	{"15. SL: SL control Cathode to CTRL_C (for 2-wired  Vgt)"},
	{"16. None"},
	{"17. None"},
	{"18. None"},
	{"19. BB: Relay control in Blackbox depending in type (HO / H3)"},
	{"20. None"},
	{"21. None"},
	{"22. SL: HC POWER (REVERSE)"},
	{"23. SL: HC POWER"},
	{"24. None"},
	{"25. None"},
	{"26. SL: Potential Anode to POTENTIAL_A"},
	{"27. SL: Potential Anode to POTENTIAL_A (REVERSE)"},
	{"28. None"},
	{"29. None"},
	{"30. SL: Potential Cathode to POTENTIAL_C"},
	{"31. GTU: POT Ctrl C to POT_CTRL_C; SL: POT C to POT_C (REV)"}
};
CounterData CounterTablePointers2[sizeof(CounterStorageDescription2) / sizeof(CounterStorageDescription2[0])] = {0};
const Int16U CounterStorageSize2 = sizeof(CounterStorageDescription2) / sizeof(CounterStorageDescription2[0]);

const CounterDescription CounterStorageDescription4[] =
{
	{"0. BVT: HV+ to POW_A"},
	{"1. BVT: HV+ to POW_C"},
	{"2. GTU: Power Anode to POW_A"},
	{"3. GTU: Power Anode to POW_C"},
	{"4. BVT: HV- to POW_C"},
	{"5. BVT: HV- to POW_A"},
	{"6. GTU: Power and Control Cathode to POW_A"},
	{"7. GTU: Power and Control Cathode to POW_C"},
	{"8. SL: Control Cathode (C-) to POW_A"},
	{"9. SL: Control Cathode (C-) to POW_C"},
	{"10. SL: Potential Anode to POT_A"},
	{"11. SL: Potential Anode to POT_C"},
	{"12. SL: Potential Cathode to POT_A"},
	{"13. SL: Potential Cathode to POT_C"},
	{"14. GTU: Potential Control Cathode to POT_A"},
	{"15. GTU: Potential Control Cathode to POT_C"},
	{"16. None"},
	{"17. None"},
	{"18. None"},
	{"19. BB: Disconnect control"},
	{"20. None"},
	{"21. None"},
	{"22. BCUHC4: IN+/IN- to OUI-/OUT+"},
	{"23. BCUHC4: IN+/IN- to OUT+/OUT-"},
	{"24. None"},
	{"25. None"},
	{"26. GTU: Control Anode to CTRL_A"},
	{"27. GTU: Potential Control Anode to POT_CTRL_A"},
	{"28. None"},
	{"29. None"},
	{"30. SL: Control Anode (C+) to CTRL_A"},
	{"31. None"}
};
CounterData CounterTablePointers4[sizeof(CounterStorageDescription4) / sizeof(CounterStorageDescription4[0])] = {0};
const Int16U CounterStorageSize4 = sizeof(CounterStorageDescription4) / sizeof(CounterStorageDescription4[0]);

const CounterDescription CounterStorageDescription6[] =
{
	{"0. SL: HC+ to POWER_2"},
	{"1. SL: HC+ to POWER_3"},
	{"2. SL: HC+ to POWER_1"},
	{"3. SL: HC- to POWER_1"},
	{"4. BVTLP: HV- to Isolation"},
	{"5. None"},
	{"6. SL: HC- to POWER_2"},
	{"7. SL: HC- to POWER_3"},
	{"8. BVTLP: LPHV+ to POTENTIAL_1"},
	{"9. BVTLP: LPHV- to POTENTIAL_1"},
	{"10. SL: Potential Anode to POTENTIAL_1"},
	{"11. SL: Potential Cathode to POTENTIAL_1"},
	{"12. BVTLP: LPHV+ to POTENTIAL_2"},
	{"13. BVTLP: LPHV- to POTENTIAL_2"},
	{"14. SL: Potential Anode to POTENTIAL_2"},
	{"15. SL: Potential Cathode to POTENTIAL_2"},
	{"16. BVT: HV+ to POWER_2"},
	{"17. BVT: HV- to POWER_2"},
	{"18. GTU: Power Anode to POWER_2"},
	{"19. GTU: Power Cathode to POWER_2"},
	{"20. BVT: HV+ to POWER_3"},
	{"21. BVT: HV- to POWER_3"},
	{"22. GTU: Power Anode to POWER_3"},
	{"23. GTU: Power Cathode to POWER_3"},
	{"24. BVTLP: LPHV+ to POTENTIAL_3"},
	{"25. BVTLP: LPHV- to POTENTIAL_3"},
	{"26. SL: Potential Anode to POTENTIAL_3"},
	{"27. SL: Potential Cathode to POTENTIAL_3"},
	{"28. BVT: HV+ to POWER_1"},
	{"29. BVT: HV- to POWER_1"},
	{"30. GTU: Power Anode to POWER_1"},
	{"31. GTU: Power Cathode to POWER_1"},
	{"32. BVTLP: HV+ to CTRL_A2"},
	{"33. None"},
	{"34. SL: Control Anode to CTRL_A2"},
	{"35. GTU: Control Anode to CTRL_A2"},
	{"36. BVTLP: HV+ to CTRL_C2"},
	{"37. None"},
	{"38. SL: Control Cathode to CTRL_C2"},
	{"39. GTU: Control Cathode to CTRL_C2"},
	{"40. BVTLP: HV+ to CTRL_A1"},
	{"41. None"},
	{"42. SL: Control Anode to CTRL_A1"},
	{"43. GTU: Control Anode to CTRL_A1"},
	{"44. BVTLP: HV+ to CTRL_C1"},
	{"45. None"},
	{"46. SL: Control Cathode to CTRL_C1"},
	{"47. GTU: Control Cathode to CTRL_C1"}
};
CounterData CounterTablePointers6[sizeof(CounterStorageDescription6) / sizeof(CounterStorageDescription6[0])] = {0};
const Int16U CounterStorageSize6 = sizeof(CounterStorageDescription6) / sizeof(CounterStorageDescription6[0]);

const CounterDescription CounterStorageDescription6Gate4Wire[] =
{
	{"0. SL: HC+ to POWER_2"},
	{"1. SL: HC+ to POWER_3"},
	{"2. SL: HC+ to POWER_1"},
	{"3. SL: HC- to POWER_1"},
	{"4. PE: Special PE to POWER_1 (inverted)"},
	{"5. PE: Special PE to POWER_2 (inverted)"},
	{"6. PE: Special PE to POWER_3 (inverted)"},
	{"7. None"},
	{"8. SL: HC- to POWER_2"},
	{"9. SL: HC- to POWER_3"},
	{"10. SL: Potential Anode to POTENTIAL_1"},
	{"11. SL+GTU: Potential Cathode to POTENTIAL_1"},
	{"12. None"},
	{"13. None"},
	{"14. SL: Potential Anode to POTENTIAL_2"},
	{"15. SL+GTU: Potential Cathode to POTENTIAL_2"},
	{"16. BVT: HV+ to POWER_2"},
	{"17. BVT: HV- to POWER_2"},
	{"18. GTU: Power Anode to POWER_2"},
	{"19. GTU: Power and Control Cathode to POWER_2"},
	{"20. BVT: HV+ to POWER_3"},
	{"21. BVT: HV- to POWER_3"},
	{"22. GTU: Power Anode to POWER_3"},
	{"23. GTU: Power and Control Cathode to POWER_3"},
	{"24. None"},
	{"25. None"},
	{"26. SL: Potential Anode to POTENTIAL_3"},
	{"27. SL+GTU: Potential Cathode to POTENTIAL_3"},
	{"28. BVT: HV+ to POWER_1"},
	{"29. BVT: HV- to POWER_1"},
	{"30. GTU: Power Anode to POWER_1"},
	{"31. GTU: Power and Control Cathode to POWER_1"},
	{"32. None"},
	{"33. None"},
	{"34. SL: Control Anode to CTRL_A2"},
	{"35. GTU: Control Anode to CTRL_A2"},
	{"36. None"},
	{"37. None"},
	{"38. GTU: Potential Control to CTRL_A2_POT"},
	{"39. None"},
	{"40. None"},
	{"41. None"},
	{"42. SL: Control Anode to CTRL_A1"},
	{"43. GTU: Control Anode to CTRL_A1"},
	{"44. None"},
	{"45. None"},
	{"46. GTU: Potential Control to CTRL_A1_POT"},
	{"47. None"}
};
CounterData CounterTablePointers6Gate4Wire[sizeof(CounterStorageDescription6Gate4Wire) / sizeof(CounterStorageDescription6Gate4Wire[0])] = {0};
const Int16U CounterStorageSize6Gate4Wire = sizeof(CounterStorageDescription6Gate4Wire) / sizeof(CounterStorageDescription6Gate4Wire[0]);
