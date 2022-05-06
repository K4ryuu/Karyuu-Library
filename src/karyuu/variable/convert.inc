#if defined _KARYUU_MODULE_CONVERT_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_CONVERT_INCLUDED_

#define CONVERT_AUTH_LENGTH 64

stock bool Karyuu_Steam2ToSteam64(const char[] c_Auth2, char[] c_Auth64, int i_Size)
{
	if (strlen(c_Auth2) < 11 || c_Auth2[0] != 'S' || c_Auth2[6] == 'I')
	{
		c_Auth64[0] = 0;
		return false;
	}

	int i_steam64Auth = StringToInt(c_Auth2[10]) * 2 + 60265728 + c_Auth2[8] - 48;
	int i_Div		  = i_steam64Auth / 100000000;
	int i_Idx		  = 9 - (i_Div ? i_Div / 10 + 1 : 0);

	FormatEx(c_Auth64[i_Idx], i_Size - i_Idx, "%d", i_steam64Auth);
	i_Idx = i_steam64Auth[9];
	FormatEx(c_Auth64, i_Size, "%d", 765611979 + i_Div);
	i_steam64Auth[9] = i_Idx;
	return true;
}

stock bool Karyuu_Steam3ToSteam2(const char[] cAuth3, char[] cAuth2, int iSize)
{
	if (!Karyuu_StrContains(cAuth3, "[U:1:") || strlen(cAuth3) >= CONVERT_AUTH_LENGTH)
		return false;

	const int startIndex = 5;

	char	  xBuf[CONVERT_AUTH_LENGTH];
	int		  i = startIndex;

	for (; i < strlen(cAuth3) - 1; i++)
	{
		xBuf[i - startIndex] = cAuth3[i];
	}
	xBuf[i - startIndex] = EOS;

	int x				 = StringToInt(xBuf);
	if (x == 0)
	{
		return false;
	}

	int a = (x % 2);
	int b = (x - a) / 2;

	FormatEx(cAuth2, iSize, "STEAM_0:%d:%d", a, b);
	return true;
}

stock bool Karyuu_AuthToSteam64(const char[] cInput, char cOutput[CONVERT_AUTH_LENGTH])
{
	switch (cInput[0])
	{
		case 'S':
		{
			return Karyuu_ConvertSteam2ToSteam64(cInput, STRING(cOutput));
		}
		case '[':
		{
			char steam2[CONVERT_AUTH_LENGTH];
			if (ConvertSteam3ToSteam2(cInput, STRING(steam2)))
				return Karyuu_ConvertSteam2ToSteam64(steam2, STRING(cOutput));
		}
		case '7':
		{
			strcopy(STRING(cOutput), cInput);
			return true;
		}
		default: return false;
	}
}
