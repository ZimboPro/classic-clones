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
  framesCounter = 0;
    finishScreen = 0;
}

void Ending::update()
{
  if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(Game::fxCoin);
    }
}

void Ending::draw()
{
DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    // DrawTextEx(Game::font, "ENDING SCREEN", (Vector2){ 20, 10 }, Game::font.baseSize*3, 4, DARKBLUE);
    DrawText("ENDING SCREEN", 20, 10 , 20, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
}

void Ending::clean()
{

}

bool Ending::finished()
{
  return static_cast<bool>(finishScreen);
}

GameScreen Ending::switchToScreen()
{
  return GameScreen::TITLE;
}
