#if defined _KARYUU_MODULE_SOUND_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_SOUND_INCLUDED_

stock void Karyuu_PlayToRadius(float origin[3], float radius, char[] sound)
{
	char cBuffer[PLATFORM_MAX_PATH];
	FormatEx(STRING(cBuffer), "play %s", sound);
	float distance;

	for (int player = 0; player < MaxClients; player++)
	{
		if (Karyuu_IsValidPlayer(player))
		{
			distance = Karyuu_GetDistanceOrigin(player, origin);

			if (distance <= radius)
				ClientCommand(player, cBuffer);
		}
	}
}

stock bool Karyuu_CheckAudio(int iClient)
{
	if (!Karyuu_IsValidPlayer(iClient))
		return false;

	return QueryClientConVar(iClient, "voice_inputfromfile", Karyuu_Query_CheckAudio);
}

stock bool Karyuu_Query_CheckAudio(QueryCookie cCookie, int iClient, ConVarQueryResult rResult, const char[] sName, const char[] sValue)
{
	return rResult == ConVarQuery_Okay && StringToInt(sValue) == 1;
}