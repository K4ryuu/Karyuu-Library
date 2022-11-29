#if defined _KARYUU_MODULE_HANDLE_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_HANDLE_INCLUDED_

stock bool Karyuu_IsValidHandle(Handle &hEntity)
{
	return hEntity != null && hEntity != INVALID_HANDLE;
}

stock bool Karyuu_IsValidStringMap(StringMap &hEntity)
{
	return hEntity != null && hEntity != INVALID_HANDLE;
}

stock bool Karyuu_IsValidArrayList(ArrayList &hEntity)
{
	return hEntity != null && hEntity != INVALID_HANDLE;
}

stock void Karyuu_DeleteStringMap(StringMap &smStringMap)
{
	if (Karyuu_IsValidStringMap(smStringMap))
	{
		smStringMap.Clear();
		delete smStringMap;
	}
}

stock void Karyuu_DeleteArrayList(ArrayList &alArrayList)
{
	if (Karyuu_IsValidArrayList(alArrayList))
	{
		alArrayList.Clear();
		delete alArrayList;
	}
}

stock void Karyuu_DeleteStack(ArrayStack &asArrayStack)
{
	if (Karyuu_IsValidHandle(asArrayStack))
	{
		while (!asArrayStack.Empty)
			asArrayStack.Pop();
	}
}

stock void Karyuu_ClearTrieSafe(StringMap &smStringMap)
{
	int iSize;
	StringMapSnapshot smSnapshot = smStringMap.Snapshot();

	for (int iData = 0; iData < smSnapshot.Length; iData++)
	{
		iSize = smSnapshot.KeyBufferSize(iData);

		char[] sBuffer = new char[iSize];
		smSnapshot.GetKey(iData, sBuffer, iSize);

		Handle hLocal;
		smStringMap.GetValue(sBuffer, hLocal);

		delete hLocal;

		smStringMap.Remove(sBuffer);
	}

	smStringMap.Clear();
	delete smSnapshot;
}

stock bool Karyuu_KillTimerSafe(Handle &hTimer)
{
	if (hTimer == null)
		return false;

	KillTimer(hTimer);
	hTimer = null;
	return true;
}