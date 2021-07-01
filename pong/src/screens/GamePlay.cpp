#include "GamePlay.hpp"
#include "../Game.hpp"
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include "../utils/TextHelper.hpp"
#include "ScreenManager.hpp"

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
  spdlog::info("Game init");
    if (!this->isPaused) {
      aiScore = 0;
      playerScore = 0;
      paddle.reset();
      player.reset();
      ball.reset();
      this->displayTimer = true;
    }
    this->aiText.setText(fmt::format("{}", aiScore), 200, 10, 20, BLUE);
    this->playerText.setText(fmt::format("{}", playerScore), 600, 10, 20, BLUE);
    this->screenFinished = false;
    this->isPaused = false;
    if (this->displayTimer) {
      this->time = 3;
    }
    this->timerText.setText(fmt::format("{}", time), 400, 300, 80, DARKGREEN);
}

void GamePlay::update()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->screenFinished = true;
        switchTo = GameScreen::PAUSE;
        ScreenManager::navigateTo(GameScreen::PAUSE);
        if (Game::playSound)
          PlaySound(Game::fxCoin);
        this->isPaused = true;
        this->displayTimer = true;
    }
    if (this->displayTimer)
    {
      if (this->timerText.scale(1.0f, 80, 200))
      {
        this->time--;
        this->timerText.setText(fmt::format("{}", this->time));
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
        if (ball.position.x < 400) {
          playerScore++;
          this->playerText.setText(fmt::format("{}", playerScore));
        }
        else {
          aiScore++;
          this->aiText.setText(fmt::format("{}", aiScore));
        }
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
    this->aiText.render();
    TextHelper::DrawTextPos(":", 400, 10, 20, WHITE);
    this->playerText.render();
    if (displayTimer) {
      this->timerText.render();
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
  this->isPaused = false;
}

void GamePlay::resume()
{
  this->isPaused = true;
}

void GamePlay::updateProps(int code)
{
  switch (code)
  {
  case 1:
    this->resume();
    break;
  case 2:
    this->exitToMain();
    break;

  default:
    break;
  }
}
