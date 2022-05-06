#if defined _KARYUU_MODULE_API_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_API_INCLUDED_

stock void Karyuu_StartSimpleForward(Handle hForward)
{
	Call_StartForward(hForward);
	Call_Finish();
}