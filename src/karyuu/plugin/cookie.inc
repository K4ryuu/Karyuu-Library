#if defined _KARYUU_COOKIE_INCLUDED_
	#endinput
#endif
#define _KARYUU_COOKIE_INCLUDED_

#include <clientprefs>

stock int Karyuu_GetCookieInt(Cookie cookieHandle, int iClient)
{
	char sBuffer[MAX_INTEGER_LENGTH + 1];
	cookieHandle.Get(iClient, STRING(sBuffer));
	return StringToInt(sBuffer);
}

stock bool Karyuu_GetCookieBool(Cookie cookieHandle, int iClient)
{
	char sBuffer[8];
	cookieHandle.Get(iClient, STRING(sBuffer));
	return view_as<bool>(StringToInt(sBuffer[0]));
}

stock char Karyuu_GetCookieString(Cookie cookieHandle, int iClient)
{
	char sBuffer[MAX_INTEGER_LENGTH + 1];
	cookieHandle.Get(iClient, STRING(sBuffer));
	return sBuffer;
}