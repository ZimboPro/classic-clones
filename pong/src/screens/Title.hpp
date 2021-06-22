#ifndef TITLE_H
#define TITLE_H

#include "Screen.hpp"

class Title : public Screen
{
	private:
    int framesCounter;
    int finishScreen;
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
