
#include "menuscreen.h"
#include "config.h"

void MenuScreen::Render(SDL_Surface *src, SDL_Surface *dest, Font &font)
{
	SDL_BlitSurface(src, nullptr, dest, nullptr);
	bool flash = (timer / 5) & 1;

	int scale = dest->h / 256;
	if (scale < 1)
		scale = 1;

	if (status == MENUSTATUS_MAIN)
	{
		DisplayStandardMenu(mainmenu, flash, scale, dest, font);
	}
	else if (status == MENUSTATUS_SOUNDOPTIONS)
	{
		DisplayStandardMenu(soundmenu, flash, scale, dest, font);
	}
	else if (status == MENUSTATUS_CONTROLOPTIONS)
	{
		DisplayStandardMenu(controlmenu, flash, scale, dest, font);
	}
	else if (status == MENUSTATUS_DISPLAYOPTIONS)
	{
		DisplayStandardMenu(displaymenu, flash, scale, dest, font);
	}
	else if (status == MENUSTATUS_KEYCONFIG)
	{
		switch (selection)
		{
		case Config::KEY_UP:
			font.PrintMessage("PRESS KEY FOR FORWARD", 120 * scale, dest, scale);
			break;
		case Config::KEY_DOWN:
			font.PrintMessage("PRESS KEY FOR BACK", 120 * scale, dest, scale);
			break;
		case Config::KEY_LEFT:
			font.PrintMessage("PRESS KEY FOR ROTATE LEFT", 120 * scale, dest, scale);
			break;
		case Config::KEY_RIGHT:
			font.PrintMessage("PRESS KEY FOR ROTATE RIGHT", 120 * scale, dest, scale);
			break;
		case Config::KEY_SLEFT:
			font.PrintMessage("PRESS KEY FOR STRAFE LEFT", 120 * scale, dest, scale);
			break;
		case Config::KEY_SRIGHT:
			font.PrintMessage("PRESS KEY FOR STRAFE RIGHT", 120 * scale, dest, scale);
			break;
		case Config::KEY_STRAFEMOD:
			font.PrintMessage("PRESS KEY FOR STRAFE MODIFIER", 120 * scale, dest, scale);
			break;
		case Config::KEY_SHOOT:
			font.PrintMessage("PRESS KEY FOR SHOOT", 120 * scale, dest, scale);
			break;
		}
	}
}

MenuScreen::MenuScreen()
{
	status = MENUSTATUS_MAIN;
	selection = 0;
	timer = 0;

	mainmenu.push_back(MenuEntry("CONTINUE", ACTION_RETURN, MENURET_PLAY, nullptr, nullptr));
	mainmenu.push_back(MenuEntry("CONTROL OPTIONS", ACTION_SWITCHMENU, MENUSTATUS_CONTROLOPTIONS, nullptr, nullptr));
	mainmenu.push_back(MenuEntry("SOUND OPTIONS", ACTION_SWITCHMENU, MENUSTATUS_SOUNDOPTIONS, nullptr, nullptr));
	mainmenu.push_back(MenuEntry("DISPLAY OPTIONS", ACTION_SWITCHMENU, MENUSTATUS_DISPLAYOPTIONS, nullptr, nullptr));
	mainmenu.push_back(MenuEntry("QUIT TO TITLE", ACTION_RETURN, MENURET_QUIT, nullptr, nullptr));

	soundmenu.push_back(MenuEntry("RETURN", ACTION_SWITCHMENU, MENUSTATUS_MAIN, nullptr, nullptr));
	soundmenu.push_back(MenuEntry("SFX VOLUME: ", ACTION_INT, 10, Config::GetSFXVol, Config::SetSFXVol));
	soundmenu.push_back(MenuEntry("MUSIC VOLUME: ", ACTION_INT, 10, Config::GetMusicVol, Config::SetMusicVol));

	controlmenu.push_back(MenuEntry("RETURN", ACTION_SWITCHMENU, MENUSTATUS_MAIN, nullptr, nullptr));
	controlmenu.push_back(MenuEntry("AUTOFIRE: ", ACTION_BOOL, 0, Config::GetAutoFire, Config::SetAutoFire));
	controlmenu.push_back(MenuEntry("CONFIGURE KEYS", ACTION_SWITCHMENU, MENUSTATUS_KEYCONFIG, nullptr, nullptr));
	controlmenu.push_back(MenuEntry("MOUSE SENSITIVITY: ", ACTION_INT, 10, Config::GetMouseSens, Config::SetMouseSens));

	displaymenu.push_back(MenuEntry("RETURN", ACTION_SWITCHMENU, MENUSTATUS_MAIN, nullptr, nullptr));
	displaymenu.push_back(MenuEntry("BLOOD SIZE: ", ACTION_INT, 5, Config::GetBlood, Config::SetBlood));
	displaymenu.push_back(MenuEntry("FULLSCREEN: ", ACTION_BOOL, 0, Config::GetFullscreen, Config::SetFullscreen));
	displaymenu.push_back(MenuEntry("MULTITHREAD RENDERER: ", ACTION_BOOL, 0, Config::GetMT, Config::SetMT));
}

