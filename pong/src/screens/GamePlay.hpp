#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Screen.hpp"
#include "../AI.hpp"
#include "../Player.hpp"
#include "../Ball.hpp"

class GamePlay : public Screen
{
	private:
    float delta;

    AI paddle;
    Player player;
    Ball ball;
    int aiScore;
    int playerScore;

    GameScreen switchTo;
    bool isPaused;
    bool displayTimer;
    double timeDelta;
    int time;
	public:

		GamePlay();
		~GamePlay();

    void init();
    void update();
    void draw();
    void clean();
    GameScreen switchToScreen();
    void exitToMain();
    void resume();
    void updateProps(int code);


};
#endif
