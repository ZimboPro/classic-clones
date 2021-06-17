#ifndef BALL_H
#define BALL_H

#include <raylib.h>

class Ball
{
	private:

	public:

		Ball();
		~Ball();
    Vector2 position;
    float size;
    Color color;
    int speed;
    Vector2 direction;
    void update(float delta);
    void reverseX();
    void reverseY();
    void setPosX(float x);
    void checkCollision(Rectangle rec, int xDir, float xPos);

};
#endif
