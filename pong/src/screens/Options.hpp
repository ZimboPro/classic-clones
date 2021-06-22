#ifndef OPTIONS_H
#define OPTIONS_H

#include "Screen.hpp"

class Options : public Screen
{
	private:
    int framesCounter;
    int finishScreen;
	public:

		Options();
		~Options();

    void init();
    void update();
    void draw();
    void clean();
    bool finished();
    GameScreen switchToScreen();

};
#endif
