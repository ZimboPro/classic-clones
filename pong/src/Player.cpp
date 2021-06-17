#include "Player.hpp"

#include <raylib.h>
#include <spdlog/spdlog.h>

Player::Player()
{

}

Player::~Player()
{
  delete this->paddle;
}

void Player::update(float delta)
{
  float dir = 0.0f;
  if (IsKeyDown(KEY_UP)) {
    dir -= 1.0f;
  }
  if (IsKeyDown(KEY_DOWN)) {
    dir += 1.0f;
  }
  this->paddle->direction.y = dir;
  this->paddle->update(delta);
}
