#if defined _KARYUU_MODULE_PROP_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_PROP_INCLUDED_

/*
 * ===  REGION  ======================================================================
 *           Name:  Additional Functions
 *    Description:  Functions that are not part of the original library, but useful
 * ===================================================================================
 */

stock bool Karyuu_GetPropBool(const char[] cPropName)
{
	return view_as<bool>(GameRules_GetProp(cPropName));
}

stock bool Karyuu_GetEntPropBool(int iEntity, PropType iType, const char[] cProp)
{
	return view_as<bool>(GetEntProp(iEntity, iType, cProp));
}

/*
 * ===  REGION  ======================================================================
 *           Name:  Safe Functions
 *    Description:  Functions with pre-defined validations
 * ===================================================================================
 */

stock void Karyuu_SafeGetEntPropVector(int iEntity, const char[] szProp, float fVec[3], PropType iType)
{
	if (!IsValidEdict(iEntity) || !HasEntProp(iEntity, iType, szProp))
		return;

	GetEntPropVector(iEntity, iType, szProp, fVec);
}

stock int Karyuu_SafeGetEntPropEnt(int iEntity, PropType iType, const char[] szProp)
{
	if (!IsValidEdict(iEntity) || !HasEntProp(iEntity, iType, szProp))
		return INVALID_ENT_REFERENCE;

	return GetEntPropEnt(iEntity, iType, szProp);
}

stock int Karyuu_SafeGetEntPropString(int iEntity, PropType iType, const char[] szProp, char[] szBuffer, int iSize)
{
	if (!IsValidEdict(iEntity) || !HasEntProp(iEntity, iType, szProp))
		return INVALID_ENT_REFERENCE;

	return GetEntPropString(iEntity, iType, szProp, cBuffer, iSize);
}