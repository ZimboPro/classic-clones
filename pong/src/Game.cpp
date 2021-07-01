#include "Game.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>
#include "screens/ScreenManager.hpp"

Font Game::font = { 0 };
Music Game::music = { 0 };
Sound Game::fxCoin = { 0 };

bool Game::playMusic;
bool Game::playSound;
float Game::masterVol;
float Game::musicVol;
float Game::soundVol;

void Game::init()
{
  spdlog::info("Initialise Game");
  InitWindow(800, 600, "Pong");
  SetExitKey(KEY_NULL);

  spdlog::info("Initialise Audio");
  InitAudioDevice();

  // Game::font = LoadFont("assets/mecha.png");
  Game::music = LoadMusicStream("assets/ambient.ogg");
  Game::fxCoin = LoadSound("assets/coin.wav");

  Game::playMusic = Game::getBoolStorageValue(StorageEnum::MusicSound, true);
  Game::playSound = Game::getBoolStorageValue(StorageEnum::FxSound, true);
  Game::masterVol = Game::getFloatStorageValue(StorageEnum::MasterVol, 100.0f);
  Game::musicVol = Game::getFloatStorageValue(StorageEnum::MusicVol, 100.0f);
  Game::soundVol = Game::getFloatStorageValue(StorageEnum::FxSound, 100.0f);

  SetSoundVolume(Game::fxCoin, Game::soundVol / 100.0f);
  spdlog::info("Play music");
  SetMusicVolume(Game::music, Game::musicVol / 100.0f);
  SetMasterVolume(Game::masterVol / 100.0f);
  if (Game::playMusic)
    PlayMusicStream(Game::music);
}

void Game::clear()
{
  BeginDrawing();
  ClearBackground(BLACK);
}

void Game::render()
{
  EndDrawing();
}

void Game::clean()
{
  spdlog::info("Clean up");

    // Unload all global loaded data (i.e. fonts) here!
    // UnloadFont(Game::font);
    UnloadMusicStream(Game::music);
    UnloadSound(Game::fxCoin);

    CloseAudioDevice();     // Close audio context
  CloseWindow();
}

bool Game::isRunning()
{
  return !WindowShouldClose();
}

void Game::createScreens() {
  spdlog::info("Create screens");
  ScreenManager::addScreen(new Logo(), GameScreen::LOGO);
  ScreenManager::addScreen(new Title(), GameScreen::TITLE);
  ScreenManager::addScreen(new Menu(), GameScreen::MENU);
  ScreenManager::addScreen(new Options(), GameScreen::OPTIONS);
  ScreenManager::addScreen(new GamePlay(), GameScreen::GAMEPLAY);
  ScreenManager::addScreen(new Ending(), GameScreen::ENDING);
  ScreenManager::addScreen(new Pause(), GameScreen::PAUSE);
  ScreenManager::addScreen(new Screen(), GameScreen::EXIT);
}

bool Game::getBoolStorageValue(StorageEnum key, bool defaultValue)
{
  unsigned int temp = LoadStorageValue(key);
  if (temp == 0)
    return defaultValue;
  if (temp == 1)
    return false;
  return true;
}

bool Game::setBoolStorageValue(StorageEnum key, bool value)
{
  int v = value ? 2 : 1;
  return SaveStorageValue(key, v);
}

float Game::getFloatStorageValue(StorageEnum key, float defaultValue)
{
  unsigned int temp = LoadStorageValue(key);
  if (temp == 0)
    return defaultValue;
  return static_cast<float>(temp);
}

float Game::getFloatStorageValue(StorageEnum key, float defaultValue, float divideBy)
{
  float temp = getFloatStorageValue(key, defaultValue);
  return defaultValue / divideBy;
}

bool Game::setFloatStorageValue(StorageEnum key, float value)
{
  return SaveStorageValue(key, static_cast<unsigned int>(value));
}
