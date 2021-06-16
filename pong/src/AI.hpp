#ifndef AI_H
#define AI_H

#include <raylib.h>
#include "Paddle.hpp"
#include "Ball.hpp"

class AI
{
	private:
    Paddle * paddle = new Paddle(20);
	public:

		AI();
		~AI();

    void update(float delta, Ball * ball);

};
#endif
