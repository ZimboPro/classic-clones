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

    static GameScreen currentScreen;
    static Font font;
    static Music music;
    static Sound fxCoin;

};
#endif
