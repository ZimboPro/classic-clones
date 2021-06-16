#include "Game.hpp"
#include <spdlog/spdlog.h>
#include <raylib.h>

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
