#if defined _KARYUU_MODULE_WEAPON_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_WEAPON_INCLUDED_

#define MAX_WEAPON_CLASSNAME_LENGTH 24
#define MAX_WEAPON_NAME_LENGTH		48
#define MAX_WEAPON_PREFIX_LENGTH		6
#define MAX_WEAPONS 						48

#define Karyuu_HITGROUP_GENERIC    			0
#define Karyuu_HITGROUP_HEAD        		1
#define Karyuu_HITGROUP_CHEST        		2
#define Karyuu_HITGROUP_STOMACH    			3
#define Karyuu_HITGROUP_LEFTARM    			4
#define Karyuu_HITGROUP_RIGHTARM    		5
#define Karyuu_HITGROUP_LEFTLEG    			6
#define Karyuu_HITGROUP_RIGHTLEG    		7
#define Karyuu_HITGROUP_GEAR        		10

#define Karyuu_HEGrenadeOffset         	14
#define Karyuu_FlashbangOffset         	15
#define Karyuu_SmokegrenadeOffset        	16
#define Karyuu_IncGrenadesOffset        	17
#define Karyuu_DecoyGrenadeOffset        	18
#define Karyuu_HealthShotOffset 				21

char gKaryuu_WeaponClasses[][] = {
	/* 0*/ "weapon_awp", /* 1*/ "weapon_ak47", /* 2*/ "weapon_m4a1", /* 3*/ "weapon_m4a1_silencer", /* 4*/ "weapon_deagle", /* 5*/ "weapon_usp_silencer", /* 6*/ "weapon_hkp2000", /* 7*/ "weapon_glock", /* 8*/ "weapon_elite",
	/* 9*/ "weapon_p250", /*10*/ "weapon_cz75a", /*11*/ "weapon_fiveseven", /*12*/ "weapon_tec9", /*13*/ "weapon_revolver", /*14*/ "weapon_nova", /*15*/ "weapon_xm1014", /*16*/ "weapon_mag7", /*17*/ "weapon_sawedoff",
	/*18*/ "weapon_m249", /*19*/ "weapon_negev", /*20*/ "weapon_mp9", /*21*/ "weapon_mac10", /*22*/ "weapon_mp7", /*23*/ "weapon_ump45", /*24*/ "weapon_p90", /*25*/ "weapon_bizon", /*26*/ "weapon_famas", /*27*/ "weapon_galilar",
	/*28*/ "weapon_ssg08", /*29*/ "weapon_aug", /*30*/ "weapon_sg556", /*31*/ "weapon_scar20", /*32*/ "weapon_g3sg1", /*33*/ "weapon_knife_karambit", /*34*/ "weapon_knife_m9_bayonet", /*35*/ "weapon_bayonet",
	/*36*/ "weapon_knife_survival_bowie", /*37*/ "weapon_knife_butterfly", /*38*/ "weapon_knife_flip", /*39*/ "weapon_knife_push", /*40*/ "weapon_knife_tactical", /*41*/ "weapon_knife_falchion", /*42*/ "weapon_knife_gut",
	/*43*/ "weapon_knife_ursus", /*44*/ "weapon_knife_gypsy_jackknife", /*45*/ "weapon_knife_stiletto", /*46*/ "weapon_knife_widowmaker", /*47*/ "weapon_mp5sd", /*48*/ "weapon_knife_css", /*49*/ "weapon_knife_cord",
	/*50*/ "weapon_knife_canis", /*51*/ "weapon_knife_outdoor", /*52*/ "weapon_knife_skeleton", /*53*/ "weapon_knife", /*54*/ "weapon_knife_t", /*55*/ "weapon_knife"
};

