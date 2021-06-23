#ifndef MENU_H
#define MENU_H

#include "Screen.hpp"

class Menu : public Screen
{
	private:
    int xPos;
    int xPosPlay;
    int xPosOptions;
    int xPosExit;
    int highLighted;
    GameScreen screen;
    bool screenFinished;

	public:

		Menu();
		~Menu();

    void init();
    void update();
    void draw();
    void clean();
    bool finished();
    GameScreen switchToScreen();

};
#endif
