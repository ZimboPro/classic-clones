#ifndef TITLE_H
#define TITLE_H

#include "Screen.hpp"
#include "../AI.hpp"
#include "../Ball.hpp"

class Title : public Screen
{
	private:
    int framesCounter;
    int finishScreen;
    AI paddle;
    AI * player;
    Ball ball;
    float delta;
    int xPos;
    int xPosMsg;
	public:

		Title();
		~Title();

    void init();
    void update();
    void draw();
    void clean();
    bool finished();
    GameScreen switchToScreen();

};
#endif
