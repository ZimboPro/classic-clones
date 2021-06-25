#include "Game.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>

Screen * Game::Game::screens[8];
GameScreen Game::currentScreen = GameScreen::LOGO;
Font Game::font = { 0 };
Music Game::music = { 0 };
Sound Game::fxCoin = { 0 };

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
  SetSoundVolume(Game::fxCoin, 0.4f);

  spdlog::info("Play music");
  SetMusicVolume(Game::music, 0.4f);
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
