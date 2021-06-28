#include "Menu.hpp"
#include <raylib.h>
#include "../Game.hpp"
#include "Options.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::init()
{
  this->xPos = (GetScreenWidth() - MeasureText("Pong", 80)) >> 1;
  this->xPosPlay = (GetScreenWidth() - MeasureText("Play", 20)) >> 1;
  this->xPosOptions = (GetScreenWidth() - MeasureText("Settings", 20)) >> 1;
  this->xPosExit = (GetScreenWidth() - MeasureText("Quit Game", 20)) >> 1;
  this->highLighted = 0;
  this->screenFinished = false;
}

void Menu::update()
{
  if (IsKeyPressed(KEY_DOWN)) {
    this->highLighted++;
  }
  if (IsKeyPressed(KEY_UP)) {
    this->highLighted--;
  }
  if (this->highLighted < 0) {
    this->highLighted = 0;
  }
  if (this->highLighted > 2) {
    this->highLighted = 2;
  }
  if (IsKeyPressed(KEY_ENTER)) {
    this->screenFinished = true;
    switch (this->highLighted)
    {
    case 0:
      this->screen = GameScreen::GAMEPLAY;
      break;
    case 1:
      this->screen = GameScreen::OPTIONS;
      ((Options *)Game::screens[GameScreen::OPTIONS])->setSwitch(GameScreen::MENU);
      break;
    case 2:
      this->screen = GameScreen::EXIT;
      break;

    default:
      break;
    }
  }
}

void Menu::draw()
{
  DrawText("Pong", this->xPos, 10, 80, DARKGREEN);
  DrawText("Play", this->xPosPlay, 220, 20, highLighted == 0 ? GREEN : DARKGREEN);
  DrawText("Settings", this->xPosOptions, 250, 20, highLighted == 1 ? GREEN : DARKGREEN);
  DrawText("Quit Game", this->xPosExit, 280, 20, highLighted == 2 ? GREEN : DARKGREEN);
}

void Menu::clean()
{

}

bool Menu::finished()
{
  return this->screenFinished;
}

GameScreen Menu::switchToScreen()
{
  return this->screen;
}
