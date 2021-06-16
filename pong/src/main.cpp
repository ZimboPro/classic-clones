#include "Game.hpp"
#include "AI.hpp"
#include "Ball.hpp"
#include <raylib.h>

int main(int argc, char const *argv[])
{
  Game game;
  game.init();
  AI paddle;
  Ball ball;
  while (game.isRunning())
  {
    game.clear();
    float delta = GetFrameTime();
    paddle.update(delta, &ball);
    ball.update(delta);
    game.render();
  }
  game.clean();

  return 0;
}
