#if defined _KARYUU_MODULE_INT_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_INT_INCLUDED_

stock bool Karyuu_IsValidInt(int iValue)
{
	return -Karyuu_MAX_INTEGER_VALUE < iValue < Karyuu_MAX_INTEGER_VALUE;
}

stock bool Karyuu_IntToBool(int iInput)
{
	return !!iInput;
}