#include "Title.hpp"
#include <raylib.h>
#include "../Game.hpp"
#include <spdlog/spdlog.h>

Title::Title()
{
  this->player = new AI(760);
}

Title::~Title()
{
  delete this->player;
}

void Title::init()
{
  spdlog::info("Init Title");
  framesCounter = 0;
  finishScreen = 0;
  ball.reset();
  paddle.reset();
  player->reset();
  this->xPos = (GetScreenWidth() - MeasureText("Pong", 80)) >> 1;
  this->xPosMsg = (GetScreenWidth() - MeasureText("Press any key to enter", 20)) >> 1;
}

void Title::update()
{
    if (GetKeyPressed())
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 1;   // GAMEPLAY
        if (Game::playSound)
          PlaySound(Game::fxCoin);
    }

    // Game in background
    delta = GetFrameTime();
    ball.update(delta);
    paddle.update(delta, &ball);
    player->update(delta, &ball);
    ball.checkCollision(paddle.getPaddleRec(), 1, paddle.xPos());
    ball.checkCollision(player->getPaddleRec(), -1, player->xPos());
    if (ball.isOutOfBounds(800)) {
      ball.reset();
      paddle.reset();
      player->reset();
    }
}

void Title::draw()
{
  Color t = GREEN;
  t.a = 120;
  ball.render();
  paddle.render();
  player->render();
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), t);

  // DrawTextEx(Game::font, "Pong", (Vector2){ 20, 10 }, Game::font.baseSize*3, 4, DARKGREEN);
  DrawText("Pong", this->xPos, 10, 80, BLACK);
  if (static_cast<int>(GetTime() * 2.0f) % 4 != 0)
    DrawText("Press any key to enter", this->xPosMsg, 220, 20, BLACK);
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
  return GameScreen::MENU;
}
