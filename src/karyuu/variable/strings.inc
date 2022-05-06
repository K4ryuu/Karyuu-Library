#if defined _KARYUU_MODULE_STRING_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_STRING_INCLUDED_

#define STRING(%1) %1, sizeof(%1)
#define STRING_EMPTY "\0"

stock bool Karyuu_IsStringEmpty(const char[] sBuffer)
{
	return !sBuffer[0] || strlen(sBuffer) == 0;
}

stock bool Karyuu_IsStringNumber(const char[] sBuffer)
{
	int iTarget, iDots, iNumbers;

	if (sBuffer[iTarget] == '+' || sBuffer[iTarget] == '-')
		iTarget++;

	while (sBuffer[iTarget] != EOS)
	{
		if (IsCharNumeric(sBuffer[iTarget]))
		{
			iNumbers++;
		}
		else if (sBuffer[iTarget] == '.')
		{
			iDots++;

			if (iDots > 1)
				return false;
		}
		else
			return false;

		iTarget++;
	}

	return iNumbers > 0;
}

stock bool Karyuu_StringToBool(const char[] sBuffer)
{
	return view_as<bool>(StringToInt(sBuffer));
}

stock void Karyuu_TruncateString(char[] sBuffer)
{
	sBuffer[0] = EOS;
}

stock int Karyuu_FlagStringToInt(char[] buffer)
{
	AdminFlag aFlag;
	return FindFlagByChar(buffer[0], aFlag) ? FlagToBit(aFlag) : INVALID_ENT_REFERENCE;
}

stock char[] Karyuu_StringBuilder(const char[] cFormat, any...)
{
	int iLength			= strlen(cFormat) + 255;
	char[] cBuiltString = new char[iLength];

	VFormat(cBuiltString, iLength, cFormat, 2);
	return cBuiltString;
}

stock int Karyuu_FlagIntToString(int iFlag)
{
	AdminFlag aFlag;
	int		  iChar;
	return (BitToFlag(iFlag, aFlag) && FindFlagChar(aFlag, iChar)) ? iChar : INVALID_ENT_REFERENCE;
}

stock char Karyuu_IntToString(int iInt)
{
	char cBuffer[64];
	FormatEx(STRING(cBuffer), "%d", iInt);
	return cBuffer;
}

stock void Karyuu_EscapeString(char[] string, int maxlen, bool name = false)
{
	if (name)
	{
		ReplaceString(string, maxlen, "everyone", "everyonｅ");
		ReplaceString(string, maxlen, "here", "herｅ");
		ReplaceString(string, maxlen, "discordtag", "dｉscordtag");
	}

	ReplaceString(string, maxlen, "#", "＃");
	ReplaceString(string, maxlen, "@", "＠");
	ReplaceString(string, maxlen, "_", "ˍ");
	ReplaceString(string, maxlen, "'", "＇");
	ReplaceString(string, maxlen, "`", "＇");
	ReplaceString(string, maxlen, "~", "∽");
	ReplaceString(string, maxlen, "\"", "＂");
	ReplaceString(string, maxlen, "%", "％");
	ReplaceString(string, maxlen, "  ", " ");
}

stock bool Karyuu_StrEquals(const char[] string, char[] substring, bool caseSensitive = true)
{
	return strcmp(string, substring, caseSensitive) == 0;
}

stock bool Karyuu_StrContains(const char[] String, const char[] Text, bool caseSensitive = false)
{
	return StrContains(String, Text, caseSensitive) != -1;
}

stock void Karyuu_StringToLower(char[] sText, int iStartLen = 0, int iEndLen = 0)
{
	int iLen = strlen(sText) + 1;

	if (1 > iEndLen || iLen < iEndLen)
		iEndLen = iLen;

	for (int i = iStartLen; i != iEndLen; i++)
	{
		sText[i] |= 0x20;
	}
}

stock void Karyuu_StringToUpper(char[] sText, int iStartLen = 0, int iEndLen = 0)
{
	int iLen = strlen(sText) + 1;

	if (1 > iEndLen || iLen < iEndLen)
		iEndLen = iLen;

	for (int i = iStartLen; i != iEndLen; i++)
	{
		sText[i] &= ~0x20;
	}
}

stock void Karyuu_FirstCharUpper(char[] sText)
{
	if (strlen(sText) > 0)
		sText[0] &= ~0x20;
}

stock void Karyuu_RemoveFrontString(char[] sText, int iSize, int iPosition)
{
	strcopy(sText, iSize, sText[iPosition]);
}

stock bool Karyuu_StartsWith(const char[] cBuffer, const char[] cSubString)
{
	int n = 0;
	while (cSubString[n] != EOS)
	{
		if (cBuffer[n] == EOS || cBuffer[n] != cSubString[n])
			return false;

		n++;
	}
	return true;
}

/*
 * Count the characters in a string
 *
 * @param str           String to check
 * @return              Count of characters in the string
 */
stock int Karyuu_CharCount(const char[] str)
{
	int iCount, len = strlen(str);

	for (int i, b; i < len; i++)
	{
		if (b = IsCharMB(str[i]))
			i += (b - 1);

		iCount++;
	}

	return iCount;
}

stock int Karyuu_CountChar(int character, const char[] string)
{
	int count, len = strlen(string);

	for (int i; i < len; i++)
	{
		if (string[i] == character)
			count++;
	}
	return count;
}