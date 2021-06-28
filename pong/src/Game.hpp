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
    static std::unique_ptr<Logo> LogoScreen;
    static std::unique_ptr<Title> TitleScreen;
    static std::unique_ptr<Menu> MenuScreen;
    static std::unique_ptr<Options> OptionsScreen;
    static std::unique_ptr<GamePlay> GamePlayScreen;
    static std::unique_ptr<Ending> EndingScreen;
    static std::unique_ptr<Pause> PauseScreen;
    static std::unique_ptr<Screen> ExitScreen;
	public:
    static Screen * screens[8];

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

    static GameScreen currentScreen;
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
