#if defined _KARYUU_MODULE_CLIENT_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_CLIENT_INCLUDED_

#define MAX_AUTH_LENGTH			  21
#define MAX_IP_LENGTH 				23

#define KARYUU_LOOP_CLIENTS(%1) for (int %1 = 1; %1 <= MaxClients; %1++) if (IsClientInGame(%1))
#define KARYUU_LOOP_PLAYERS(%1) for (int %1 = 1; %1 <= MaxClients; %1++) if (IsClientInGame(%1) && !IsFakeClient(%1))

enum WaterLevel
{
	WL_NotInWater = 0,
	WL_Feet,
	WL_Waist,
	WL_Full
};

enum TeamType
{
	TeamType_Unknown = 0,
	TeamType_Active,
	TeamType_Spectator,
	TeamType_Unassigned
};

stock bool Karyuu_IsClientIndex(int iIndex)
{
	return 0 < iIndex <= MaxClients;
}

stock bool Karyuu_IsValidClient(int iClient)
{
	return Karyuu_IsClientIndex(iClient) && IsClientInGame(iClient);
}

stock bool Karyuu_IsValidPlayer(int iClient)
{
	return (Karyuu_IsValidClient(iClient) && !IsFakeClient(iClient) && !IsClientSourceTV(iClient) && !IsClientReplay(iClient));
}

stock bool Karyuu_IsValidClient2(int iClient, bool bAllowConnecting = false, bool bAllowBot = false, bool bAllowDead = true, bool bAllowUnAuthorized = false)
{
	return (Karyuu_IsClientIndex(iClient) && IsClientConnected(iClient) && (bAllowConnecting || !IsClientInGame(iClient)) && (bAllowBot || !IsFakeClient(iClient)) && (bAllowDead || !IsPlayerAlive(iClient)) && (bAllowUnAuthorized || !IsClientAuthorized(iClient)));
}

stock bool Karyuu_IsClientAuthorized(int iClient, bool bCheck = true)
{
	return (!bCheck || Karyuu_IsValidPlayer(iClient)) && IsClientAuthorized(iClient);
}

stock bool Karyuu_IsClientInTeam(int iClient)
{
	return Karyuu_IsActiveTeam(GetClientTeam(iClient));
}

stock bool Karyuu_IsClientInVehicle(int iClient)
{
	return Karyuu_GetClientVehicle(iClient) != -1;
}

stock bool Karyuu_IsClientCrouching(int iClient)
{
	return GetEntityFlags(iClient) & FL_DUCKING;
}

stock bool Karyuu_IsClientOnGround(int iClient)
{
	return GetEntityFlags(iClient) & FL_ONGROUND;
}

stock bool Karyuu_IsClientOnLadder(int iClient)
{
	return GetEntityMoveType(iClient) == MOVETYPE_LADDER;
}

stock bool Karyuu_IsClientCoaching(int iClient)
{
	return (GetClientTeam(iClient) == CS_TEAM_SPECTATOR && Karyuu_GetEntPropBool(iClient, Prop_Send, "m_iCoachingTeam"));
}

stock bool Karyuu_IsClientTimingOut(int iClient, bool bCheck = true)
{
	return (!bCheck || Karyuu_IsValidPlayer(iClient)) && IsClientTimingOut(iClient);
}

stock bool Karyuu_IsLookingAtWall(int iClient, float fDistance = 40.0)
{

	float fEye[3], fEyeAngle[3];
	bool isClientLookingAtWall = false;

	GetClientEyePosition(iClient, fEye);
	GetClientEyeAngles(iClient, fEyeAngle);

	fEyeAngle[0] = 0.0;

	Handle hTrace = TR_TraceRayFilterEx(fEye, fEyeAngle, CONTENTS_SOLID, RayType_Infinite, Karyuu_LookingWall_TraceEntityFilter);

	if (TR_DidHit(hTrace))
	{
		if (TR_GetEntityIndex(hTrace) > 0)
		{
			CloseHandle(hTrace);
			return false;
		}

		float fEnd[3];

		TR_GetEndPosition(fEnd, hTrace);

		if (GetVectorDistance(fEye, fEnd, true) <= (fDistance * fDistance))
			isClientLookingAtWall = true;
	}

	CloseHandle(hTrace);

	return isClientLookingAtWall;
}

public bool Karyuu_LookingWall_TraceEntityFilter(int iEntity, int iMask)
{
	return iEntity == 0;
}

stock TeamType Karyuu_GetClientTeamType(int iClient, int iTeam)
{
	switch (GetClientTeam(iClient))
	{
		case CS_TEAM_NONE:			return TeamType_Unassigned;
		case CS_TEAM_T, CS_TEAM_CT:	return TeamType_Active;
		case CS_TEAM_SPECTATOR:		return TeamType_Spectator;
		default:					return TeamType_Unknown;
	}
}

