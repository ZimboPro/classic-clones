#include "Paddle.hpp"
#include <raylib.h>

Paddle::Paddle(int x)
{
	this->direction.x = 0.0f;
	this->direction.y = 0.0f;
  this->position.y = 300;
  this->position.x = x;
  this->speed = 50;
  this->color = BLUE;
  this->rec.height = 80.0f;
  this->rec.width = 20.0f;
  this->rec.x = this->position.x- this->rec.width / 2;
  this->rec.y = this->position.y - this->rec.height / 2;
}

Paddle::~Paddle()
{

}

void Paddle::update(float delta)
{
  this->position.x += this->direction.x * this->speed * delta;
  this->position.y += this->direction.y * this->speed * delta;
  this->rec.x += this->direction.x * this->speed * delta;
  this->rec.y += this->direction.y * this->speed * delta;
  if (this->rec.y <= 0) {
    this->rec.y = 0.0f;
    this->position.y = this->rec.height / 2;
  }
  if (this->rec.y + this->rec.height >= 600) {
    this->rec.y = static_cast<float>(600) - this->rec.height;
    this->position.y = this->rec.y + this->rec.height / 2;
  }
  DrawRectangleRec(this->rec, this->color);
}
