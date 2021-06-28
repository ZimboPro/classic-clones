#include "Ending.hpp"
#include <raylib.h>
#include "../Game.hpp"

Ending::Ending()
{

}

Ending::~Ending()
{

}

void Ending::init()
{
  this->time = GetTime();
  this->thanks.setText("Thanks for playing", GetScreenWidth() >> 1, GetScreenHeight() >> 1, 80, DARKGREEN);
  this->screenFinished = false;
}

void Ending::update()
{
  if (GetTime() - this->time > 2.0f)
    this->screenFinished = true;
}

void Ending::draw()
{
    this->thanks.render();
}

void Ending::clean()
{

}

bool Ending::finished()
{
  return this->screenFinished;
}

GameScreen Ending::switchToScreen()
{
  return GameScreen::EXIT;
}