stock bool Karyuu_GetClientAuthId(int iClient, AuthIdType aiType, char[] szAuth, int iSize, bool bCheck = true)
{
	return (!bCheck || Karyuu_IsClientAuthorized(iClient)) && GetClientAuthId(iClient, aiType, szAuth, iSize);
}

stock float Karyuu_GetPlayerSpeed(int iClient)
{
	float fVelocity[3];
	GetEntPropVector(iClient, Prop_Data, "m_vecAbsVelocity", fVelocity);
	return GetVectorLength(fVelocity);
}

stock int Karyuu_GetClientVehicle(int iClient)
{
	return GetEntPropEnt(iClient, Prop_Send, "m_hVehicle");
}

stock int Karyuu_GetClientArmor(int iClient)
{
	return GetEntProp(iClient, Prop_Data, "m_ArmorValue");
}

stock int Karyuu_GetArmor(int iClient)
{
	return GetEntProp(iClient, Prop_Data, "m_ArmorValue");
}

stock void Karyuu_ResetArmor(int iClient)
{
	if (Karyuu_IsValidClient(iClient))
	{
		SetEntProp(iClient, Prop_Send, "m_bHasHelmet", 0);
		SetEntProp(iClient, Prop_Send, "m_ArmorValue", 0, 0);

		if (GetEngineVersion() == Engine_CSGO)
		{
			SetEntProp(iClient, Prop_Send, "m_bHasHeavyArmor", 0);
			SetEntProp(iClient, Prop_Send, "m_bWearingSuit", 0);
		}
	}
}

stock void Karyuu_SetClientArmor(int iClient, int value)
{
	SetEntProp(iClient, Prop_Data, "m_ArmorValue", value);
}

stock void Karyuu_GetClientLastPlaceName(int iClient, char[] szBuffer, int iSize)
{
	GetEntPropString(iClient, Prop_Send, "m_szLastPlaceName", szBuffer, iSize);
}

stock WaterLevel Karyuu_GetClientWaterLevel(int iClient)
{
	return view_as<WaterLevel>(GetEntProp(iClient, Prop_Send, "m_nWaterLevel"));
}

stock int Karyuu_GetClientFOV(int iClient)
{
	return GetEntProp(iClient, Prop_Send, "m_iFOV");
}

stock void Karyuu_SetClientFOV(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Send, "m_iFOV", iValue);
}

stock void Karyuu_GetClientViewOffset(int iClient, float fVec[3])
{
	GetEntPropVector(iClient, Prop_Data, "m_vecViewOffset", fVec);
}

stock void Karyuu_SetViewOffset(int iClient, float fVec[3])
{
	SetEntPropVector(iClient, Prop_Data, "m_vecViewOffset", fVec);
}

stock void Karyuu_SetClientCoaching(int iClient, int iTeam)
{
	SetEntProp(iClient, Prop_Send, "m_iCoachingTeam", iTeam);
}

stock bool Karyuu_ChangeClientTeamAlive(int iClient, int iTeam)
{
	if (!Karyuu_IsClientIndex(iClient) || !IsClientInGame(iClient) || !IsPlayerAlive(iClient) || iTeam < 2 || iTeam > 3)
		return false;

	int iLifeState = GetEntProp(iClient, Prop_Send, "m_lifeState");
	SetEntProp(iClient, Prop_Send, "m_lifeState", 2);
	ChangeClientTeam(iClient, iTeam);
	SetEntProp(iClient, Prop_Send, "m_lifeState", iLifeState);
	return true;
}

stock void Karyuu_SetClientFrags(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Data, "m_iFrags", iValue);
}

stock void Karyuu_SetClientDeaths(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Data, "m_iDeaths", iValue);
}

stock int Karyuu_GetClientDeaths(int iClient)
{
	return GetEntProp(iClient, Prop_Data, "m_iDeaths");
}

stock int Karyuu_GetClientMoney(int iClient)
{
   return GetEntProp(iClient, Prop_Send, "m_iAccount");
}

stock void Karyuu_SetClientMoney(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Send, "m_iAccount", iValue);
}

stock void Karyuu_GiveClientMoney(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Send, "m_iAccount", GetEntProp(iClient, Prop_Send, "m_iAccount") + iValue);
}

stock void Karyuu_SetClientHelmet(int iClient, bool bHasHelmet)
{
	SetEntProp(iClient, Prop_Send, "m_bHasHelmet", bHasHelmet);
}

stock void Karyuu_SetClientHud(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Send, "m_iHideHUD", iValue);
}

stock int Karyuu_GetVehicle(int iClient)
{
	return GetEntPropEnt(iClient, Prop_Send, "m_hVehicle");
}

