#if defined _KARYUU_MODULE_INT_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_INT_INCLUDED_

#define MAX(% 0, % 1)	   (((% 0) > (% 1)) ? (% 0) : (% 1))

#define MAX_INTEGER_VALUE  2147483647
#define MAX_INTEGER_LENGTH 16

stock bool Karyuu_IsValidInt(int iValue)
{
	return -MAX_INTEGER_VALUE < iValue < MAX_INTEGER_VALUE;
}

stock bool Karyuu_IntToBool(int iInput)
{
	return !!iInput;
}

stock int Karyuu_uintcmp(int a, int b)
{
	if (a == b)
		return 0;

	char a_[12], b_[12];
	FormatEx(STRING(a_), "%u", a);
	FormatEx(STRING(b_), "%u", b);

	int a_size = strlen(a_), b_size = strlen(b_);

	switch (true)
	{
		case (a_size > b_size):
			return 1;
		case (a_size < b_size):
			return -1;
		default:
		{
			for (int i = 0; i < a_size; i++)
			{
				if (a_[i] > b_[i])
					return 1;
				else if (a_[i] < b_[i])
					return -1;
			}
		}
	}

	return 0;
}
