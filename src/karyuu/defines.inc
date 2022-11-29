#if defined _KARYUU_MODULE_DEFINES_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_DEFINES_INCLUDED_

#define STRING(%1) %1, sizeof(%1)

#define Karyuu_MAX(% 0, % 1)	   (((% 0) > (% 1)) ? (% 0) : (% 1))

#define Karyuu_MAX_INTEGER_VALUE  		2147483647
#define Karyuu_MAX_INTEGER_LENGTH 		16
#define Karyuu_MAX_FLOAT_LENGTH 			32
#define Karyuu_MAX_QUERY_SIZE 			2048
#define Karyuu_MAX_MAP_NAME_LENGTH 		64
#define Karyuu_MAX_CONVAR_VALUE_SIZE 	256
#define Karyuu_MAX_AUTH_LENGTH			21
#define Karyuu_CONVERT_AUTH_LENGTH 		64
#define Karyuu_MAX_IP_LENGTH 				23
#define Karyuu_MAX_MESSAGE_LENGTH 		512

#define KARYUU_LOOP_CLIENTS(%1) for (int %1 = 1; %1 <= MaxClients; %1++) if (IsClientInGame(%1))
#define KARYUU_LOOP_PLAYERS(%1) for (int %1 = 1; %1 <= MaxClients; %1++) if (IsClientInGame(%1) && !IsFakeClient(%1))

#define Karyuu_MAX_WEAPON_CLASSNAME_LENGTH 	24
#define Karyuu_MAX_WEAPON_NAME_LENGTH			48
#define Karyuu_MAX_WEAPON_PREFIX_LENGTH		6
#define Karyuu_MAX_WEAPONS 						48

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

#define Karyuu_MAX_ENTITY_LIMIT 4097