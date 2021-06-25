#include "GamePlay.hpp"
#include "../Game.hpp"
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

GamePlay::GamePlay()
{
  this->isPaused = false;
  this->displayTimer = true;
}

GamePlay::~GamePlay()
{

}

void GamePlay::init()
{
  spdlog::info("Game init {}", this->isPaused);
    if (!this->isPaused) {
      aiScore = 0;
      playerScore = 0;
      paddle.reset();
      player.reset();
      ball.reset();
      this->displayTimer = true;
    }
    this->screenFinished = false;
    this->isPaused = false;
    if (this->displayTimer) {
      this->time = 3;
      this->timeDelta = GetTime();
    }
}

void GamePlay::update()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->screenFinished = true;
        switchTo = GameScreen::PAUSE;
        PlaySound(Game::fxCoin);
        this->isPaused = true;
        this->displayTimer = true;
    }
    if (this->displayTimer)
    {
      if (GetTime() - this->timeDelta >= 1.0f)
      {
        this->timeDelta = GetTime();
        this->time--;
        if (this->time == 0) {
          this->displayTimer = false;
        }
      }
    } else
    {
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
}

void GamePlay::draw()
{
    ball.render();
    paddle.render();
    player.render();
    DrawText(fmt::format("{}", aiScore).c_str(), 200, 10, 20, BLUE);
    DrawText(":", 400, 10, 20, WHITE);
    DrawText(fmt::format("{}", playerScore).c_str(), 600, 10, 20, BLUE);
    if (displayTimer) {
      const char * text = fmt::format("{}", time).c_str();
      int width = MeasureText(text, 80) >> 1;
      DrawText(text, 400 - width, 260, 80, DARKGREEN);
    }
}

void GamePlay::clean()
{

}

GameScreen GamePlay::switchToScreen()
{
  return this->switchTo;
}

void GamePlay::exitToMain()
{
  spdlog::info("Exit gameplay");
  spdlog::info("Exit gameplay {}", this->isPaused);
  this->isPaused = false;
  spdlog::info("Exit gameplay");
}

void GamePlay::resume()
{
  spdlog::info("Resume gameplay");
  this->isPaused = true;
}

void GamePlay::updateProps(int code)
{
  spdlog::info("Update props");
  switch (code)
  {
  case 1:
    // this->resume();
    spdlog::info("Resume gameplay");
    this->isPaused = true;
    break;
  case 2:
    this->exitToMain();
    break;

  default:
    break;
  }
}
