#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "screens/Screen.hpp"
#include <memory>
#include "screens/Logo.hpp"
#include "screens/Title.hpp"
#include "screens/Menu.hpp"
#include "screens/GamePlay.hpp"
#include "screens/Options.hpp"
#include "screens/Ending.hpp"
#include "screens/Pause.hpp"

enum StorageEnum
{
  MasterSound,
  MusicSound,
  FxSound,
  MasterVol,
  MusicVol,
  FXVol
};

class Game
{
	private:
	public:

		static void init();
    static void clear();
		static void render();
    static void clean();
    static bool isRunning();
    static void createScreens();
    // static void loadAssets();
    static bool getBoolStorageValue(StorageEnum key, bool defaultValue);
    static bool setBoolStorageValue(StorageEnum key, bool value);
    static float getFloatStorageValue(StorageEnum key, float defaultValue);
    static float getFloatStorageValue(StorageEnum key, float defaultValue, float divideBy);
    static bool setFloatStorageValue(StorageEnum key, float value);

    static Font font;
    static Music music;
    static Sound fxCoin;
    static bool playMusic;
    static bool playSound;
    static float masterVol;
    static float musicVol;
    static float soundVol;
};
#endif