stock bool Karyuu_IsInVehicle(int iClient)
{
	return !(Karyuu_GetVehicle(iClient) == -1);
}

stock bool Karyuu_ExitVehicle(int iClient)
{
	int iVehicle = Karyuu_GetVehicle(iClient);
	return iVehicle != -1 && AcceptEntityInput(iVehicle, "ExitVehicle");
}

stock void Karyuu_SetClanTag(int iClient, const char[] sBuffer)
{
	if (Karyuu_IsValidClient(iClient))
		CS_SetClientClanTag(iClient, sBuffer);
}

stock void Karyuu_SafeSlay(int iClient)
{
	if (Karyuu_IsValidClient(iClient))
		ForcePlayerSuicide(iClient);
}

stock void Karyuu_ShowOverlayToClient(int iClient, const char[] cOverlayPath)
{
	ClientCommand(iClient, "r_screenoverlay \"%s\"", cOverlayPath);
}

stock bool Karyuu_ClientHasDefuser(int iClient)
{
	return view_as<bool>(GetEntProp(iClient, Prop_Send, "m_bHasDefuser"));
}

stock void Karyuu_GiveClientDefuser(int iClient)
{
	SetEntProp(iClient, Prop_Send, "m_bHasDefuser", true);
}

stock void Karyuu_RemoveClientDefuser(int iClient)
{
	SetEntProp(iClient, Prop_Send, "m_bHasDefuser", false);
}

stock void Karyuu_ShowOverlayToAll(const char[] cOverlayPath)
{
	for (int iClient = 1; iClient <= MaxClients; iClient++)
	{
		if (Karyuu_IsValidPlayer(iClient))
			Karyuu_ShowOverlayToClient(iClient, cOverlayPath);
	}
}

stock void Karyuu_GodMode(int iClient, bool bEnabled)
{
	if (Karyuu_IsValidPlayer(iClient))
		SetEntProp(iClient, Prop_Data, "m_takedamage", bEnabled ? 0 : 2, 1);
}

stock void Karyuu_MutePlayer(int iClient)
{
	if (Karyuu_IsValidPlayer(iClient))
		SetClientListeningFlags(iClient, VOICE_MUTED);
}

stock void Karyuu_UnmutePlayer(int iClient)
{
	if (Karyuu_IsValidPlayer(iClient))
		SetClientListeningFlags(iClient, VOICE_NORMAL);
}

stock void Karyuu_SetThirdPerson(int iClient)
{
	if (Karyuu_IsValidClient(iClient))
	{
		SetEntPropEnt(iClient, Prop_Send, "m_hObserverTarget", 0);
		SetEntProp(iClient, Prop_Send, "m_iObserverMode", 1);
		SetEntProp(iClient, Prop_Send, "m_bDrawViewmodel", 0);
		SetEntProp(clieiClientnt, Prop_Send, "m_iFOV", 120);
	}
}

stock void Karyuu_SetFirstPerson(int client)
{
	if (Karyuu_IsValidClient(iClient))
	{
		SetEntPropEnt(iClient, Prop_Send, "m_hObserverTarget", 1);
		SetEntProp(iClient, Prop_Send, "m_iObserverMode", 0);
		SetEntProp(iClient, Prop_Send, "m_bDrawViewmodel", 1);
		SetEntProp(iClient, Prop_Send, "m_iFOV", 90);
	}
}

stock void Karyuu_ToggleThirdPerson(int iClient)
{
	if (Karyuu_IsInThirdPerson(iClient))
	{
		Karyuu_SetFirstPerson(iClient);
	}
	else
		Karyuu_SetThirdPerson(iClient);
}

stock void Karyuu_RadarVisibilityToggle(int iClient, bool bStatus)
{
	static int iOffset = FindSendPropInfo("CBaseEntity", "m_bSpotted");
	if (iOffset > 0)
	{
		static Address g_aCanBeSpotted = view_as<Address>(iOffset - 4);

		if (bStatus)
		{
			SetEntProp(iClient, Prop_Send, "m_bSpotted", false);
			SetEntProp(iClient, Prop_Send, "m_bSpottedByMask", 0, 4, 0);
			SetEntProp(iClient, Prop_Send, "m_bSpottedByMask", 0, 4, 1);

			StoreToAddress(GetEntityAddress(iClient) + g_aCanBeSpotted, 0, NumberType_Int32);
		}
		else
			StoreToAddress(GetEntityAddress(iClient) + g_aCanBeSpotted, 9, NumberType_Int32);
	}
}

stock int Karyuu_FindBySteamId(const char[] szAuth, AuthIdType iType)
{
	int	 iMax = GetMaxClients();
	char szTempAuth[MAX_AUTH_LENGTH];

	for (int iClient = 0; iClient < iMax; iClient++)
	{
		if (!Karyuu_IsValidClient(iClient) || !IsClientAuthorized(iClient))
			continue;

		if (GetClientAuthId(iClient, iType, STRING(szTempAuth)) && Karyuu_StrEquals(szAuth, szTempAuth))
			return iClient;
	}
	return INVALID_ENT_REFERENCE;
}

