#include "Ball.hpp"
#include <raymath.h>

float setDirection(int min, int max)
{
  int mag = GetRandomValue(min, max);
  int dir = GetRandomValue(0, 100);
  return (dir < 50) ? mag : -mag;
}

Ball::Ball()
{
  this->size = 20.0f;
  this->position.x = 400;
  this->position.y = 300;
  this->speed = 100;
  this->direction.x = setDirection(5, 25);
  this->direction.y = setDirection(5, 25);
  this->direction = Vector2Normalize(this->direction);
  this->color = RED;
}


Ball::~Ball()
{

}

void Ball::update(float delta)
{
  this->position.x += this->direction.x * this->speed * delta;
  this->position.y += this->direction.y * this->speed * delta;
  if (this->position.y - this->size <= 0) {
    this->direction.y *= -1;
    this->position.y = this->size;
  } else if (this->position.y + this->size >= 600) {
    this->direction.y *= -1;
    this->position.y = static_cast<float>(600) - this->size;
  }
  // TODO end round
  if (this->position.x - this->size <= 0) {
    this->direction.x *= -1;
    this->position.x = this->size;
  } else if (this->position.x + this->size >= 800) {
    this->direction.x *= -1;
    this->position.x = static_cast<float>(800) - this->size;
  }

  DrawCircleV(this->position, this->size, this->color);
}

void Ball::reverseX()
{
    this->direction.x *= -1;
}

void Ball::reverseY()
{
    this->direction.y *= -1;
}

void Ball::setPosX(float x)
{
  this->position.x = x;
}
