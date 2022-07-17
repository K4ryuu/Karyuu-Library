#if defined _KARYUU_MODULE_MENU_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_MENU_INCLUDED_

stock bool Karyuu_ClearClientMenu(int iClient)
{
	if (!Karyuu_IsClientIndex(iClient) || IsFakeClient(iClient) || !IsClientInGame(iClient))
		return false;

	CancelClientMenu(iClient);

	Panel panel = new Panel();
	panel.Send(iClient, __Karyuu_Panel_Void, 1);
	delete panel;

	return true;
}
public int __Karyuu_Panel_Void(Menu menu, MenuAction action, int param1, int param2) { delete menu; }

stock void Karyuu_Menu_SetTitle(Menu menu, const char[] myString, any...)
{
	int len					 = strlen(myString) + 255;
	char[] myFormattedString = new char[len];
	VFormat(myFormattedString, len, myString, 3);

	menu.SetTitle(myFormattedString);
}

stock void Karyuu_Menu_AddItem(Menu menu, int ItemDraw = ITEMDRAW_DEFAULT, char[] id, const char[] myString, any...)
{
	int len					 = strlen(myString) + 255;
	char[] myFormattedString = new char[len];
	VFormat(myFormattedString, len, myString, 5);

	menu.AddItem(id, myFormattedString, ItemDraw);
}

stock char Karyuu_Menu_GetSelect(Menu menu, int iParam)
{
	char cBuffer[32];
	GetMenuItem(menu, iParam, STRING(cBuffer));
	return cBuffer;
}

stock void Karyuu_Menu_Send(Menu menu, int iClient, bool ExitBack = false, bool Exit = true, int time = MENU_TIME_FOREVER)
{
	menu.ExitBackButton = ExitBack;
	menu.ExitButton		= Exit;
	menu.Display(iClient, time);
}

stock void Karyuu_HandleMenuJunk(Menu menu, MenuAction action)
{
	if (action == MenuAction_End)
		delete menu;
}

stock void Karyuu_Panel_SetTitle(Panel TargetPanel, const char[] myString, any...)
{
	int len					 = strlen(myString) + 255;
	char[] myFormattedString = new char[len];
	VFormat(myFormattedString, len, myString, 3);

	TargetPanel.SetTitle(myFormattedString);
}

stock void Karyuu_Panel_AddItem(Panel TargetPanel, int ItemDraw = ITEMDRAW_DEFAULT, const char[] myString, any...)
{
	int len					 = strlen(myString) + 255;
	char[] myFormattedString = new char[len];
	VFormat(myFormattedString, len, myString, 4);

	TargetPanel.DrawItem(myFormattedString, ItemDraw);
}

stock void Karyuu_Panel_AddText(Panel TargetPanel, const char[] myString, any...)
{
	int len					 = strlen(myString) + 255;
	char[] myFormattedString = new char[len];
	VFormat(myFormattedString, len, myString, 3);

	TargetPanel.DrawText(myFormattedString);
}

stock void Karyuu_Panel_Send(Panel TargetPanel, MenuHandler handler, int iClient, int time = MENU_TIME_FOREVER)
{
	TargetPanel.Send(iClient, handler, time);
	delete TargetPanel;
}

stock void Karyuu_HandlePanelJunk(Menu menu, MenuAction action)
{
	if (action == MenuAction_End || action == MenuAction_Cancel)
		delete menu;
}