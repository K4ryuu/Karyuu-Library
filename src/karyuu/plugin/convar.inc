#if defined _KARYUU_CONVARS_INCLUDED_
	#endinput
#endif
#define _KARYUU_CONVARS_INCLUDED_

#define MAX_CONVAR_VALUE_SIZE 256

stock int Karyuu_GetConVarIntSafe(const char[] cName)
{
	ConVar cvConVar = FindConVar(cName);
	return (cvConVar == null ? -1 : cvConVar.IntValue);
}

stock bool Karyuu_SetConVarIntSafe(const char[] cName, int iValue)
{
	ConVar cvConVar = FindConVar(cName);

	if (cvConVar == null)
		return false;

	cvConVar.IntValue = iValue;
	return true;
}

stock bool Karyuu_SetConVarStringSafe(const char[] cName, const char[] cValue)
{
	ConVar cvConVar = FindConVar(cName);

	if (cvConVar == null)
		return false;

	cvConVar.SetString(cValue);
	return true;
}

stock bool Karyuu_GetConVarStringSafe(const char[] cName, char[] cValue, int iLength)
{
	ConVar cvConVar = FindConVar(cName);

	if (cvConVar == null)
		return false;

	cvConVar.GetString(cValue, iLength);
	return true;
}

stock char[] Karyuu_GetConVarStringSafeEx(const char[] cName)
{
	ConVar cvConVar = FindConVar(cName);

	if (cvConVar == null)
		return NULL_STRING;

	char cValue[MAX_CONVAR_VALUE_SIZE];
	cvConVar.GetString(STRING(cValue));
	return cValue;
}