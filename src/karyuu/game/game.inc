#if defined _KARYUU_GAME_INCLUDED_
	#endinput
#endif
#define _KARYUU_GAME_INCLUDED_

/* clang-format off */
#include <sdktools_gamerules>
#include <cstrike>
#include <console>
/* clang-format on */

stock void IdentifyGame()
{
	char m_szGameDir[64];
	GetGameFolderName(STRING(m_szGameDir));
}

/*
 * ===  REGION  ======================================================================
 *         Name:  GamePhase
 *  Description:  Functions connected to the game phase
 * ===================================================================================
 */

enum GamePhase
{
	GamePhase_FirstHalf	 = 2,
	GamePhase_SecondHalf = 3,
	GamePhase_HalfTime	 = 4,
	GamePhase_PostGame	 = 5,
};

stock void Karyuu_EnsurePausedWarmup()
{
	if (!Karyuu_IsWarmupPeriod())
		Karyuu_StartWarmup();

	ServerCommand("mp_warmup_pausetimer 1");
	ServerCommand("mp_do_warmup_period 1");
	ServerCommand("mp_warmup_pausetimer 1");
}

stock void Karyuu_StartWarmup(bool bIndefiniteWarmup = true, int iWarmupTime = 60)
{
	ServerCommand("mp_do_warmup_period 1");
	ServerCommand("mp_warmuptime %d", iWarmupTime);
	ServerCommand("mp_warmup_start");

	/* Note: For some reason it needs to get sent twice. Ask Valve. */
	if (bIndefiniteWarmup)
	{
		ServerCommand("mp_warmup_pausetimer 1");
		ServerCommand("mp_warmup_pausetimer 1");
	}
}

stock void Karyuu_EndWarmup(int iTime = 0)
{
	if (iTime > 0)
	{
		ServerCommand("mp_warmup_pausetimer 0");
		ServerCommand("mp_warmuptime %d", iTime);
	}
	else
		ServerCommand("mp_warmup_end");
}

stock bool Karyuu_IsMatchPaused()
{
	return Karyuu_GetPropBool("m_bMatchWaitingForResume");
}

stock void Karyuu_PauseMatch(int iTime = 0, int iTeam = CS_TEAM_NONE)
{
	if (iTime > 0 || iTeam >= CS_TEAM_T)
	{
		ServerCommand("mp_pause_match");

		if (iTeam == CS_TEAM_T)
		{
			GameRules_SetProp("m_bTerroristTimeOutActive", true);
			GameRules_SetPropFloat("m_flTerroristTimeOutRemaining", float(iTime));
		}
		else
		{
			GameRules_SetProp("m_bCTTimeOutActive", true);
			GameRules_SetPropFloat("m_flCTTimeOutRemaining", float(iTime));
		}
	}
	else
		ServerCommand("mp_pause_match");
}

stock void Karyuu_UnPauseMatch()
{
	ServerCommand("mp_unpause_match");
}

stock void Karyuu_RestartGame(int iDelay)
{
	ServerCommand("mp_restartgame %d", iDelay < 1 ? 1 : iDelay);
}

/*
 * ===  REGION  ======================================================================
 *         Name:  RoundState
 *  Description:  Functions connected to the round state
 * ===================================================================================
 */

/** Round states detiled
 *	Imported from SourceMod > sdktools_gamerules.inc
 *
 *	RoundState_Init				Initialize the game, create teams
 *	RoundState_Pregame			Before players have joined the game and also reverts to this when there are no active players
 *	RoundState_StartGame		The game is about to start, wait a bit and spawn everyone
 *	RoundState_Preround			All players are (re)spawned, frozen in place
 *	RoundState_RoundRunning		Round is on, playing normally
 *	RoundState_TeamWin			Someone has won the round
 *	RoundState_Restart			Noone has won, manually restart the game, reset scores
 *	RoundState_Stalemate		Noone has won, restart the game
 *	RoundState_GameOver			Game is over, showing the scoreboard etc
 *	RoundState_Bonus			Game is over, doing bonus round stuff
 *	RoundState_BetweenRounds	Between two rounds
 */

stock RoundState Karyuu_GetRoundState()
{
	return view_as<RoundState>(GameRules_GetProp("m_iRoundState"));
}

stock GamePhase Karyuu_GetGamePhase()
{
	return view_as<GamePhase>(GameRules_GetProp("m_gamePhase"));
}

stock bool Karyuu_IsWarmupPeriod()
{
	return Karyuu_GetPropBool("m_bWarmupPeriod");
}

stock float Karyuu_WarmupTimeLeft()
{
	return GameRules_GetPropFloat("m_fWarmupPeriodEnd");
}

stock bool Karyuu_IsOvertime()
{
	return Karyuu_GetPropBool("m_nOvertimePlaying");
}

stock bool Karyuu_IsFreezeTime()
{
	return Karyuu_GetPropBool("m_bFreezePeriod");
}

stock bool Karyuu_IsBombPlanted()
{
	return Karyuu_GetPropBool("m_bBombPlanted");
}

stock int Karyuu_GetTotalRoundTime()
{
	return GameRules_GetProp("m_iRoundTime");
}

/*
 * ===  REGION  ======================================================================
 *         Name:  Map
 *  Description:  Functions connected to the maps
 * ===================================================================================
 */

stock bool Karyuu_ChangeMap(const char[] cMap, bool bDoChecks = true)
{
	if (bDoChecks && !IsMapValid(cMap))
		return false;

	ServerCommand("changelevel %s", cMap);
	return true;
}

/*
 * ===  REGION  ======================================================================
 *         Name:  TV
 *  Description:  Functions connected to the TV
 * ===================================================================================
 */

stock bool Karyuu_IsTVEnabled()
{
	return (Karyuu_GetConVarIntSafe("tv_enable") != -1);
}

stock int Karyuu_GetTvDelay()
{
	return (Karyuu_IsTVEnabled() ? Karyuu_GetConVarIntSafe("tv_delay") : 0);
}

stock bool Karyuu_StartRecord(const char[] cDemo)
{
	char cDemoName[256];
	strcopy(STRING(cDemoName), cDemo);
	ReplaceString(STRING(cDemoName), "\"", "\\\"");
	ServerCommand("tv_record \"%s\"", cDemoName);

	if (Karyuu_IsTVEnabled())
		return true;

	LogError("Autorecording will not work with current ConVar \"tv_enable\"=0. Set \"tv_enable 1\" in server.cfg (or another config file) to fix this.");
	return false;
}

stock void Karyuu_StopRecord()
{
	ServerCommand("tv_stoprecord");
}

/*
 * ===  REGION  ======================================================================
 *         Name:  Others
 *  Description:  Just simply others
 * ===================================================================================
 */

stock void Karyuu_ExecCFG(const char[] cFile)
{
	ServerCommand("exec \"%s\"", cFile);
}
