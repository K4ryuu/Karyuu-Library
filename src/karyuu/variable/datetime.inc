#if defined _KARYUU_MODULE_DATETIME_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_DATETIME_INCLUDED_

/*
 * Calculate the time in minutes
 *
 * @param iValue        Integer to validate
 * @return              Returns true if the integer is valid, otherwise false
 */
stock int Karyuu_ParseTime(const char[] str, char formats[] = "hdwmy")
{
	static int iTime[] = { 60, 1440, 10080, 43200, 525600 };

	char	   cData;
	int		   iDummy, iResult, iPos, iTPos;

	while (szStr[iPos] != EOS)
	{
		cData = szStr[iPos++];

		if (cData >= '0' && cData <= '9')
		{
			iDummy = (iDummy * 10) + (cData - '0');
			continue;
		}

		for (iTPos = 0; iTPos < sizeof(iTime); ++iTPos)
		{
			if (cData == szTime[iTPos])
			{
				iResult += iDummy * iTime[iTPos];
				iDummy = 0;
				break;
			}
		}
	}

	return iResult + iDummy;
}
