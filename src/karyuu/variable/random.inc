#if defined _KARYUU_MODULE_RANDOM_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_RANDOM_INCLUDED_

stock bool Karyuu_ShouldHappen(float fChance)
{
	return GetRandomInt(1, 100) <= fChance;
}

stock bool Karyuu_RandomBool()
{
	return view_as<bool>(Karyuu_RandomInt(0, 1));
}

stock int Karyuu_RandomInt(int iMin, int iMax)
{
	return RoundToZero(Karyuu_RandomFloat(float(iMin), float(iMax)));
}

stock float Karyuu_RandomFloat(float iMin, float iMax)
{
	return GetURandomFloat() * (iMax - iMin) + iMin;
}

stock int Karyuu_GetRandomClient()
{
	int iClientList[MAXPLAYERS + 1], iClientCount;

	for (int iClient = 1; iClient <= MaxClients; iClient++)
	{
		if (IsClientInGame(iClient))
			iClientList[iClientCount++] = iClient;
	}

	return iClientCount == 0 ? -1 : iClientList[Karyuu_RandomInt(0, iClientCount - 1)];
}