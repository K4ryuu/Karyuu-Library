#if defined _KARYUU_MODULE_SERVER_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_SERVER_INCLUDED_

enum EngineOS
{
	OS_Unknown,
	OS_Windows,
	OS_Linux,
	OS_Mac
};

stock EngineOS Karyuu_GetServerOS()
{
	static EngineOS Server_OS = OS_Unknown;

	if (Server_OS != OS_Unknown)
		return Server_OS;

	char cBuffer[512];
	ServerCommandEx(STRING(sBuffer), "status");

	Regex hRegex = CompileRegex("(os\\s+:\\s+\\w+)");
	hRegex.GetSubString(hRegex.Match(sBuffer), STRING(sBuffer));

	int iSystem = FindCharInString(sBuffer, ' ', true) + 1;

	Server_OS	= !strncmp(sBuffer[iSystem], "win", 3, false) ? OS_Windows
				: !strncmp(sBuffer[iSystem], "lin", 3, false) ? OS_Linux
															  : OS_Mac;

	delete hRegex;
	return Server_OS;
}

stock int Karyuu_GetClientCount(bool bAllowConnecting = false, bool bAllowBots = false, bool bAllowDead = true)
{
	int iCount = 0;
	for (int iClient = 1; iClient <= MaxClients; iClient++)
	{
		if (!IsClientConnected(iClient))
			continue;

		if (!bAllowConnecting && !IsClientInGame(iClient))
			continue;

		if (!bAllowBots && IsFakeClient(iClient))
			continue;

		if (!bAllowDead && !IsClientAlive(iClient))
			continue;

		iCount++;
	}
	return iCount;
}

stock int Karyuu_GetTeamClientCount(int iTeam, bool bAllowBots = false, bool bAllowDead = true)
{
	int iCount = 0;
	for (int iClient = 1; iClient <= MaxClients; iClient++)
	{
		if (!IsClientInGame(iClient) || GetClientTeam(iClient) != iTeam)
			continue;

		if (!bAllowBots && IsFakeClient(iClient))
			continue;

		if (!bAllowDead && !IsClientAlive(iClient))
			continue;

		iCount++;
	}
	return iCount;
}