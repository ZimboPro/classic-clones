#ifndef GAMEPLAYPVP_H
#define GAMEPLAYPVP_H

#include "Screen.hpp"
#include "../Player.hpp"
#include "../Ball.hpp"
#include "../utils/Text.hpp"

class GamePlayPVP : public Screen
{
	private:
    float delta;

    Player * playerLeft;
    Player * player;
    Ball ball;
    Text aiText;
    int aiScore;
    Text playerText;
    int playerScore;

    GameScreen switchTo;
    bool isPaused;
    bool displayTimer;
    Text timerText;
    int time;

	public:
		GamePlayPVP();
		~GamePlayPVP();

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
