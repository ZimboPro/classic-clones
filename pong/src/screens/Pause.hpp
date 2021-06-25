#ifndef PAUSE_H
#define PAUSE_H

#include "Screen.hpp"

class Pause : public Screen
{
	private:
    int highLighted;

    int xPos;
    int xPosResume;
    int xPosOptions;
    int xPosMenu;

    GameScreen switchTo;

	public:

		Pause();
		~Pause();

    void init();
    void update();
    void draw();
    void clean();
    GameScreen switchToScreen();

};
#endif
