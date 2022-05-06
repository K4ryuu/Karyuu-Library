#if defined _KARYUU_MODULE_ENTITY_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_ENTITY_INCLUDED_

#define MAX_ENTITY_LIMIT 4096 + 1

stock bool Karyuu_IsValidEntity(int iEntity)
{
	if (!iEntity || iEntity < MaxClients || iEntity > MAX_ENTITY_LIMIT)
		return false;

	return IsValidEntity(iEntity);
}

stock bool Karyuu_IsEntityWorld(int iEntity)
{
	return iEntity == 0;
}

stock bool Karyuu_IsValidEntityRef(int iReference)
{
	return Karyuu_IsValidEntity(EntRefToEntIndex(iReference));
}

stock bool Karyuu_GetAbsOrigin(int iEntity, float fVec[3], bool bValidate = false)
{
	if (!bValidate || (IsValidEdict(iEntity) && HasEntProp(iEntity, Prop_Send, "m_vecOrigin")))
	{
		GetEntPropVector(iEntity, Prop_Send, "m_vecOrigin", fVec);
		return true;
	}
	return false;
}

stock int Karyuu_GetClassName(int iEntity, char[] cBuffer, int iSize)
{
	return GetEntPropString(iEntity, Prop_Data, "m_iClassname", cBuffer, iSize);
}

stock bool Karyuu_SetClassName(int iEntity, const char[] cClassName)
{
	return DispatchKeyValue(iEntity, "classname", cClassName);
}

stock bool Karyuu_ClassNameMatches(int iEntity, const char[] cClassName, bool bPartialMatch = false)
{
	char cEntityClassName[64];
	Karyuu_GetClassName(iEntity, STRING(cEntityClassName));

	if (bPartialMatch)
	{
		return Karyuu_StrContains(cEntityClassName, cClassName);
	}

	return Karyuu_StrEquals(cEntityClassName, cClassName);
}

stock float Karyuu_GetDistanceOrigin(int entity, const float vec[3])
{
	float entityVec[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", entityVec);

	return GetVectorDistance(entityVec, vec);
}

stock int Karyuu_GetClosestToEntity(int iEntity, bool bOnlyClients = false)
{
	float fOrigin[3];
	return Karyuu_GetAbsOrigin(iEntity, fOrigin) ? Karyuu_GetClosest(fOrigin, bOnlyClients) : INVALID_ENT_REFERENCE;
}

stock int Karyuu_GetClosest(float fOriginVec[3], bool bOnlyClients = false)
{
	float fTempVec[3], fSmallestDistance = 0.0, fTempDistance;
	float;
	int iClosest	 = INVALID_ENT_REFERENCE;

	int iMaxEntities = bOnlyClients ? MaxClients : GetMaxEntities();

	for (int iEdict = 1; iEdict <= iMaxEntities; iEdict++)
	{
		if (Karyuu_GetAbsOrigin(iEdict, fTempVec))
		{
			fTempDistance = GetVectorDistance(fOriginVec, fTempVec, true);

			if (fTempDistance < fSmallestDistance || fSmallestDistance == 0.0)
			{
				fSmallestDistance = fTempDistance;
				iClosest		  = iEdict;
			}
		}
	}

	return iClosest;
}

stock void Karyuu_SetEntitySelfDestruct(int iEntity, float fDuration)
{
	char sOutput[64];
	FormatEx(STRING(sOutput), "OnUser1 !self:kill::%.1f:1", fDuration);
	SetVariantString(sOutput);
	AcceptEntityInput(iEntity, "AddOutput");
	AcceptEntityInput(iEntity, "FireUser1");
}