#include "Game.hpp"
#include "AI.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include <raylib.h>

int main(int argc, char const *argv[])
{
  Game game;
  game.init();
  AI paddle;
  Player player;
  Ball ball;
  while (game.isRunning())
  {
    game.clear();
    float delta = GetFrameTime();
    ball.update(delta);
    paddle.update(delta, &ball);
    player.update(delta);
    ball.checkCollision(paddle.getPaddleRec(), 1, paddle.xPos());
    ball.checkCollision(player.getPaddleRec(), -1, player.xPos());
    game.render();
  }
  game.clean();

  return 0;
}
