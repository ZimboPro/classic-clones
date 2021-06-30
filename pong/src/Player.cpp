#include "Player.hpp"

#include <raylib.h>
#include <spdlog/spdlog.h>

Player::Player()
{
  this->paddle = new Paddle(760);
  this->up = KEY_UP;
  this->down = KEY_DOWN;
}

Player::Player(int x)
{
  this->paddle = new Paddle(x);
  this->up = KEY_W;
  this->down = KEY_S;
}

Player::~Player()
{
  delete this->paddle;
}

void Player::update(float delta)
{
  float dir = 0.0f;
  if (IsKeyDown(this->up)) {
    dir -= 1.0f;
  }
  if (IsKeyDown(this->down)) {
    dir += 1.0f;
  }
  this->paddle->direction.y = dir;
  this->paddle->update(delta);
}
