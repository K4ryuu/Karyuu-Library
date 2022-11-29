/***
 *    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
 *    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
 *    █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
 *    ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
 *    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
 *    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
 */

#if defined _KARYUU_FUNCTONS_INCLUDED_
	#endinput
#endif
#define _KARYUU_FUNCTONS_INCLUDED_

stock void Karyuu_SelfReload(Handle hPlugin = INVALID_HANDLE)
{
	char szFileName[64];
	GetPluginFilename(hPlugin, STRING(szFileName));
	ServerCommand("sm plugins reload %s", szFileName);
}

stock void Karyuu_SelfUnload(Handle hPlugin = INVALID_HANDLE)
{
	char szFileName[64];
	GetPluginFilename(hPlugin, STRING(szFileName));
	ServerCommand("sm plugins unload %s", szFileName);
}

stock void Karyuu_ReloadTranslations()
{
	ServerCommand("sm_reload_translations");
}

stock bool Karyuu_SetModel(int iEntity, char sModel[PLATFORM_MAX_PATH], bool bPreLoad = false)
{
	if (iEntity <= 0)
		return false;

	if (Karyuu_PrepareModel(sModel, bPreLoad) != 0)
	{
		if (strlen(sModel) > 0 && IsModelPrecached(sModel))
		{
			SetEntityModel(iEntity, sModel);
			return true;
		}
	}
	return false;
}