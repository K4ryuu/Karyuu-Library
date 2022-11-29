#if defined _KARYUU_TEAMS_INCLUDED_
	#endinput
#endif
#define _KARYUU_TEAMS_INCLUDED_

stock int Karyuu_GetPlayersInTeam(int iTeam, bool bAllowBots = false)
{
	int iCount = 0;
	for (int i = 1; i <= MaxClients; i++)
	{
		if (Karyuu_IsValidClient(i) && (bAllowBots || !IsFakeClient(i)) && GetClientTeam(i) == iTeam)
		{
			iCount++;
		}
	}
	return iCount;
}

stock bool Karyuu_IsActiveTeam(int iTeam)
{
	return iTeam == CS_TEAM_T || iTeam == CS_TEAM_CT;
}

stock int Karyuu_GetTeamIndex(int iTeam)
{
	return (iTeam == CS_TEAM_T)	 ? 2
		 : (iTeam == CS_TEAM_CT) ? 1
								 : 0;
}

stock void Karyuu_SetTeamName(int iTeam, const char[] cValue)
{
	char sBuffer[64];
	FormatEx(STRING(sBuffer), "mp_teamname_%d", Karyuu_GetTeamIndex(iTeam));
	Karyuu_SetConVarStringSafe(sBuffer, cValue);
}

stock void Karyuu_SetTeamLogo(int iTeam, const char[] cValue)
{
	char sBuffer[64];
	FormatEx(STRING(sBuffer), "mp_teamlogo_%d", Karyuu_GetTeamIndex(iTeam));
	Karyuu_SetConVarStringSafe(sBuffer, cValue);
}

stock void Karyuu_SetTeamFlag(int iTeam, const char[] cValue)
{
	char sBuffer[64];
	FormatEx(STRING(sBuffer), "mp_teamlogo_%d", Karyuu_GetTeamIndex(iTeam));
	Karyuu_SetConVarStringSafe(sBuffer, cValue);
}

stock void Karyuu_SetTeamScore(int iTeam, int iValue)
{
	char sBuffer[64];
	FormatEx(STRING(sBuffer), "mp_teamscore_%d", Karyuu_GetTeamIndex(iTeam));
	Karyuu_SetConVarIntSafe(sBuffer, iValue);
}

stock void Karyuu_SetTeamText(int iTeam, const char[] cValue)
{
	char sBuffer[64];
	FormatEx(STRING(sBuffer), "mp_teammatchstat_%d", Karyuu_GetTeamIndex(iTeam));
	Karyuu_SetConVarStringSafe(sBuffer, cValue);
}

stock void Karyuu_SetTeamData(int iTeam, const char[] cName, const char[] cFlag = "", const char[] cLogo = "", const char[] cText = "", int iScore = 0)
{
	Karyuu_SetTeamName(iTeam, cName);
	Karyuu_SetTeamLogo(iTeam, cLogo);
	Karyuu_SetTeamFlag(iTeam, cFlag);
	Karyuu_SetTeamScore(iTeam, iScore);
	Karyuu_SetTeamText(iTeam, cText);
}
