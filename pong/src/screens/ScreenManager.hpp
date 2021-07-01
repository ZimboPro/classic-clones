#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.hpp"
#include <vector>
#include <memory>
#include <map>

class ScreenManager
{
	private:
    static std::vector<GameScreen> navigatedScreens;
    static std::map<GameScreen, Screen *> screens;
    static GameScreen current;
    static Screen * _currentScreen;
	public:

    static void setCurrent(GameScreen screen, bool transition = false);
    static void redirectTo(GameScreen screen, bool transition = false);
    static void navigateTo(GameScreen screen, bool transition = false);
    static void navigateBack();
    static const GameScreen currentScreen();
    template<class T>
    static void addScreen(T * screenInstance, GameScreen screen);
    static Screen * getCurrentScreen();
    static Screen * getScreen(GameScreen screen);
    static void render();
    static void update();

};
#endif
