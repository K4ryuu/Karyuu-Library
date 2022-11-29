#if defined _KARYUU_MODULE_SOUND_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_SOUND_INCLUDED_

stock void Karyuu_PlayToRadius(float origin[3], float radius, char[] sound)
{
	char cBuffer[PLATFORM_MAX_PATH];
	FormatEx(STRING(cBuffer), "play %s", sound);
	float distance;

	for (int player = 0; player < MaxClients; player++)
	{
		if (Karyuu_IsValidPlayer(player))
		{
			distance = Karyuu_GetDistanceOrigin(player, origin);

			if (distance <= radius)
				ClientCommand(player, cBuffer);
		}
	}
}