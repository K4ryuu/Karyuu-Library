#if defined _KARYUU_MODULE_STRING_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_STRING_INCLUDED_

stock bool Karyuu_IsStringEmpty(const char[] sBuffer)
{
	return !sBuffer[0] || strlen(sBuffer) == 0;
}

stock bool Karyuu_IsStringSimpleNumber(const char[] sBuffer)
{
	int iLength = strlen(sBuffer);
	for (int i = 0; i < iLength; i++)
	{
		if (sBuffer[i] == EOS)
			break;

		if (!IsCharNumeric(sBuffer[i]))
			return false;
	}

	return true;
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

stock char[] Karyuu_IntDotBuilder(int iValue)
{
	char cValue[Karyuu_MAX_INTEGER_LENGTH + 1];
	FormatEx(STRING(cValue), "%d", iValue);

	char cBuffer[32];
	int iLength = strlen(cValue);

	if (iLength <= 3)
	{
		strcopy(STRING(cBuffer), cValue);
		return cBuffer;
	}

	int iCounter = iLength % 3;

	if (iCounter == 0)
		iCounter = 3;

	for (int i = 0, j = 0; i < iLength; i++, j++)
	{
		if (iCounter == 0)
		{
			cBuffer[j] = '.';
			j++;
			iCounter = 2;
		}
		else
			iCounter--;

		cBuffer[j] = cValue[i];
	}

	return cBuffer;
}

stock int Karyuu_FlagIntToString(int iFlag)
{
	AdminFlag aFlag;
	int		  iChar;
	return (BitToFlag(iFlag, aFlag) && FindFlagChar(aFlag, iChar)) ? iChar : INVALID_ENT_REFERENCE;
}

stock char[] Karyuu_IntToString(int iInt)
{
	char cBuffer[Karyuu_MAX_INTEGER_LENGTH + 1];
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

stock bool Karyuu_EndsWith(const char[] cBuffer, const char[] cSubString)
{
	int n_str = strlen(cBuffer) - 1;
	int n_subString = strlen(cSubString) - 1;

	if(n_str < n_subString)
		return false;

	while (n_str != 0 && n_subString != 0)
	{
		if (cBuffer[n_str--] != cSubString[n_subString--])
			return false;
	}

	return true;
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

stock void Karyuu_ShuffleString(char[] sBuffer, int iSize)
{
	ArrayList arTemp = new ArrayList();

	for (int iCount = 0; iCount < iSize; iCount++)
	{
		if (sBuffer[iCount] == EOS)
			break;

		arTemp.Push(sBuffer[iCount]);
	}

	arTemp.Sort(Sort_Random, Sort_String);

	int iarSize = arTemp.Length;
	for (int iCount = 0; iCount < iarSize; iCount++)
	{
		sBuffer[iCount] = view_as<char>(arTemp.Get(iCount));
	}
	delete arTemp;
}

stock void Karyuu_GenerateUUID(char[] sBuffer, int iLength)
{
	FormatEx(sBuffer, iLength, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x",
		// 32 bits for "time_low"
		GetRandomInt(0, 0xffff), GetRandomInt(0, 0xffff),

		// 16 bits for "time_mid"
		GetRandomInt(0, 0xffff),

		// 16 bits for "time_hi_and_version"
		// four most significant bits holds version number 4
		(GetRandomInt(0, 0x0fff) | 0x4000),

		// 16 bits, 8 bits for "clk_seq_hi_res",
		// 8 bits for "clk_seq_low",
		// two most significant bits holds zero and one for variant DCE1.1
		(GetRandomInt(0, 0x3fff) | 0x8000),

		// 48 bits for node
		GetRandomInt(0, 0xffff), GetRandomInt(0, 0xffff), GetRandomInt(0, 0xffff)
	);
}