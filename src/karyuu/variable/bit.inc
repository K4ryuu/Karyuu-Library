#if defined _KARYUU_MODULE_BIT_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_BIT_INCLUDED_

stock void Karyuu_AddBits(int &iSum, int iBits)
{
	iSum |= iBits;
}

stock void Karyuu_RemoveBits(int &iSum, int iBits)
{
	iSum &= ~iBits;
}

stock bool Karyuu_ContainsBits(int iSum, int iBits)
{
	return (iSum & iBits) == iBits;
}