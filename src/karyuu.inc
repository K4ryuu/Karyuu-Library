
#if defined _KARYUU_MODULE_BASE_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_BASE_INCLUDED_

#pragma semicolon 1
#pragma newdecls optional;

/*==== NOTE <-- Important! ===================================================*
 |																	   		  						|
 |	> Comment out the modules that you don't want to include. 				  		|
 |	> Some modules may use other modules. 									  				|
 |	> If you want to use a module, you must include it.                      	|
 | 																			  						|
 *============================================================================*/

#include <sourcemod>
#include <sdktools>

/*==== NOTE <-- Important! ===================================================*
 |																	   		  						|
 |	> Bypass cstrike.inc dependency 										  					|
 | 																			  						|
 *============================================================================*/
#if !defined _cstrike_included
	#define CS_TEAM_NONE        0   /* No team yet */
	#define CS_TEAM_SPECTATOR   1   /* Spectators */
	#define CS_TEAM_T           2   /* Terrorists */
	#define CS_TEAM_CT          3   /* Counter-Terrorists */

	#define CS_SLOT_PRIMARY     0   /* Primary weapon slot */
	#define CS_SLOT_SECONDARY   1   /* Secondary weapon slot */
	#define CS_SLOT_KNIFE       2   /* Knife slot */
	#define CS_SLOT_GRENADE     3   /* Grenade slot (will only return one grenade) */
	#define CS_SLOT_C4          4   /* C4 slot */
	#define CS_SLOT_BOOST       11  /* Slot for healthshot and shield (will only return one weapon/item) */
	#define CS_SLOT_UTILITY     12  /* Slot for tablet */
#endif

#include <karyuu/variable/bit>
#include <karyuu/variable/convert>
#include <karyuu/variable/datetime>
#include <karyuu/variable/float>
#include <karyuu/variable/gamedata>
#include <karyuu/variable/handles>
#include <karyuu/variable/int>
#include <karyuu/variable/random>
#include <karyuu/variable/strings>

#include <karyuu/game/team>
#include <karyuu/game/game>

#include <karyuu/api>
#include <karyuu/weapon>
#include <karyuu/server>
#include <karyuu/prop>
#include <karyuu/offset>
#include <karyuu/entity>
#include <karyuu/dump>
#include <karyuu/client>
#include <karyuu/weapon>
#include <karyuu/menu>
#include <karyuu/sound>

#include <karyuu/plugin/benchmark>
#include <karyuu/plugin/command>
#include <karyuu/plugin/convar>
#include <karyuu/plugin/database>
#include <karyuu/plugin/filesystem>
#include <karyuu/plugin/function>
#include <karyuu/plugin/chatprocessor>
#include <karyuu/plugin/cookie>