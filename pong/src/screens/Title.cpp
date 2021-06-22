#include "Title.hpp"
#include <raylib.h>
#include "../Game.hpp"

Title::Title()
{

}

Title::~Title()
{

}

void Title::init()
{
  framesCounter = 0;
  finishScreen = 0;
}

void Title::update()
{
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 1;   // GAMEPLAY
        PlaySound(Game::fxCoin);
    }
}

void Title::draw()
{
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
  // DrawTextEx(Game::font, "Pong", (Vector2){ 20, 10 }, Game::font.baseSize*3, 4, DARKGREEN);
  DrawText("Pong", 20, 10, 20, DARKGREEN);
  DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
}

void Title::clean()
{

}

bool Title::finished()
{
    return static_cast<bool>(finishScreen);
}

GameScreen Title::switchToScreen()
{
  return GameScreen::GAMEPLAY;
}
