#include "AI.hpp"
#include <spdlog/spdlog.h>

AI::AI()
{

}

AI::AI(int xPos)
{
  if (this->paddle)
  {
    delete this->paddle;
  }
  this->paddle = new Paddle(xPos);
  this->_xPos = xPos;
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
}

void AI::render()
{
  this->paddle->render();
}
