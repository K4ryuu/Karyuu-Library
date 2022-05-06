/***
 *     █████╗ ███╗   ██╗████████╗██╗ ██████╗██╗  ██╗███████╗ █████╗ ████████╗
 *    ██╔══██╗████╗  ██║╚══██╔══╝██║██╔════╝██║  ██║██╔════╝██╔══██╗╚══██╔══╝
 *    ███████║██╔██╗ ██║   ██║   ██║██║     ███████║█████╗  ███████║   ██║
 *    ██╔══██║██║╚██╗██║   ██║   ██║██║     ██╔══██║██╔══╝  ██╔══██║   ██║
 *    ██║  ██║██║ ╚████║   ██║   ██║╚██████╗██║  ██║███████╗██║  ██║   ██║
 *    ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝
 */

#if defined _yugen_anticheat_included_
	#endinput
#endif
#define _yugen_anticheat_included_

#define CHECK_SKY_CHANGER_ENABLED

/***
 *     ██████╗ ██████╗ ██████╗ ███████╗███████╗
 *    ██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔════╝
 *    ██║     ██║   ██║██║  ██║█████╗  ███████╗
 *    ██║     ██║   ██║██║  ██║██╔══╝  ╚════██║
 *    ╚██████╗╚██████╔╝██████╔╝███████╗███████║
 *     ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝
 */

// TODO Continue
#if defined CHECK_SKY_CHANGER_ENABLED
	#define CHECK_SKY_INTERVAL 30.0
	#define CHECK_SKY_DELAY	   GetRandomFloat(8.0, 16.0)

public Action Timer_DoSkyCheck(Handle hTimer)	  // Check All The Players Against "sv_skyname" ConVar
{
	for (int iClient = 1; iClient <= MaxClients; iClient++)	   // Loop Through All The Players
	{
		if (Karyuu_IsValidPlayer(iClient))	 // The Player Is On The Game Server
		{
			int nTeam = GetClientTeam(iClient);	   // Retrieve The Player's Team

			if (nTeam == CS_TEAM_T || nTeam == CS_TEAM_CT)	  // The Player Is Actually Playing
			{
				QueryClientConVar(iClient, "sv_skyname", Res_FinishedCheckingSkyName);	  // Retrieve The Player's "sv_skyname" ConVar's String Value
			}
		}
	}
}
#endif
