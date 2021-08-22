#include "config.h"
#include "objectgraphics.h"
#include "soundhandler.h"

#include <psp2/ctrl.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <fstream>

namespace Config
{
	static bool zombiemassacremode = false;

	static SceCtrlButtons configkeys[KEY_END];
	static int renderwidth;
	static int renderheight;
	static int windowwidth;
	static int windowheight;
	static int32_t focallength;
	static int mousesens;
	static bool autofire;
	static int bloodsize;
	static bool debug = false;
	static uint32_t FPS;
	static bool multithread = false;
	static bool vsync = false;
	static bool fullscreen = false;
	static bool switchsticks = false;

	static unsigned char rightStickDeadzone = 20;
	static unsigned char leftStickDeadzone = 20;

	static int sfxvol;
	static int musvol;
	static xmp_context musctx;

	// needed to toggle fullscreen
	static SDL_Window *win;

	unsigned char GetRightStickDeadzone()
	{
		return rightStickDeadzone;
	}

	unsigned char GetLeftStickDeadzone()
	{
		return leftStickDeadzone;
	}

	void SetDebug(bool b)
	{
		debug = b;
	}

	bool GetDebug()
	{
		return debug;
	}

	void SetFPS(uint32_t f)
	{
		FPS = f;
	}

	uint32_t GetFPS()
	{
		return FPS;
	}

	void SetFullscreen(int f)
	{
		fullscreen = f ? 1 : 0;

		if (fullscreen)
		{
			SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
		}
		else
		{
			SDL_SetWindowFullscreen(win, 0);
		}
	}

	int GetFullscreen()
	{
		return fullscreen ? 1 : 0;
	}

	int GetSwitchSticks()
	{
		return switchsticks ? 1 : 0;
	}

	void SetSwitchSticks(int s)
	{
		switchsticks = (s != 0);
	}

	void SetZM(bool zm)
	{
		zombiemassacremode = zm;
	}

	std::string GetScriptName()
	{
		if (zombiemassacremode)
		{
			std::string result = "ux0:/data/zgloom/stuf/stages";
			return result;
		}
		else
		{
			std::string result = "ux0:/data/zgloom/misc/script";
			return result;
		}
	}

	std::string GetMiscDir()
	{
		if (zombiemassacremode)
		{
			std::string result = "ux0:/data/zgloom/stuf/";
			return result;
		}
		else
		{
			std::string result = "ux0:/data/zgloom/misc/";
			return result;
		}
	}

	std::string GetPicsDir()
	{
		if (zombiemassacremode)
		{
			std::string result = "ux0:/data/zgloom/pixs/";
			return result;
		}
		else
		{
			std::string result = "ux0:/data/zgloom/pics/";
			return result;
		}
	}

	std::string GetLevelDir()
	{
		if (zombiemassacremode)
		{
			std::string result = "ux0:/data/zgloom/lvls/";
			return result;
		}
		else
		{
			std::string result = "ux0:/data/zgloom/maps/";
			return result;
		}
	}

	std::string objectfilenames[ObjectGraphics::OGT_END];
	std::string soundfilenames[SoundHandler::SOUND_END];

	std::string GetObjectFilename(ObjectGraphics::ObjectGraphicType i)
	{
		return objectfilenames[i];
	}

	std::string GetGoreFilename(ObjectGraphics::ObjectGraphicType i)
	{
		return objectfilenames[i] + "2";
	}

	std::string GetSoundFilename(SoundHandler::Sounds i)
	{
		return soundfilenames[i];
	}

	std::string GetMusicFilename(int i)
	{
		std::string result;
		if (zombiemassacremode)
		{
			if (i == 0)
				result = "ux0:/data/zgloom/musi/meda";
			else
				result = "ux0:/data/zgloom/musi/medb";
		}
		else
		{
			if (i == 0)
				result = "ux0:/data/zgloom/sfxs/med1";
			else
				result = "ux0:/data/zgloom/sfxs/med2";
		}

		return result;
	}

