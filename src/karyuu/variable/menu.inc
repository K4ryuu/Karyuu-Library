// clang-format off
#if defined _KARYUU_MODULE_MENU_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_MENU_INCLUDED_

methodmap K4Menu < Menu
{
	public K4Menu(MenuHandler hHandler, MenuAction hAction = MENU_ACTIONS_DEFAULT)
	{
		Menu hMenu = new Menu(hHandler, hAction);
		return view_as<K4Menu>(hMenu);
	}

	public void SetTitle(const char[] sTitle, any...)
	{
		int iLength				  = strlen(sTitle) + 255;
		char[] sFormattedTitle = new char[iLength];
		VFormat(sFormattedTitle, iLength, sTitle, 2);

		this.SetTitle(sFormattedTitle);
	}

	public void AddItem(int iDraw = ITEMDRAW_DEFAULT, char[] sUnique, const char[] sText, any...)
	{
		int iLength				 = strlen(sText) + 255;
		char[] sFormattedText = new char[iLength];
		VFormat(sFormattedText, iLength, sText, 4);

		this.AddItem(sUnique, sFormattedText, iDraw);
	}

	public void GetSelect(int iParam, char[] sBuffer, int iLength)
	{
		GetMenuItem(this, iParam, sBuffer, iLength);
	}

	public void Send(int iClient, bool bBack = false, bool bExit = true, int iTime = MENU_TIME_FOREVER)
	{
		this.ExitBackButton = bBack;
		this.ExitButton	  = bExit;
		this.Display(iClient, iTime);
	}

	public void HandleJunk(MenuAction hAction)
	{
		if (hAction == MenuAction_End)
			delete this;
	}

	public void Delete()
	{
		delete this;
	}
}