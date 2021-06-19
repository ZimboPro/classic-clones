#include "Game.hpp"
#include "AI.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include <raylib.h>
#include <spdlog/fmt/fmt.h>

int main(int argc, char const *argv[])
{
  Game game;
  game.init();
  AI paddle;
  Player player;
  Ball ball;
  int aiScore = 0;
  int playerScore = 0;
  while (game.isRunning())
  {
    game.clear();
    float delta = GetFrameTime();
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
    DrawText(fmt::format("{}", aiScore).c_str(), 200, 10, 20, BLUE);
    DrawText(":", 400, 10, 20, WHITE);
    DrawText(fmt::format("{}", playerScore).c_str(), 600, 10, 20, BLUE);
    game.render();
  }
  game.clean();

  return 0;
}
