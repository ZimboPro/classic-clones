#include "GamePlay.hpp"
#include "../Game.hpp"
#include <spdlog/fmt/fmt.h>

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{

}

void GamePlay::init()
{
    framesCounter = 0;
    finishScreen = 0;
    aiScore = 0;
    playerScore = 0;
    paddle.reset();
    player.reset();
    ball.reset();
}

void GamePlay::update()
{
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        switchTo = GameScreen::ENDING;
        PlaySound(Game::fxCoin);
    }
    delta = GetFrameTime();
    ball.update(delta);
    paddle.update(delta, &ball);
    player.update(delta);
    ball.checkCollision(paddle.getPaddleRec(), 1, paddle.xPos());
    ball.checkCollision(player.getPaddleRec(), -1, player.xPos());
    if (ball.isOutOfBounds(800)) {
      if (ball.position.x < 400)
        playerScore++;
      else
        aiScore++;
      ball.reset();
      paddle.reset();
      player.reset();
    }
}

void GamePlay::draw()
{
    ball.render();
    paddle.render();
    player.render();
    DrawText(fmt::format("{}", aiScore).c_str(), 200, 10, 20, BLUE);
    DrawText(":", 400, 10, 20, WHITE);
    DrawText(fmt::format("{}", playerScore).c_str(), 600, 10, 20, BLUE);
}

void GamePlay::clean()
{

}

bool GamePlay::finished()
{
  return static_cast<bool>(finishScreen);
}

GameScreen GamePlay::switchToScreen()
{
  return this->switchTo;
}
