#if defined _KARYUU_FILESYSTEM_INCLUDED_
	#endinput
#endif
#define _KARYUU_FILESYSTEM_INCLUDED_

stock bool Karyuu_DeleteFileIfExists(const char[] sPath)
{
	return FileExists(sPath) && DeleteFile(sPath);
}

stock bool Karyuu_DirExistsEx(const char sPath[PLATFORM_MAX_PATH])
{
	if (Karyuu_CreateDirectory(sPath))
		return true;

	LogError("Unable to create a folder at \"%s\"", sPath);
	return false;
}

stock bool Karyuu_CreateFile(const char[] sBuffer)
{
	if (strlen(sBuffer) == 0)
		return false;

	char sPath[PLATFORM_MAX_PATH];
	BuildPath(Path_SM, STRING(sPath), sBuffer);

	if (!FileExists(sPath))
	{
		File fFile = OpenFile(sPath, "w");
		if (fFile == INVALID_HANDLE)
			SetFailState("Permission problems when creating file \"%s\"", sPath);

		delete fFile;
	}

	return true;
}

stock bool Karyuu_CreateDirectory(const char[] szPath, int iMode = 511)
{
	return !DirExists(szPath) && CreateDirectory(szPath, iMode);
}

stock bool Karyuu_AddFileToDownloadsTableEx(const char[] sFormat, any ...)
{
	if (strlen(sFormat) == 0)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	VFormat(STRING(sBuffer), sFormat, 2);

	AddFileToDownloadsTable(sBuffer);
	return true;
}

stock bool Karyuu_MoveFile(char[] szFile, char[] szPath)
{
	char szFileName[PLATFORM_MAX_PATH], szTargetPath[PLATFORM_MAX_PATH];
	if (Karyuu_GetFileName(szFile, STRING(szFileName)))
	{
		FormatEx(STRING(szTargetPath), "%s%s", szPath, szFileName);
		return Karyuu_MoveFileEx(szTargetPath, szFile);
	}
	else
		return false;
}

stock bool Karyuu_MoveFileEx(char[] szFile, char[] szPath)
{
	return RenameFile(szPath, szFile, true, "csgo");
}

stock int Karyuu_PrepareModel(char sModel[PLATFORM_MAX_PATH], bool bPreLoad = false)
{
	if (strlen(sModel) == 0)
		return INVALID_ENT_REFERENCE;

	if (StrContains(sModel, "models/") != 0)
		Format(STRING(sModel), "models/%s", sModel);

	return Karyuu_PreCacheModel(sModel, bPreLoad);
}

stock bool Karyuu_PrepareSound(const char[] sFile, bool bDownload = true)
{
	if (strlen(sFile) == 0)
		return false;

	char sSound[PLATFORM_MAX_PATH];
	strcopy(STRING(sSound), sFile);

	if (!Karyuu_StrContains(sSound, "sound/"))
		Format(STRING(sSound), "sounds/%s", sSound);

	if (bDownload)
		AddFileToDownloadsTable(sSound);

	PrecacheSound(sSound);

	Karyuu_RemoveFrontString(STRING(sSound), 6);

	return Karyuu_FakePrecacheSound(sSound);
}

stock bool Karyuu_FakePrecacheSound(const char[] sSound)
{
	char sPath[PLATFORM_MAX_PATH];
	FormatEx(STRING(sPath), "sound/%s", sSound);

	if (!FileExists(sPath))
		return false;

	AddFileToDownloadsTable(sPath);

	FormatEx(STRING(sPath), "*/%s", sSound);
	AddToStringTable(FindStringTable("soundprecache"), sPath);
	return true;
}

stock int Karyuu_PreCacheModel(char[] sModel, bool bPreLoad = true)
{
	return IsModelPrecached(sModel) ? INVALID_ENT_REFERENCE : PrecacheModel(sModel, bPreLoad);
}

stock bool Karyuu_GetFileName(const char[] szPath, char[] szFileName, int iSize)
{
	int iLastPlace = -1;
	int iLength = strlen(szPath) -1;
	for (int i = 0; i < iLength; i++)
		if (szPath[i] == '\\' || szPath[i] == '/')
			iLastPlace = i;

	if (iLastPlace == -1)
		return false;

	strcopy(szFileName, iSize, szPath[iLastPlace]);
	szFileName[iLength] = 0;
	return true;
}