int gKaryuu_iWeaponDefIndex[] = {
	/* 0*/ 9, /* 1*/ 7, /* 2*/ 16, /* 3*/ 60, /* 4*/ 1, /* 5*/ 61, /* 6*/ 32, /* 7*/ 4, /* 8*/ 2,
	/* 9*/ 36, /*10*/ 63, /*11*/ 3, /*12*/ 30, /*13*/ 64, /*14*/ 35, /*15*/ 25, /*16*/ 27, /*17*/ 29,
	/*18*/ 14, /*19*/ 28, /*20*/ 34, /*21*/ 17, /*22*/ 33, /*23*/ 24, /*24*/ 19, /*25*/ 26, /*26*/ 10, /*27*/ 13,
	/*28*/ 40, /*29*/ 8, /*30*/ 39, /*31*/ 38, /*32*/ 11, /*33*/ 507, /*34*/ 508, /*35*/ 500,
	/*36*/ 514, /*37*/ 515, /*38*/ 505, /*39*/ 516, /*40*/ 509, /*41*/ 512, /*42*/ 506,
	/*43*/ 519, /*44*/ 520, /*45*/ 522, /*46*/ 523, /*47*/ 23, /*48*/ 503, /*49*/ 517,
	/*50*/ 518, /*51*/ 521, /*52*/ 525, /*53*/ 41, /*54*/ 59, /*55*/ 42
};

int gKaryuu_iKnifeIndices[] = {
	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 48, 49, 50, 51, 52, 53, 54, 55
};

int gKaryuu_iGloveIndices[] = {
	5027, 5030, 5031, 5032, 5033, 5034, 5035, 4725
};

/*
 * ===  REGION  ======================================================================
 *           Name:  Validation Functions
 *    Description:  Functions that validate a given parameter
 * ===================================================================================
 */

stock bool Karyuu_IsValidWeapon(int iWeapon)
{
	char sClassName[MAX_WEAPON_CLASSNAME_LENGTH];
	Karyuu_GetClassnameByWeapon(iWeapon, STRING(sClassName));
	return Karyuu_StartsWith(sClassName, "weapon_");
}

stock bool Karyuu_IsValidWeaponSafe(int iWeapon)
{
	if (iWeapon == INVALID_ENT_REFERENCE)
		return false;

	if (iWeapon > 4096)
		iWeapon = EntRefToEntIndex(iWeapon);

	if (!IsValidEdict(iWeapon) || !Karyuu_IsValidEntity(iWeapon))
	{
		return false;
	}

	return Karyuu_IsValidWeapon(iWeapon);
}

stock int Karyuu_GetWeaponNumByDefId(int iDefId)
{
	int iSize = sizeof(gKaryuu_iWeaponDefIndex);
	for (int i = 0; i < iSize; i++)
	{
		if (gKaryuu_iWeaponDefIndex[i] == iDefId)
		{
			return i;
		}
	}
	return INVALID_ENT_REFERENCE;
}

stock bool Karyuu_IsValidWeaponDefIndex(int iIndex)
{
	int iSize = sizeof(gKaryuu_iWeaponDefIndex);
	for (int iWeapon = 0; iWeapon < iSize; iWeapon++)
	{
		if (gKaryuu_iWeaponDefIndex[iWeapon] == iIndex)
			return true;
	}
	return false;
}

stock bool Karyuu_IsGloveDefIndex(int iIndex)
{
	int iSize = sizeof(gKaryuu_iGloveIndices);
	for (int iGlove = 0; iGlove < iSize; iGlove++)
	{
		if (gKaryuu_iGloveIndices[iGlove] == iIndex)
			return true;
	}
	return false;
}

stock bool Karyuu_IsKnifeDefIndex(int iDefIndex)
{
	int iSize = sizeof(gKaryuu_iKnifeIndices);
	for (int i = 0; i < iSize; i++)
	{
		if (gKaryuu_iWeaponDefIndex[gKaryuu_iKnifeIndices[i]] == iDefIndex)
			return true;
	}
	return false;
}

stock bool Karyuu_IsKnifeClassName(const char[] sClassName)
{
	return (Karyuu_StrContains(sClassName, "knife") && !Karyuu_StrEquals(sClassName, "weapon_knifegg")) || Karyuu_StrContains(sClassName, "bayonet");
}

stock bool Karyuu_IsKnifeClassNameEx(int iWeapon)
{
	char sClassName[MAX_WEAPON_CLASSNAME_LENGTH];
	Karyuu_GetClassnameByWeapon(iWeapon, STRING(sClassName));
	return (Karyuu_StrContains(sClassName, "knife") && !Karyuu_StrEquals(sClassName, "weapon_knifegg")) || Karyuu_StrContains(sClassName, "bayonet");
}