stock bool Karyuu_GetClientCrosshairOrigin(int iClient, float fOrigin[3], bool bFilterPlayers = true, float fDistance = -35.0)
{
	if (iClient == 0 || iClient > MaxClients || !IsClientInGame(iClient))
		return false;

	float vOrigin[3];
	GetClientEyePosition(iClient, vOrigin);

	float vAngles[3];
	GetClientEyeAngles(iClient, vAngles);

	Handle hTrace = TR_TraceRayFilterEx(vOrigin, vAngles, MASK_SHOT, RayType_Infinite, bFilterPlayers ? Karyuu_TraceEntityFilterPlayer : Karyuu_TraceEntityFilterNone, iClient);
	bool bReturn = TR_DidHit(hTrace);

	if (bReturn)
	{
		float vStart[3];
		TR_GetEndPosition(vStart, hTrace);

		float vBuffer[3];
		GetAngleVectors(vAngles, vBuffer, NULL_VECTOR, NULL_VECTOR);

		fOrigin[0] = vStart[0] + (vBuffer[0] * fDistance);
		fOrigin[1] = vStart[1] + (vBuffer[1] * fDistance);
		fOrigin[2] = vStart[2] + (vBuffer[2] * fDistance);
	}

	delete hTrace;
	return bReturn;
}

stock bool Karyuu_TraceEntityFilterPlayer(int iEntity, int iMask, any aData)
{
	return iEntity > GetMaxClients() || !iEntity;
}

stock bool Karyuu_TraceEntityFilterNone(int iEntity, int iMask, any aData)
{
	return iEntity != aData;
}

stock bool Karyuu_IsAdmin(int iClient)
{
	AdminId aiAdmin = GetUserAdmin(iClient);

	if (aiAdmin == INVALID_ADMIN_ID)
		return false;

	return GetAdminFlag(aiAdmin, Admin_Generic);
}

stock bool Karyuu_CheckAdminFlagsByString(int iClient, const char[] sFlags)
{
	return Karyuu_ClientHasFlag(iClient, ReadFlagString(sFlags));
}

stock bool Karyuu_ClientHasFlag(int iClient, int iFlags)
{
	AdminId aiAdmin = GetUserAdmin(iClient);

	if (aiAdmin == INVALID_ADMIN_ID)
		return false;

	int iUserFlags = GetAdminFlags(aiAdmin, Access_Effective);
	return Karyuu_ContainsBits(iUserFlags, iFlags) || Karyuu_ContainsBits(iUserFlags, ADMFLAG_ROOT);
}

stock int Karyuu_GetObserverTarget(int iClient)
{
	return GetEntPropEnt(iClient, Prop_Send, "m_hObserverTarget");
}

stock int Karyuu_SetObserverTarget(int iClient, int iEntity)
{
	SetEntPropEnt(iClient, Prop_Send, "m_hObserverTarget", iEntity);
}

stock int Karyuu_GetFOV(int iClient)
{
	return GetEntProp(iClient, Prop_Send, "m_iFOV");
}

stock int Karyuu_SetFOV(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Send, "m_iFOV", iValue);
}

stock bool Karyuu_IsInThirdPerson(int iClient)
{
	return view_as<bool>(GetEntProp(iClient, Prop_Data, "m_iObserverMode"));
}

stock void Karyuu_LastLocation(int iClient, const char[] sBuffer, int iLength)
{
	GetEntPropString(iClient, Prop_Send, "m_szLastPlaceName", sBuffer, iLength);
}

stock int Karyuu_GetScore(int iClient)
{
	return GetClientFrags(client);
}

stock void Karyuu_SetScore(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Data, "m_iFrags", iValue);
}

stock void Karyuu_RemoveAllDecals(int iClient)
{
	ClientCommand(iClient, "r_cleardecals");
}

stock void Karyuu_Impulse(int iClient, int iValue)
{
	SetEntProp(iClient, Prop_Data, "m_nImpulse", iValue);
}

stock bool Karyuu_IsClientReloading(int iClient)
{
	int iWeapon = Karyuu_GetActiveWeapon(iClient);

	if (iWeapon == INVALID_ENT_REFERENCE)
		return false;

	return Karyuu_IsWeaponReloading(iWeapon);
}

stock int Karyuu_GetPing(int iClient)
{
	return RoundFloat(GetClientLatency(iClient, NetFlow_Both) * 1000.0);
}

stock int Karyuu_GetLoss(int iClient)
{
	return RoundFloat(GetClientAvgLoss(iClient, NetFlow_Both));
}