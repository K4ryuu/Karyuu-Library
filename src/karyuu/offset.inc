#if defined _KARYUU_MODULE_OFFSET_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_OFFSET_INCLUDED_

stock int Karyuu_GetClientOffset(int iClient, const char[] cProp)
{
	return FindDataMapInfo(iClient, cProp);
}

/*
 * ===  REGION  ======================================================================
 *         Name:  Specified offset finders
 *  Description:  Pre-made offset finder functions for the most common offsets.
 * ===================================================================================
 */

stock int Karyuu_GetWeaponsOffset(int iClient)
{
	return FindDataMapInfo(iClient, "m_hMyWeapons");
}