void MenuScreen::HandleKeyMenu()
{
	int button;

	if (Input::GetButtonDown(SCE_CTRL_UP))
		button = SCE_CTRL_UP;
	if (Input::GetButtonDown(SCE_CTRL_DOWN))
		button = SCE_CTRL_DOWN;
	if (Input::GetButtonDown(SCE_CTRL_LEFT))
		button = SCE_CTRL_LEFT;
	if (Input::GetButtonDown(SCE_CTRL_RIGHT))
		button = SCE_CTRL_RIGHT;

	if (Input::GetButtonDown(SCE_CTRL_CROSS))
		button = SCE_CTRL_CROSS;
	if (Input::GetButtonDown(SCE_CTRL_SQUARE))
		button = SCE_CTRL_SQUARE;
	if (Input::GetButtonDown(SCE_CTRL_TRIANGLE))
		button = SCE_CTRL_TRIANGLE;
	if (Input::GetButtonDown(SCE_CTRL_CIRCLE))
		button = SCE_CTRL_CIRCLE;

	if (Input::GetButtonDown(SCE_CTRL_RTRIGGER))
		button = SCE_CTRL_RTRIGGER;
	if (Input::GetButtonDown(SCE_CTRL_LTRIGGER))
		button = SCE_CTRL_LTRIGGER;

	Config::SetKey((Config::keyenum)selection, button);
	selection++;
	if (selection == Config::KEY_END)
	{
		selection = 0;
		status = MENUSTATUS_MAIN;
	}
}

MenuScreen::MenuReturn MenuScreen::HandleStandardMenu(std::vector<MenuEntry> &menu)
{

	if (Input::GetButtonDown(SCE_CTRL_UP))
	{
		selection--;
		if (selection == -1)
			selection = 0;
	}
	else if (Input::GetButtonDown(SCE_CTRL_DOWN))

	{
		selection++;
		if (selection == menu.size())
			selection = menu.size() - 1;
	}
	else if (Input::GetButtonDown(SCE_CTRL_CROSS))
	{
		switch (menu[selection].action)
		{
		case ACTION_BOOL:
		{
			menu[selection].setval(!menu[selection].getval());
			break;
		}
		case ACTION_INT:
		{
			int x = (menu[selection].getval() + 1);
			if (x >= menu[selection].arg)
				x = 0;
			menu[selection].setval(x);
			break;
		}
		case ACTION_SWITCHMENU:
		{
			status = (MENUSTATUS)menu[selection].arg;
			selection = 0;
			break;
		}
		case ACTION_RETURN:
		{
			return (MenuReturn)menu[selection].arg;
			break;
		}
		default:
			break;
		}
	}
	return MENURET_NOTHING;
}

MenuScreen::MenuReturn MenuScreen::Update()
{

	switch (status)
	{
	case MENUSTATUS_MAIN:
	{
		return HandleStandardMenu(mainmenu);
		break;
	}
	case MENUSTATUS_KEYCONFIG:
	{
		HandleKeyMenu();
		break;
	}

	case MENUSTATUS_SOUNDOPTIONS:
	{
		HandleStandardMenu(soundmenu);
		break;
	}

	case MENUSTATUS_CONTROLOPTIONS:
	{
		HandleStandardMenu(controlmenu);
		break;
	}

	case MENUSTATUS_DISPLAYOPTIONS:
	{
		HandleStandardMenu(displaymenu);
		break;
	}

	default:
		break;
	}

	return MENURET_NOTHING;
}

void MenuScreen::DisplayStandardMenu(std::vector<MenuEntry> &menu, bool flash, int scale, SDL_Surface *dest, Font &font)
{
	int starty = 100 * scale;
	int yinc = 10 * scale;

	for (size_t i = 0; i < menu.size(); i++)
	{
		if (menu[i].action == ACTION_INT)
		{
			if (flash || (selection != i))
			{
				std::string menustring = menu[i].name;
				menustring += std::to_string(menu[i].getval());
				font.PrintMessage(menustring, starty, dest, scale);
			}
		}
		else if (menu[i].action == ACTION_BOOL)
		{
			if (flash || (selection != i))
			{
				std::string menustring = menu[i].name;
				menustring += menu[i].getval() ? "ON" : "OFF";
				font.PrintMessage(menustring, starty, dest, scale);
			}
		}
		else
		{
			if (flash || (selection != i))
				font.PrintMessage(menu[i].name, starty, dest, scale);
		}
		starty += yinc * ((i == 0) ? 2 : 1);
	}
}
