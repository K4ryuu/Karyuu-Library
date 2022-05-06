#if defined _KARYUU_MODULE_COLORPOOL_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_COLORPOOL_INCLUDED_

enum CL_Color
{
	CL_Color_Default	= 0x01,
	CL_Color_Player		= 0x0F,
	CL_Color_Darkred	= 0x02,
	CL_Color_Error		= 0x07,
	CL_Color_Warning	= 0x10,
	CL_Color_Info		= 0x0A,
	CL_Color_Text		= 0x06,
	CL_Color_Highlight	= 0x10,
	CL_Color_Settings	= 0x0F,
	CL_Color_Command	= 0x0F,
	CL_Color_Team_0		= 0x08,
	CL_Color_Team_1		= 0x09,
	CL_Color_Team_2		= 0x11,
	CL_Color_Teamcolor	= 0x03,
	CL_Color_White		= 0x01,
	CL_Color_Red		= 0x07,
	CL_Color_Lightred	= 0x0F,
	CL_Color_Bluegrey	= 0x0A,
	CL_Color_Blue		= 0x0B,
	CL_Color_Darkblue	= 0x0C,
	CL_Color_Purple		= 0x03,
	CL_Color_Orchid		= 0x0E,
	CL_Color_Orange		= 0x10,
	CL_Color_Yellow		= 0x09,
	CL_Color_Gold		= 0x10,
	CL_Color_Lightgreen = 0x05,
	CL_Color_Green		= 0x04,
	CL_Color_Lime		= 0x06,
	CL_Color_Grey		= 0x08,
	CL_Color_Grey2		= 0x0D,
	CL_Color_Engine_1	= 0x01,
	CL_Color_Engine_2	= 0x02,
	CL_Color_Engine_3	= 0x03,
	CL_Color_Engine_4	= 0x04,
	CL_Color_Engine_5	= 0x05,
	CL_Color_Engine_6	= 0x06,
	CL_Color_Engine_7	= 0x07,
	CL_Color_Engine_8	= 0x08,
	CL_Color_Engine_9	= 0x09,
	CL_Color_Engine_10	= 0x0A,
	CL_Color_Engine_11	= 0x0B,
	CL_Color_Engine_12	= 0x0C,
	CL_Color_Engine_13	= 0x0D,
	CL_Color_Engine_14	= 0x0E,
	CL_Color_Engine_15	= 0x0F,
	CL_Color_Engine_16	= 0x10,
};

CL_Color _CL_ColorMap(const char[] color, int& length)
{
	switch (color[0])
	{
		case 'e':
		{
			if (color[1] == 'n')
			{
				switch (color[7])
				{
					case '1':
					{
						switch (color[8])
						{
							case '}':
							{
								length = 9;
								return CL_Color_Engine_1;
							}
							case '0':
							{
								length = 10;
								return CL_Color_Engine_10;
							}
							case '1':
							{
								length = 10;
								return CL_Color_Engine_11;
							}
							case '2':
							{
								length = 10;
								return CL_Color_Engine_12;
							}
							case '3':
							{
								length = 10;
								return CL_Color_Engine_13;
							}
							case '4':
							{
								length = 10;
								return CL_Color_Engine_14;
							}
							case '5':
							{
								length = 10;
								return CL_Color_Engine_15;
							}
							case '6':
							{
								length = 10;
								return CL_Color_Engine_16;
							}
						}
					}
					case '2':
					{
						length = 9;
						return CL_Color_Engine_2;
					}
					case '3':
					{
						length = 9;
						return CL_Color_Engine_3;
					}
					case '4':
					{
						length = 9;
						return CL_Color_Engine_4;
					}
					case '5':
					{
						length = 9;
						return CL_Color_Engine_5;
					}
					case '6':
					{
						length = 9;
						return CL_Color_Engine_6;
					}
					case '7':
					{
						length = 9;
						return CL_Color_Engine_7;
					}
					case '8':
					{
						length = 9;
						return CL_Color_Engine_8;
					}
					case '9':
					{
						length = 9;
						return CL_Color_Engine_9;
					}
				}
			}
			else if (color[1] == 'r')
			{
				length = 6;
				return CL_Color_Error;
			}
		}
		case 't':
		{
			if (color[2] == 'a')
			{
				if (color[4] == ' ')
				{
					if (color[5] == '0')
					{
						length = 7;
						return CL_Color_Team_0;
					}
					else if (color[5] == '1')
					{
						length = 7;
						return CL_Color_Team_1;
					}
					else if (color[5] == '2')
					{
						length = 7;
						return CL_Color_Team_2;
					}
				}
				else if (color[4] == 'c')
				{
					length = 10;
					return CL_Color_Teamcolor;
				}
			}
			else if (color[2] == 'x')
			{
				length = 5;
				return CL_Color_Text;
			}
		}
		case 'g':
		{
			if (color[1] == 'r')
			{
				if (color[3] == 'y')
				{
					if (color[4] == '}')
					{
						length = 5;
						return CL_Color_Grey;
					}
					else if (color[4] == '2')
					{
						length = 6;
						return CL_Color_Grey2;
					}
				}
				else if (color[3] == 'e')
				{
					length = 6;
					return CL_Color_Green;
				}
			}
			else if (color[1] == 'o')
			{
				length = 5;
				return CL_Color_Gold;
			}
		}
		case 'd':
		{
			if (color[1] == 'a')
			{
				if (color[4] == 'r')
				{
					length = 8;
					return CL_Color_Darkred;
				}
				else if (color[4] == 'b')
				{
					length = 9;
					return CL_Color_Darkblue;
				}
			}
			else if (color[1] == 'e')
			{
				length = 8;
				return CL_Color_Default;
			}
		}
		case 'l':
		{
			if (color[2] == 'g')
			{
				if (color[5] == 'r')
				{
					length = 9;
					return CL_Color_Lightred;
				}
				else if (color[5] == 'g')
				{
					length = 11;
					return CL_Color_Lightgreen;
				}
			}
			else if (color[2] == 'm')
			{
				length = 5;
				return CL_Color_Lime;
			}
		}
		case 'p':
		{
			if (color[1] == 'l')
			{
				length = 7;
				return CL_Color_Player;
			}
			else if (color[1] == 'u')
			{
				length = 7;
				return CL_Color_Purple;
			}
		}
		case 'w':
		{
			if (color[1] == 'a')
			{
				length = 8;
				return CL_Color_Warning;
			}
			else if (color[1] == 'h')
			{
				length = 6;
				return CL_Color_White;
			}
		}
		case 'b':
		{
			if (color[4] == 'g')
			{
				length = 9;
				return CL_Color_Bluegrey;
			}
			else if (color[4] == '}')
			{
				length = 5;
				return CL_Color_Blue;
			}
		}
		case 'o':
		{
			if (color[2] == 'c')
			{
				length = 7;
				return CL_Color_Orchid;
			}
			else if (color[2] == 'a')
			{
				length = 7;
				return CL_Color_Orange;
			}
		}
		case 'i':
		{
			length = 5;
			return CL_Color_Info;
		}
		case 'h':
		{
			length = 10;
			return CL_Color_Highlight;
		}
		case 's':
		{
			length = 9;
			return CL_Color_Settings;
		}
		case 'c':
		{
			length = 8;
			return CL_Color_Command;
		}
		case 'r':
		{
			length = 4;
			return CL_Color_Red;
		}
		case 'y':
		{
			length = 7;
			return CL_Color_Yellow;
		}
	}

	return view_as<CL_Color>(0x00);
}