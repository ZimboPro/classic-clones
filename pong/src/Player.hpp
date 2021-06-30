#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.hpp"

class Player
{
	private:
    Paddle * paddle;
    KeyboardKey up;
    KeyboardKey down;
	public:

		Player();
		Player(int x);
		~Player();

    void update(float delta);
    Rectangle getPaddleRec() {
      return this->paddle->rec;
    }

    float xPos() {
      return this->paddle->position.x;
    }

    void reset() {
      this->paddle->reset(760);
    }

    void render() {
      this->paddle->render();
    }

};
#endif
