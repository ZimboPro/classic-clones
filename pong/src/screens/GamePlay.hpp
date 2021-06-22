#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Screen.hpp"
#include "../AI.hpp"
#include "../Player.hpp"
#include "../Ball.hpp"

class GamePlay : public Screen
{
	private:
    int framesCounter;
    int finishScreen;
    float delta;

    AI paddle;
    Player player;
    Ball ball;
    int aiScore;
    int playerScore;

    GameScreen switchTo;
	public:

		GamePlay();
		~GamePlay();

    void init();
    void update();
    void draw();
    void clean();
    bool finished();
    GameScreen switchToScreen();

};
#endif
