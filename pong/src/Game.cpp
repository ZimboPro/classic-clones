#include "Game.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>

GameScreen Game::currentScreen = GameScreen::LOGO;
Font Game::font = { 0 };
Music Game::music = { 0 };
Sound Game::fxCoin = { 0 };

Game::Game()
{

}

Game::~Game()
{

}

void Game::init()
{
  spdlog::info("Initialise Game");
  InitWindow(800, 600, "Pong");
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
  CloseWindow();
}

bool Game::isRunning()
{
  return !WindowShouldClose();
}
