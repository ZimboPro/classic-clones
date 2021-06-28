#include "Game.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>

Screen * Game::Game::screens[8];
GameScreen Game::currentScreen = GameScreen::LOGO;
Font Game::font = { 0 };
Music Game::music = { 0 };
Sound Game::fxCoin = { 0 };

bool Game::playMusic;
bool Game::playSound;
float Game::masterVol;
float Game::musicVol;
float Game::soundVol;

std::unique_ptr<Logo> Game::LogoScreen;
std::unique_ptr<Title> Game::TitleScreen;
std::unique_ptr<Menu> Game::MenuScreen;
std::unique_ptr<Options> Game::OptionsScreen;
std::unique_ptr<GamePlay> Game::GamePlayScreen;
std::unique_ptr<Ending> Game::EndingScreen;
std::unique_ptr<Pause> Game::PauseScreen;
std::unique_ptr<Screen> Game::ExitScreen;

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
  Game::LogoScreen = std::make_unique<Logo>();
  Game::screens[GameScreen::LOGO] = LogoScreen.get();
  Game::TitleScreen = std::make_unique<Title>();
  Game::screens[GameScreen::TITLE] = TitleScreen.get();
  Game::MenuScreen = std::make_unique<Menu>();
  Game::screens[GameScreen::MENU] = MenuScreen.get();
  Game::OptionsScreen = std::make_unique<Options>();
  Game::screens[GameScreen::OPTIONS] = OptionsScreen.get();
  Game::GamePlayScreen = std::make_unique<GamePlay>();
  Game::screens[GameScreen::GAMEPLAY] = GamePlayScreen.get();
  Game::EndingScreen = std::make_unique<Ending>();
  Game::screens[GameScreen::ENDING] = EndingScreen.get();
  Game::PauseScreen = std::make_unique<Pause>();
  Game::screens[GameScreen::PAUSE] = PauseScreen.get();
  Game::ExitScreen = std::make_unique<Screen>();
  Game::screens[GameScreen::EXIT] = ExitScreen.get();
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
