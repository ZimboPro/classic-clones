#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

class Paddle
{
	private:

	public:

		Paddle(int x);
		~Paddle();
    Vector2 position;
    Vector2 direction;
    Rectangle rec;
    Color color;
    int speed;
    void update(float delta);
    void reset(int x);
    void render();


};
#endif
