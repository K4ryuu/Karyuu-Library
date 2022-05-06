#if defined _KARYUU_MODULE_FLOAT_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_FLOAT_INCLUDED_

#define MAX_FLOAT_LENGTH 32

stock float Karyuu_FloatMultiply(float fValue, float fMultiply)
{
	return fValue *= 1.0 + fMultiply;
}

stock float Karyuu_FloatDivide(float fValue, float fMultiply)
{
	return fValue *= 1.0 - fMultiply;
}