	std::string GetMusicDir()
	{
		std::string result;
		if (zombiemassacremode)
		{
			result = "ux0:/data/zgloom/musi/"; 
		}
		else
		{
			result = "ux0:/data/zgloom/sfxs/"; 
		}

		return result;
	}

	void RegisterMusContext(xmp_context ctx)
	{
		musctx = ctx;
	}

	void RegisterWin(SDL_Window *_win)
	{
		win = _win;
	}

	void Init()
	{
		if (zombiemassacremode)
		{
			// some of this is guesswork, need to check
			objectfilenames[ObjectGraphics::OGT_TOKENS] = "ux0:/data/zgloom/char/pwrups";
			objectfilenames[ObjectGraphics::OGT_MARINE] = "ux0:/data/zgloom/char/troopr";
			objectfilenames[ObjectGraphics::OGT_BALDY] = "ux0:/data/zgloom/char/zombi";
			objectfilenames[ObjectGraphics::OGT_TERRA] = "ux0:/data/zgloom/char/fatzo";
			objectfilenames[ObjectGraphics::OGT_PHANTOM] = "ux0:/data/zgloom/char/zomboid";
			objectfilenames[ObjectGraphics::OGT_GHOUL] = "ux0:/data/zgloom/char/ghost";
			objectfilenames[ObjectGraphics::OGT_DRAGON] = "ux0:/data/zgloom/char/zombie";
			objectfilenames[ObjectGraphics::OGT_LIZARD] = "ux0:/data/zgloom/char/skinny";
			objectfilenames[ObjectGraphics::OGT_DEMON] = "ux0:/data/zgloom/char/zocom";
			objectfilenames[ObjectGraphics::OGT_DEATHHEAD] = "ux0:/data/zgloom/char/dows-head";
			objectfilenames[ObjectGraphics::OGT_TROLL] = "ux0:/data/zgloom/char/james";

			//double check these
			soundfilenames[SoundHandler::SOUND_SHOOT] = "ux0:/data/zgloom/musi/shoot.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT2] = "ux0:/data/zgloom/musi/shoot2.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT3] = "ux0:/data/zgloom/musi/shoot3.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT4] = "ux0:/data/zgloom/musi/shoot4.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT5] = "ux0:/data/zgloom/musi/shoot5.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT] = "ux0:/data/zgloom/musi/groan.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT2] = "ux0:/data/zgloom/musi/groan2.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT3] = "ux0:/data/zgloom/musi/groan3.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT4] = "ux0:/data/zgloom/musi/groan4.bin";
			soundfilenames[SoundHandler::SOUND_TOKEN] = "ux0:/data/zgloom/musi/pwrup.bin";
			soundfilenames[SoundHandler::SOUND_DOOR] = "ux0:/data/zgloom/musi/door.bin";
			soundfilenames[SoundHandler::SOUND_FOOTSTEP] = "ux0:/data/zgloom/musi/footstep.bin";
			soundfilenames[SoundHandler::SOUND_DIE] = "ux0:/data/zgloom/musi/die.bin";
			soundfilenames[SoundHandler::SOUND_SPLAT] = "ux0:/data/zgloom/musi/splat.bin";
			soundfilenames[SoundHandler::SOUND_TELEPORT] = "ux0:/data/zgloom/musi/teleport.bin";
			soundfilenames[SoundHandler::SOUND_GHOUL] = "ux0:/data/zgloom/musi/ghost.bin";
			soundfilenames[SoundHandler::SOUND_LIZARD] = "ux0:/data/zgloom/musi/skinny.bin";
			soundfilenames[SoundHandler::SOUND_LIZHIT] = "ux0:/data/zgloom/musi/skihit.bin";
			soundfilenames[SoundHandler::SOUND_TROLLMAD] = "ux0:/data/zgloom/musi/jamesmad.bin";
			soundfilenames[SoundHandler::SOUND_TROLLHIT] = "ux0:/data/zgloom/musi/jameshit.bin";
			soundfilenames[SoundHandler::SOUND_ROBOT] = "ux0:/data/zgloom/musi/fatzo.bin";
			soundfilenames[SoundHandler::SOUND_ROBODIE] = "ux0:/data/zgloom/musi/fatzdie.bin";
			soundfilenames[SoundHandler::SOUND_DRAGON] = "ux0:/data/zgloom/musi/zombie.bin";
		}
		else
		{
			objectfilenames[ObjectGraphics::OGT_TOKENS] = "ux0:/data/zgloom/objs/tokens";
			objectfilenames[ObjectGraphics::OGT_MARINE] = "ux0:/data/zgloom/objs/marine";
			objectfilenames[ObjectGraphics::OGT_BALDY] = "ux0:/data/zgloom/objs/baldy";
			objectfilenames[ObjectGraphics::OGT_TERRA] = "ux0:/data/zgloom/objs/terra";
			objectfilenames[ObjectGraphics::OGT_PHANTOM] = "ux0:/data/zgloom/objs/phantom";
			objectfilenames[ObjectGraphics::OGT_GHOUL] = "ux0:/data/zgloom/objs/ghoul";
			objectfilenames[ObjectGraphics::OGT_DRAGON] = "ux0:/data/zgloom/objs/dragon";
			objectfilenames[ObjectGraphics::OGT_LIZARD] = "ux0:/data/zgloom/objs/lizard";
			objectfilenames[ObjectGraphics::OGT_DEMON] = "ux0:/data/zgloom/objs/demon";
			objectfilenames[ObjectGraphics::OGT_DEATHHEAD] = "ux0:/data/zgloom/objs/deathhead";
			objectfilenames[ObjectGraphics::OGT_TROLL] = "ux0:/data/zgloom/objs/troll";


			soundfilenames[SoundHandler::SOUND_SHOOT] = "ux0:/data/zgloom/sfxs/shoot.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT2] = "ux0:/data/zgloom/sfxs/shoot2.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT3] = "ux0:/data/zgloom/sfxs/shoot3.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT4] = "ux0:/data/zgloom/sfxs/shoot4.bin";
			soundfilenames[SoundHandler::SOUND_SHOOT5] = "ux0:/data/zgloom/sfxs/shoot5.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT] = "ux0:/data/zgloom/sfxs/grunt.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT2] = "ux0:/data/zgloom/sfxs/grunt2.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT3] = "ux0:/data/zgloom/sfxs/grunt3.bin";
			soundfilenames[SoundHandler::SOUND_GRUNT4] = "ux0:/data/zgloom/sfxs/grunt4.bin";
			soundfilenames[SoundHandler::SOUND_TOKEN] = "ux0:/data/zgloom/sfxs/token.bin";
			soundfilenames[SoundHandler::SOUND_DOOR] = "ux0:/data/zgloom/sfxs/door.bin";
			soundfilenames[SoundHandler::SOUND_FOOTSTEP] = "ux0:/data/zgloom/sfxs/footstep.bin";
			soundfilenames[SoundHandler::SOUND_DIE] = "ux0:/data/zgloom/sfxs/die.bin";
			soundfilenames[SoundHandler::SOUND_SPLAT] = "ux0:/data/zgloom/sfxs/splat.bin";
			soundfilenames[SoundHandler::SOUND_TELEPORT] = "ux0:/data/zgloom/sfxs/teleport.bin";
			soundfilenames[SoundHandler::SOUND_GHOUL] = "ux0:/data/zgloom/sfxs/ghoul.bin";
			soundfilenames[SoundHandler::SOUND_LIZARD] = "ux0:/data/zgloom/sfxs/lizard.bin";
			soundfilenames[SoundHandler::SOUND_LIZHIT] = "ux0:/data/zgloom/sfxs/lizhit.bin";
			soundfilenames[SoundHandler::SOUND_TROLLMAD] = "ux0:/data/zgloom/sfxs/trollmad.bin";
			soundfilenames[SoundHandler::SOUND_TROLLHIT] = "ux0:/data/zgloom/sfxs/trollhit.bin";
			soundfilenames[SoundHandler::SOUND_ROBOT] = "ux0:/data/zgloom/sfxs/robot.bin";
			soundfilenames[SoundHandler::SOUND_ROBODIE] = "ux0:/data/zgloom/sfxs/robodie.bin";
			soundfilenames[SoundHandler::SOUND_DRAGON] = "ux0:/data/zgloom/sfxs/dragon.bin";
		}

		configkeys[KEY_SHOOT] = SCE_CTRL_CROSS;
		configkeys[KEY_UP] = SCE_CTRL_UP;
		configkeys[KEY_DOWN] = SCE_CTRL_DOWN;
		configkeys[KEY_LEFT] = SCE_CTRL_LTRIGGER | SCE_CTRL_TRIANGLE;
		configkeys[KEY_RIGHT] = SCE_CTRL_RTRIGGER | SCE_CTRL_SQUARE;
		configkeys[KEY_SLEFT] = SCE_CTRL_LEFT;
		configkeys[KEY_SRIGHT] = SCE_CTRL_RIGHT;
		configkeys[KEY_STRAFEMOD] = SCE_CTRL_CIRCLE;

		renderwidth = 320;
		renderheight = 256;
		windowwidth = 960;
		windowheight = 544;

		focallength = 128;

		mousesens = 5;
		bloodsize = 2;

		multithread = false;
		debug = false;
		vsync = false;
		fullscreen = false;
		switchsticks = false;

		musvol = 5;
		sfxvol = 5;

		autofire = false;

		std::ifstream file;

		file.open("ux0:/data/zgloom/config.txt");

		if (file.is_open())
		{
			while (!file.eof())
			{
				std::string line;
					
				std::getline(file, line);

				if (line.size() && (line[0] != ';'))
				{
					std::string command = line.substr(0, line.find(" "));
					line = line.substr(line.find(" ") + 1, std::string::npos);

					//std::cout << "\"" << line << "\"" << std::endl;

					if (command == "keys")
					{
						for (int i = 0; i < KEY_END; i++)
						{
							std::string val = line.substr(0, line.find(" "));

							configkeys[i] = std::stoi(val);

							if ((i + 1) << KEY_END)
							{
								line = line.substr(line.find(" ") + 1, std::string::npos);
							}
						}
					}
					if (command == "rendersize")
					{
						renderwidth = std::stoi(line.substr(0, line.find(" ")));
						renderheight = std::stoi(line.substr(line.find(" ") + 1, std::string::npos));
					}
					if (command == "windowsize")
					{
						windowwidth = std::stoi(line.substr(0, line.find(" ")));
						windowheight = std::stoi(line.substr(line.find(" ") + 1, std::string::npos));
					}
					if (command == "focallength")
					{
						focallength = std::stoi(line);
					}
					if (command == "mousesensitivity")
					{
						mousesens = std::stoi(line);
					}
					if (command == "bloodsize")
					{
						bloodsize = std::stoi(line);
					}
					if (command == "sfxvol")
					{
						sfxvol = std::stoi(line);
					}
					if (command == "musvol")
					{
						musvol = std::stoi(line);
					}
					if (command == "multithread")
					{
						multithread = std::stoi(line) != 0;
					}
					if (command == "vsync")
					{
						vsync = std::stoi(line) != 0;
					}
					if (command == "fullscreen")
					{
						fullscreen = std::stoi(line) != 0;
					}
					if (command == "autofire")
					{
						autofire = std::stoi(line) != 0;
					}
					if (command == "rightStickDeadzone")
					{
						rightStickDeadzone = std::stoi(line.substr(0, line.find(" ")));
					}
					if (command == "leftStickDeadzone")
					{
						leftStickDeadzone = std::stoi(line.substr(0, line.find(" ")));
					}
				}
			}

			file.close();
		}
	}

	int GetKey(keyenum k)
	{
		return configkeys[k];
	}

	void SetKey(keyenum k, int newval)
	{
		configkeys[k] = newval; 
	}

	int GetMouseSens()
	{
		return mousesens;
	}

	void SetMouseSens(int sens)
	{
		mousesens = sens;
	}

	int GetBlood()
	{
		return bloodsize;
	}

	void SetBlood(int b)
	{
		bloodsize = b;
	}

	int GetMT()
	{
		return multithread ? 1 : 0;
	}

	void SetMT(int s)
	{
		multithread = (s != 0);
	}

	bool GetVSync()
	{
		return vsync;
	}

	int GetSFXVol()
	{
		return sfxvol;
	}

	void SetSFXVol(int vol)
	{
		sfxvol = vol;
		//Mix_Volume(-1, vol * 12);
	}

	int GetMusicVol()
	{
		return musvol;
	}

	int GetAutoFire()
	{
		return autofire ? 1 : 0;
	}

	void SetAutoFire(int a)
	{
		autofire = (a != 0);
	}

	void SetMusicVol(int vol)
	{
		musvol = vol;
		//this does not seem to work with Hook'ed audio? Can't find any documentation explicitly forbidding it
		//Mix_VolumeMusic(vol * 12);
		for (int i = 0; i < XMP_MAX_CHANNELS; i++)
		{
			xmp_channel_vol(musctx, i, vol * 7);
		}
	}

	void Save()
	{

		std::ofstream file;

		file.open("config.txt");

		if (file.is_open())
		{
			file << ";ZGloom config\n\n";

			file << ";SDL keyvals, up/down/left/right/strafeleft/straferight/strafemod/shoot\n";
			file << "keys ";

			for (int i = 0; i < KEY_END; i++)
			{
				file << configkeys[i];

				if ((i + 1) != KEY_END)
				{
					file << " ";
				}
			}

			file << "\n";

			file << ";The size of the game render bitmap. Bumping this up may lead to more overflow issues in the renderer. But you can get, say, 16:9 by using 460x256 or something in a larger window\n";
			file << "rendersize " << renderwidth << " " << renderheight << "\n";

			file << ";The size of the actual window/fullscreen res. Guess this should be a multiple of the above for pixel perfect\n";
			file << "windowsize " << windowwidth << " " << windowheight << "\n";

			file << ";vsync on or off?\n";
			file << "vsync " << (vsync ? 1 : 0) << "\n";

			file << ";fullscreen on or off?\n";
			file << "fullscreen " << (fullscreen ? 1 : 0) << "\n";

			file << ";focal length. Original used 128 for a 320x256 display, bump this up for higher resolution. Rule of thumb: for 90degree fov, = renderwidth/2\n";
			file << "focallength " << focallength << "\n";

			file << ";Mouse sensitivity\n";
			file << "mousesensitivity " << mousesens << "\n";

			file << ";size of blood splatters in pixels\n";
			file << "bloodsize " << bloodsize << "\n";

			file << ";audio volumes\n";
			file << "sfxvol " << sfxvol << "\n";
			file << "musvol " << musvol << "\n";

			file << ";multithreaded renderer (somewhat experimental)\n";
			file << "multithread " << (multithread ? 1 : 0) << "\n";

			file << ";rapidfire?\n";
			file << "autofire " << (autofire ? 1 : 0) << "\n";

			file << ";rightStickDeadzone\n";
			file << "rightStickDeadzone " << rightStickDeadzone << "\n";
			file << ";leftStickDeadzone\n";
			file << "leftStickDeadzone " << leftStickDeadzone << "\n";

			file.close();
		}
	}

	void GetRenderSizes(int &rw, int &rh, int &ww, int &wh)
	{
		rw = renderwidth;
		rh = renderheight;
		ww = windowwidth;
		wh = windowheight;
	}

	int32_t GetFocalLength()
	{
		return focallength;
	}
}
