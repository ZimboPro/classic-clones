#include "ScreenManager.hpp"

std::vector<GameScreen> ScreenManager::navigatedScreens;
std::map<GameScreen, Screen *> ScreenManager::screens;
GameScreen ScreenManager::current;
Screen * ScreenManager::_currentScreen;

void ScreenManager::redirectTo(GameScreen screen, bool transition)
{
  _currentScreen->clean();
  navigatedScreens.pop_back();
  setCurrent(screen);
}

void ScreenManager::navigateTo(GameScreen screen, bool transition)
{
  setCurrent(screen);
}

void ScreenManager::navigateBack()
{
  _currentScreen->clean();
  navigatedScreens.pop_back();
  current = navigatedScreens[navigatedScreens.size() - 1];
}

const GameScreen ScreenManager::currentScreen()
{
  return navigatedScreens[current];
}

template<class T>
void ScreenManager::addScreen(T * screenInstance, GameScreen screen)
{
  screens[screen] = std::make_unique<T>(screenInstance);
}

Screen * ScreenManager::getCurrentScreen()
{
  return screens[current];
}

Screen * ScreenManager::getScreen(GameScreen screen)
{
  return screens[screen];
}

void ScreenManager::render()
{
  _currentScreen->draw();
}

void ScreenManager::update()
{
  _currentScreen->update();
}

void ScreenManager::setCurrent(GameScreen screen, bool transition)
{
  navigatedScreens.emplace_back(screen);
  current = screen;
  _currentScreen = screens[current];
}
