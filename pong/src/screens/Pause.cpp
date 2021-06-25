#include "Pause.hpp"
#include "../Game.hpp"
#include "GamePlay.hpp"
#include <raylib.h>
#include <spdlog/spdlog.h>

Pause::Pause()
{

}

Pause::~Pause()
{

}

void Pause::init()
{
  this->xPos = (GetScreenWidth() - MeasureText("Paused", 80)) >> 1;
  this->xPosResume = (GetScreenWidth() - MeasureText("Resume", 20)) >> 1;
  this->xPosOptions = (GetScreenWidth() - MeasureText("Settings", 20)) >> 1;
  this->xPosMenu = (GetScreenWidth() - MeasureText("Exit to Main Menu", 20)) >> 1;

  this->highLighted = 0;
  this->screenFinished = false;
}

void Pause::update()
{
  if (IsKeyPressed(KEY_DOWN))
    this->highLighted++;
  if (IsKeyPressed(KEY_UP))
    this->highLighted--;

  if (this->highLighted < 0)
    this->highLighted = 0;
  else if (this->highLighted > 2)
    this->highLighted = 2;

  if (IsKeyPressed(KEY_ENTER)) {
    this->screenFinished = true;
    switch (this->highLighted)
    {
    case 0:
      this->switchTo = GameScreen::GAMEPLAY;
      break;
    case 1:
      this->switchTo = GameScreen::OPTIONS;
      break;
    case 2:
      this->switchTo = GameScreen::MENU;
      break;

    default:
      break;
    }
  }

  if (this->screenFinished && this->switchTo == GAMEPLAY) {
    spdlog::info("Game refresh");
    Game::screens[GameScreen::GAMEPLAY]->updateProps(1);
  }
  if (this->screenFinished && this->switchTo == MENU) {
    spdlog::info("Clean game exit");
    Game::screens[GameScreen::GAMEPLAY]->updateProps(2);
    spdlog::info("Clean game clean");
    Game::screens[GameScreen::GAMEPLAY]->clean();
    spdlog::info("Cleaned game");
  }

}

void Pause::draw()
{
  DrawText("Paused", this->xPos, 10, 80, DARKGREEN);
  DrawText("Resume", this->xPosResume, 220, 20, highLighted == 0 ? GREEN : DARKGREEN);
  DrawText("Settings", this->xPosOptions, 250, 20, highLighted == 1 ? GREEN : DARKGREEN);
  DrawText("Exit to Main Menu", this->xPosMenu, 280, 20, highLighted == 2 ? GREEN : DARKGREEN);
}

void Pause::clean()
{
  if (this->switchTo == MENU) {

  }
}

GameScreen Pause::switchToScreen()
{
  return this->switchTo;
}