stock bool Karyuu_IsWeaponKnife(int iWeapon, bool bDefault = false)
{
	return Karyuu_IsKnifeDefIndex(Karyuu_GetWeaponDefIndex(iWeapon)) || (bDefault && Karyuu_IsKnifeClassNameEx(iWeapon));
}

stock int Karyuu_GetPrimaryAmmoType(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_iPrimaryAmmoType");
}

stock void Karyuu_SetPrimaryAmmoType(int iWeapon, int iType)
{
	SetEntProp(iWeapon, Prop_Data, "m_iPrimaryAmmoType", iType);
}

stock int Karyuu_GetSecondaryAmmoType(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_iSecondaryAmmoType");
}

stock void Karyuu_SetSecondaryAmmoType(int iWeapon, int iType)
{
	SetEntProp(iWeapon, Prop_Data, "m_iSecondaryAmmoType", iType);
}

stock int Karyuu_GetPrimaryClip(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_iClip1");
}

stock void Karyuu_SetPrimaryClip(int iWeapon, int iValue)
{
	SetEntProp(iWeapon, Prop_Data, "m_iClip1", iValue);
}

stock int Karyuu_GetSecondaryClip(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_iClip2");
}

stock void Karyuu_SetSecondaryClip(int iWeapon, int iValue)
{
	SetEntProp(iWeapon, Prop_Data, "m_iClip2", iValue);
}

stock void Karyuu_SetClips(int iWeapon, int iPrimary, int iSecondary)
{
	Karyuu_SetPrimaryClip(iWeapon, iPrimary);
	Karyuu_SetSecondaryClip(iWeapon, iSecondary);
}

stock int Karyuu_GetPrimaryAmmoCount(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_iPrimaryAmmoCount");
}

stock void Karyuu_SetPrimaryAmmoCount(int iWeapon, int iValue)
{
	SetEntProp(iWeapon, Prop_Data, "m_iPrimaryAmmoCount", iValue);
}

stock int Karyuu_GetSecondaryAmmoCount(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_iSecondaryAmmoCount");
}

stock void Karyuu_SetSecondaryAmmoCount(int iWeapon, int iValue)
{
	SetEntProp(iWeapon, Prop_Data, "m_iSecondaryAmmoCount", iValue);
}

stock void Karyuu_SetAmmoCounts(int iWeapon, int iPrimary, int iSecondary)
{
	Karyuu_SetPrimaryAmmoCount(iWeapon, iPrimary);
	Karyuu_SetSecondaryAmmoCount(iWeapon, iSecondary);
}

stock int Karyuu_GetViewModelIndex(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Data, "m_nViewModelIndex");
}

stock void Karyuu_SetViewModelIndex(int iWeapon, int iIndex)
{
	SetEntProp(iWeapon, Prop_Data, "m_nViewModelIndex", iIndex);
	ChangeEdictState(iWeapon, FindDataMapInfo(iWeapon, "m_nViewModelIndex"));
}

stock bool Karyuu_IsWeaponReloading(int iWeapon)
{
	return view_as<bool>(GetEntProp(iWeapon, Prop_Data, "m_bInReload"));
}

stock void Karyuu_SetShootingSound(int iEntity, const char[] sSound)
{
	SetEntPropString(iEntity, Prop_Data, "m_iszShootSound", sSound);
}

stock int Karyuu_GetClientActiveSlot(int iClient)
{
	if (!Karyuu_IsClientIndex(iClient) || !IsClientInGame(iClient) || !IsPlayerAlive(iClient))
		return INVALID_ENT_REFERENCE;

	int iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");

	if (Karyuu_IsValidEntity(iWeapon))
		return INVALID_ENT_REFERENCE;

	for (int iSlot = 0; iSlot < 5; iSlot++)
	{
		if (GetPlayerWeaponSlot(iClient, iSlot) != iWeapon)
			continue;

		return iSlot;
	}
	return INVALID_ENT_REFERENCE;
}

stock bool Karyuu_ClientHasGun(int iClient)
{
	return Karyuu_PlayerHasPrimary(iClient) || Karyuu_PlayerHasSecondary(iClient);
}

