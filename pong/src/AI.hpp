#ifndef AI_H
#define AI_H

#include <raylib.h>
#include "Paddle.hpp"
#include "Ball.hpp"

class AI
{
	private:
    Paddle * paddle = new Paddle(20);
    int _xPos = 20;
	public:

		AI();
		AI(int xPos);
		~AI();

    void update(float delta, Ball * ball);

    Rectangle getPaddleRec() {
      return this->paddle->rec;
    }

    float xPos() {
      return this->paddle->position.x;
    }

    void reset() {
      this->paddle->reset(this->_xPos);
    }

    void render();

};
#endif
