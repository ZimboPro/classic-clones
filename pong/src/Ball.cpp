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
  this->color = RED;
  this->reset();
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

void Ball::checkCollision(Rectangle rec, int xDir, float xPos)
{
  if (CheckCollisionCircleRec(this->position, this->size, rec)) {
    this->reverseX();
    this->setPosX(static_cast<float>(xPos) + (rec.width / 2 + this->size) * static_cast<float>(xDir));
    this->speed += 5;
  }
}

bool Ball::isOutOfBounds(int width)
{
  return ((this->position.x - this->size <= 0) || (this->position.x + this->size >= width));
}

void Ball::reset()
{
  this->position.x = 400;
  this->position.y = 300;
  this->speed = 200;
  this->direction.x = setDirection(5, 25);
  this->direction.y = setDirection(5, 25);
  this->direction = Vector2Normalize(this->direction);
}

void Ball::render()
{
  DrawCircleV(this->position, this->size, this->color);
}