stock bool Karyuu_PlayerHasPrimary(int iClient)
{
	return GetPlayerWeaponSlot(iClient, CS_SLOT_PRIMARY) != -1;
}

stock bool Karyuu_PlayerHasSecondary(int iClient)
{
	return GetPlayerWeaponSlot(iClient, CS_SLOT_SECONDARY) != -1;
}

stock bool Karyuu_HasWeapon(int iClient, const char[] sClassName)
{
	return Karyuu_GetClientWeapon(iClient, sClassName) != INVALID_ENT_REFERENCE;
}

stock int Karyuu_GetWeaponSlot(int iClient, int iWeapon)
{
	if (!Karyuu_IsClientIndex(iClient) || !IsClientInGame(iClient) || !IsPlayerAlive(iClient) || !Karyuu_IsValidEntity(iWeapon))
		return INVALID_ENT_REFERENCE;

	for (int iSlot = 0; iSlot < 5; iSlot++)
	{
		if (GetPlayerWeaponSlot(iClient, iSlot) != iWeapon)
			continue;

		return iSlot;
	}
	return INVALID_ENT_REFERENCE;
}

stock int Karyuu_GetClientGrenades(int iClient)
{
	return GetEntProp(iClient, Prop_Send, "m_iAmmo", _, Karyuu_DecoyGrenadeOffset)
		  + GetEntProp(iClient, Prop_Send, "m_iAmmo", _, Karyuu_SmokegrenadeOffset)
		  + GetEntProp(iClient, Prop_Send, "m_iAmmo", _, Karyuu_FlashbangOffset)
		  + GetEntProp(iClient, Prop_Send, "m_iAmmo", _, Karyuu_IncGrenadesOffset)
		  + GetEntProp(iClient, Prop_Send, "m_iAmmo", _, Karyuu_HEGrenadeOffset);
}

stock int Karyuu_GetClientHealtshots(int iClient)
{
   return GetEntProp(iClient, Prop_Send, "m_iAmmo", _, Karyuu_HealthShotOffset);
}

stock int Karyuu_GetClientWeapon(int iClient, const char[] cSearchClassName)
{
	char cClassName[MAX_WEAPON_STRING];
	int	 iWeapon, iSize = GetEntPropArraySize(iClient, Prop_Send, "m_hMyWeapons");

	for (int i = 0; i < iSize; i++)
	{
		iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hMyWeapons", i);

		if (!IsValidEdict(iWeapon))
			continue;

		Karyuu_GetClassName(iWeapon, STRING(cClassName));

		if (Karyuu_StrEquals(cClassName, cSearchClassName))
			return iWeapon;
	}
	return INVALID_ENT_REFERENCE;
}

stock int Karyuu_GetClassnameByWeapon(int iWeapon, char[] sClassName, int iLength)
{
	return Karyuu_GetClassnameByDefIndex(Karyuu_GetWeaponDefIndex(iWeapon), sClassName, iLength);
}

stock bool Karyuu_GetClassnameByDefIndex(int iDefIndex, char[] sClassName, int iLength)
{
	int iSize = sizeof(gKaryuu_iWeaponDefIndex);
	for (int iWeapon = 0; iWeapon < iSize; iWeapon++)
	{
		if (gKaryuu_iWeaponDefIndex[iWeapon] == iDefIndex)
		{
			strcopy(sClassName, iLength, gKaryuu_WeaponClasses[iWeapon]);
			return true;
		}
	}
	return false;
}

stock int Karyuu_GetWeaponDefIndexByClassName(char[] sClassName)
{
	int iSize = sizeof(gKaryuu_WeaponClasses);
	for (int i = 0; i < iSize; i++)
	{
		if (Karyuu_StrEquals(sClassName, gKaryuu_WeaponClasses[i]))
			return gKaryuu_iWeaponDefIndex[i];
	}
	return -1;
}

stock void Karyuu_RemoveWeaponPrefix(const char[] sSource, int iSize)
{
	Karyuu_RemoveFrontString(sSource, iSize, sSource[7]);
}

stock int Karyuu_GetWeaponPreviousOwner(int iWeapon, bool bCheck = true)
{
	return (!bCheck || IsValidEdict(iWeapon)) ? GetEntPropEnt(iWeapon, Prop_Send, "m_hPrevOwner") : INVALID_ENT_REFERENCE;
}

