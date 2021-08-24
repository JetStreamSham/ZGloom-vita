#include "titlescreen.h"

void TitleScreen::Render(SDL_Surface *src, SDL_Surface *dest, Font &font)
{
	SDL_BlitSurface(src, nullptr, dest, nullptr);
	bool flash = (timer / 5) & 1;

	font.PrintMessage("A BLACK MAGIC GAME   PSVITA PORT BY JETSTREAMSHAM", 245, dest, 1); // added copyright text in footer

	if (status == TITLESTATUS_MAIN)
	{
		if (flash || (selection != MAINENTRY_PLAY))
			font.PrintMessage("PLAY", 150, dest, 1);
		if (flash || (selection != MAINENTRY_SELECT))
			font.PrintMessage("LEVEL SELECT", 170, dest, 1);
		if (flash || (selection != MAINENTRY_ABOUT))
			font.PrintMessage("ABOUT", 190, dest, 1);
		if (flash || (selection != MAINENTRY_QUIT))
			font.PrintMessage("EXIT", 210, dest, 1);
	}
	else if (status == TITLESTATUS_SELECT)
	{
		for (int i = selection - 10; i < selection + 10; i++)
		{
			if ((i >= 0) && (i < (int)levelnames.size()))
			{
				if (flash || (i != selection))
					font.PrintMessage(levelnames[i], 100 + (i - selection) * 10, dest, 1);
			}
		}
	}
	else
	{
		font.PrintMessage("GLOOM", 30, dest, 1);

		font.PrintMessage("A BLACK MAGIC GAME ENGINE", 50, dest, 1); // added "ENGINE" for other ZGloom games

		font.PrintMessage("PROGRAMMED BY MARK SIBLY", 70, dest, 1);
		font.PrintMessage("GRAPHICS BY THE BUTLER BROTHERS", 80, dest, 1);
		font.PrintMessage("MUSIC BY KEV STANNARD", 90, dest, 1);
		font.PrintMessage("AUDIO BY US", 100, dest, 1);
		font.PrintMessage("PRODUCED AND DESIGNED BY US", 110, dest, 1);
		font.PrintMessage("GAME CODED IN DEVPAC2", 120, dest, 1);
		font.PrintMessage("UTILITIES CODED IN BLITZ BASIC 2", 130, dest, 1);
		font.PrintMessage("RENDERED IN DPAINT3 AND DPAINT4", 140, dest, 1);
		font.PrintMessage("DECRUNCHING CODE BY THOMAS SCHWARZ", 150, dest, 1);

		font.PrintMessage("PSVITA PORT BY JETSTREAMSHAM", 170, dest, 1); // added port
	}
}

TitleScreen::TitleScreen()
{
	status = TITLESTATUS_MAIN;
	selection = 0;
	timer = 0;
}

TitleScreen::TitleReturn TitleScreen::Update(int &levelout)
{

	if (status == TITLESTATUS_MAIN)
	{

		if (Input::GetButtonDown(SCE_CTRL_DOWN))
		{
			selection++;
			if (selection == MAINENTRY_END)
				selection = MAINENTRY_END - 1;
		}

		if (Input::GetButtonDown(SCE_CTRL_UP))
		{
			selection--;
			if (selection == -1)
				selection = 0;
		}

		if (Input::GetButtonDown(SCE_CTRL_CROSS))
		{
			if (selection == MAINENTRY_PLAY)
				return TITLERET_PLAY;
			if (selection == MAINENTRY_QUIT)
				return TITLERET_QUIT;
			if (selection == MAINENTRY_ABOUT)
				status = TITLESTATUS_ABOUT;
			if (selection == MAINENTRY_SELECT)
			{
				selection = 0;
				status = TITLESTATUS_SELECT;
			};
		}
	}
	else if (status == TITLESTATUS_SELECT)
	{

		if (Input::GetButtonDown(SCE_CTRL_DOWN))
		{
			selection++;
			if (selection == levelnames.size())
				selection = levelnames.size() - 1;
		}

		if (Input::GetButtonDown(SCE_CTRL_UP))
		{
			selection--;
			if (selection == -1)
				selection = 0;
		}

		if (Input::GetButtonDown(SCE_CTRL_CROSS))
		{
			levelout = selection;
			status = TITLESTATUS_MAIN;
			selection = 0;
			return TITLERET_SELECT;
		}
	}
	else
	{
		if (Input::GetButtonDown(SCE_CTRL_CROSS))
			status = TITLESTATUS_MAIN;
	}

	return TITLERET_NOTHING;
}
