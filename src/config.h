#pragma once
#include <psp2/ctrl.h>

#include <string>
#include "objectgraphics.h"
#include "soundhandler.h"
#include "xmp.h"

//just for controller defines
#include <SDL2/SDL.h>

namespace Config
{
	enum keyenum
	{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_SLEFT,
		KEY_SRIGHT,
		KEY_STRAFEMOD,
		KEY_SHOOT,
		KEY_END
	};

	enum GameTitle 
	{
		GLOOM,
		DELUXE,
		GLOOM3,
		MASSACRE,
		CUSTOM,
	};
	void SetZM(bool zm);
	void SetGame(Config::GameTitle id);
	int GetGameID();
	std::string GetGamePath();
	std::string GetScriptName();
	std::string GetPicsDir();
	std::string GetLevelDir();
	std::string GetMiscDir();
	std::string GetObjectFilename(ObjectGraphics::ObjectGraphicType i);
	std::string GetGoreFilename(ObjectGraphics::ObjectGraphicType i);
	std::string GetSoundFilename(SoundHandler::Sounds i);
	std::string GetMusicFilename(int i);
	std::string GetMusicDir();
	int GetKey(keyenum k);
	void SetKey(keyenum k, int newval);
	void GetRenderSizes(int &rw, int &rh, int &ww, int& wh);
	int32_t GetFocalLength();
	int GetMouseSens();
	void SetMouseSens(int sens);
	int GetBlood();
	void SetBlood(int b);
	void SetDebug(bool b);
	bool GetDebug();
	void SetFPS(uint32_t f);
	uint32_t GetFPS();
	void SetFullscreen(int f);
	int GetFullscreen();

	int GetMT();
	void SetMT(int s);
	bool GetVSync();

	int GetAutoFire();
	void SetAutoFire(int a);

	bool UseSticks();
	
	unsigned char GetRightStickDeadzone();
	unsigned char GetLeftStickDeadzone();

	int GetSwitchSticks();
	void SetSwitchSticks(int s);

	// sound options
	int GetSFXVol();
	void SetSFXVol(int vol);
	int GetMusicVol();
	void SetMusicVol(int vol);
	void RegisterMusContext(xmp_context ctx);
	
	
	void RegisterWin(SDL_Window* _win);

	void Init();
	void Save();
};
