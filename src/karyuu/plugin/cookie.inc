#if defined _KARYUU_COOKIE_INCLUDED_
	#endinput
#endif
#define _KARYUU_COOKIE_INCLUDED_

#include <clientprefs>

stock int Karyuu_GetCookieInt(Cookie cookieHandle, int iClient)
{
	char sBuffer[Karyuu_MAX_INTEGER_LENGTH + 1];
	cookieHandle.Get(iClient, STRING(sBuffer));
	return strlen(sBuffer) == 0 ? 0 : StringToInt(sBuffer);
}

stock bool Karyuu_GetCookieBool(Cookie cookieHandle, int iClient)
{
	char sBuffer[8];
	cookieHandle.Get(iClient, STRING(sBuffer));
	return strlen(sBuffer) == 0 ? false : view_as<bool>(StringToInt(sBuffer[0]));
}

stock char[] Karyuu_GetCookieString(Cookie cookieHandle, int iClient)
{
	char sBuffer[Karyuu_MAX_INTEGER_LENGTH + 1];
	cookieHandle.Get(iClient, STRING(sBuffer));
	return sBuffer;
}

stock void Karyuu_SetCookieInt(Cookie cookieHandle, int iClient, int iValue)
{
	char sBuffer[Karyuu_MAX_INTEGER_LENGTH + 1];
	FormatEx(STRING(sBuffer), "%d", iValue);
	cookieHandle.Set(iClient, sBuffer);
}

stock void Karyuu_SetCookieBool(Cookie cookieHandle, int iClient, bool bValue)
{
	char sBuffer[8];
	FormatEx(STRING(sBuffer), "%d", view_as<int>(bValue));
	cookieHandle.Set(iClient, sBuffer);
}

stock void Karyuu_SetCookieString(Cookie cookieHandle, int iClient, const char[] sValue)
{
	cookieHandle.Set(iClient, sValue);
}