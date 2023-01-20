// clang-format off
#if defined _KARYUU_MODULE_PANEL_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_PANEL_INCLUDED_

methodmap K4Panel < Panel
{
	public K4Panel()
	{
		Panel hPanel = new Panel();
		return view_as<K4Panel>(hPanel);
	}

	public void SetTitle(const char[] sTitle, any...)
	{
		int iLength						 = strlen(sTitle) + 255;
		char[] sFormattedTitle = new char[iLength];
		VFormat(sFormattedTitle, iLength, sTitle, 2);

		this.SetTitle(sFormattedTitle);
	}

	public void AddItem(int iDraw = ITEMDRAW_DEFAULT, const char[] sText, any...)
	{
		int iLength						 = strlen(sText) + 255;
		char[] sFormattedItem = new char[iLength];
		VFormat(sFormattedItem, iLength, sText, 3);

		this.DrawItem(sFormattedItem, iDraw);
	}

	public void AddText(const char[] sText, any...)
	{
		int iLength						 = strlen(sText) + 255;
		char[] sFormattedText = new char[iLength];
		VFormat(sFormattedText, iLength, sText, 2);

		this.DrawText(sFormattedText);
	}

	public void Send(MenuHandler hHandler, int iClient, int iTime = MENU_TIME_FOREVER)
	{
		this.Send(iClient, hHandler, iTime);
		delete this;
	}

	public void HandleJunk(MenuAction hAction)
	{
		if (hAction == MenuAction_End || hAction == MenuAction_Cancel)
			delete this;
	}

	public void Delete()
	{
		delete this;
	}
}