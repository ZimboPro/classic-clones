#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Screen.hpp"
#include "../AI.hpp"
#include "../Player.hpp"
#include "../Ball.hpp"
#include "../utils/Text.hpp"

class GamePlay : public Screen
{
	private:
    float delta;

    AI paddle;
    Player player;
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
