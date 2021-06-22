#include "Options.hpp"

Options::Options()
{

}

Options::~Options()
{

}

void Options::init()
{
  framesCounter = 0;
  finishScreen = 0;
}

void Options::update()
{

}

void Options::draw()
{

}

void Options::clean()
{

}

bool Options::finished()
{
  return static_cast<bool>(finishScreen);
}

GameScreen Options::switchToScreen()
{
  return GameScreen::GAMEPLAY;
}
