#include "AI.hpp"
#include <spdlog/spdlog.h>

AI::AI()
{

}

AI::~AI()
{
  delete this->paddle;
}

void AI::update(float delta, Ball * ball)
{
  if (this->paddle->position.y > ball->position.y) {
    this->paddle->direction.y = -1.0f;
  } else if (this->paddle->position.y < ball->position.y)
  {
    this->paddle->direction.y = 1.0f;
  } else {
    this->paddle->direction.y = 0.0f;
  }
  this->paddle->update(delta);

  if (CheckCollisionCircleRec(ball->position, ball->size, this->paddle->rec)) {
    ball->reverseX();
    ball->setPosX(this->paddle->position.x + this->paddle->rec.width / 2 + ball->size);
  }
}
