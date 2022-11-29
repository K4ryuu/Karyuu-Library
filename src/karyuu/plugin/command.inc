/***
 *     ██████╗ ██████╗ ███╗   ███╗███╗   ███╗ █████╗ ███╗   ██╗██████╗ ███████╗
 *    ██╔════╝██╔═══██╗████╗ ████║████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝
 *    ██║     ██║   ██║██╔████╔██║██╔████╔██║███████║██╔██╗ ██║██║  ██║███████╗
 *    ██║     ██║   ██║██║╚██╔╝██║██║╚██╔╝██║██╔══██║██║╚██╗██║██║  ██║╚════██║
 *    ╚██████╗╚██████╔╝██║ ╚═╝ ██║██║ ╚═╝ ██║██║  ██║██║ ╚████║██████╔╝███████║
 *     ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝ ╚══════╝
 */

#if defined _KARYUU_COMMANDS_INCLUDED_
	#endinput
#endif
#define _KARYUU_COMMANDS_INCLUDED_

stock void Karyuu_RegCommand(char[] cCommand, ConCmd ccCallBack, char[] cDescription = "", int iFlag = -1, bool bIgnoreExistance = false)
{
	// - Check the given iFlag wether it's an admin command or not
	if (!bIgnoreExistance && Karyuu_IsCommandExists(cCommand))
		return;

	if (iFlag == -1)
	{
		RegConsoleCmd(cCommand, ccCallBack, cDescription);
	}
	else
		RegAdminCmd(cCommand, ccCallBack, iFlag, cDescription);
}

stock int Karyuu_RegMultipleCommand(char[] cCommand, ConCmd ccCallBack, char[] cDescription = "", int iFlag = 0)
{
	int iRegistered = 0;
	if (Karyuu_StrContains(cCommand, ";"))
	{
		char gShadow_AliasList[32][32];
		int	 iAliasCount = ExplodeString(cCommand, ";", STRING(gShadow_AliasList), sizeof(gShadow_AliasList[]));
		for (int i = 0; i < iAliasCount; i++)
		{
			Karyuu_RegCommand(gShadow_AliasList[i], ccCallBack, cDescription, iFlag);
			iRegistered++;
		}
	}
	else
	{
		Karyuu_RegCommand(cCommand, ccCallBack, cDescription, iFlag);
		iRegistered++;
	}

	return iRegistered;
}

stock bool Karyuu_RegCommandEx(char[] cCommand, ConCmd ccCallBack, char[] cDescription = "", int iFlag = 0)
{
	/*** Check the given iFlag wether it's an admin command or not ***/
	if (Karyuu_IsCommandExists(cCommand))
		return false;

	Karyuu_RegCommand(cCommand, ccCallBack, cDescription, iFlag);
	return true;
}

stock void Karyuu_GetCommandName(char[] sBuffer, int iSize)
{
	GetCmdArg(0, sBuffer, iSize);
}

stock int Karyuu_GetCmdArgInt(int iArgNum)
{
	char sBuffer[64];
	GetCmdArg(iArgNum, STRING(sBuffer));
	return StringToInt(sBuffer);
}

stock float Karyuu_GetCmdArgFloat(int iArgNum)
{
	char sBuffer[64];
	GetCmdArg(iArgNum, STRING(sBuffer));
	return StringToFloat(sBuffer);
}

stock bool Karyuu_GetCmdArgBool(int iArgNum)
{
	char sBuffer[64];
	GetCmdArg(iArgNum, STRING(sBuffer));
	return view_as<bool>(StringToInt(sBuffer));
}

stock int Karyuu_GetCmdArgTarget(int iClient, int iArgNum, bool bNoBots = false, bool bImmunity = true)
{
	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(iArgNum, STRING(sTarget));
	return FindTarget(iClient, sTarget, bNoBots, bImmunity);
}

stock bool Karyuu_IsCommandExists(const char[] cCommand)
{
	return GetCommandFlags(cCommand) != INVALID_FCVAR_FLAGS;
}