stock int Karyuu_GetWeaponOwner(int iWeapon, bool bCheck = true)
{
	return (!bCheck || IsValidEdict(iWeapon)) ? GetEntPropEnt(iWeapon, Prop_Data, "m_hOwnerEntity") : INVALID_ENT_REFERENCE;
}

stock void Karyuu_SetWeaponOwner(int iWeapon, int iEntity, bool bCheck = true)
{
	if (!bCheck || IsValidEdict(iWeapon))
		SetEntPropEnt(iWeapon, Prop_Data, "m_hOwner", iEntity);
}

stock int Karyuu_GetWeaponDefIndex(int iWeapon)
{
	return GetEntProp(iWeapon, Prop_Send, "m_iItemDefinitionIndex");
}

stock int Karyuu_GetActiveWeapon(int iClient)
{
	if (!Karyuu_IsValidClient(iClient) || !IsPlayerAlive(iClient) || !HasEntProp(iClient, Prop_Send, "m_hActiveWeapon"))
		return INVALID_ENT_REFERENCE;

	int iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
	return Karyuu_IsValidEntity(iWeapon) ? iWeapon : INVALID_ENT_REFERENCE;
}

/*
 * ===  REGION  ======================================================================
 *           Name:  Action Functions
 *    Description:  Functions that runs an actual action on an entity
 * ===================================================================================
 */

stock bool Karyuu_RemoveWeapon(int iClient, int iWeapon)
{
	if (!Karyuu_IsValidClient(iClient))
		return false;

	if (Karyuu_GetWeaponDefIndex(iWeapon) == -1)
		return false;

	if (!RemovePlayerItem(iClient, iWeapon))
	{
		if (!Karyuu_DropWeapon(iClient, iWeapon))
			return false;
	}

	AcceptEntityInput(iWeapon, "Kill");
	return true;
}

stock void Karyuu_StripClientWeapons(int iClient)
{
	if (!Karyuu_IsValidClient(iClient))
		return;

	int iWeapon;
	while ((iWeapon = Karyuu_GetActiveWeapon(iClient)) != INVALID_ENT_REFERENCE)
	{
		Karyuu_RemoveWeapon(iClient, iWeapon);
	}
}

stock void Karyuu_StripAllClientWeapons()
{
	for (int iClient = 0; iClient <= MAXPLAYERS + 1; iClient++)
	{
		Karyuu_StripClientWeapons(iClient);
	}
}

stock bool Karyuu_ChangeWeapon(int iClient, const char[] cClassName)
{
	int iWeapon = Karyuu_GetClientWeapon(iClient, cClassName);

	if (iWeapon == INVALID_ENT_REFERENCE)
		return false;

	Karyuu_SetActiveWeapon(iClient, iWeapon);
	return true;
}

stock void Karyuu_SetClientActiveWeapon(int iClient, int iWeapon)
{
	SetEntPropEnt(iClient, Prop_Data, "m_hActiveWeapon", iWeapon);
	ChangeEdictState(iClient, FindDataMapInfo(iClient, "m_hActiveWeapon"));
}

stock bool Karyuu_DropWeapon(int iClient, int iWeapon)
{
	if (!Karyuu_IsValidClient(iClient))
		return false;

	if (Karyuu_GetWeaponDefIndex(iWeapon) == -1)
		return false;

	int iHudFlags	 = GetEntProp(iClient, Prop_Send, "m_iHideHUD");
	int iOwnerEntity = GetEntPropEnt(iWeapon, Prop_Send, "m_hOwnerEntity");

	if (iOwnerEntity != iClient)
	{
		SetEntPropEnt(iWeapon, Prop_Send, "m_hOwnerEntity", iClient);
	}

	if (iWeapon == Karyuu_GetActiveWeapon(iClient))
	{
		SetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon", -1);
	}

	CS_DropWeapon(iClient, iWeapon, false, true);

	if (iOwnerEntity != iClient)
	{
		SetEntPropEnt(iWeapon, Prop_Send, "m_hOwnerEntity", iOwnerEntity);
	}

	SetEntProp(iClient, Prop_Send, "m_iHideHUD", iHudFlags);
	return true;
}