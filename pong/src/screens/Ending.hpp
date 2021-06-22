#ifndef ENDING_H
#define ENDING_H

#include "Screen.hpp"

class Ending : public Screen
{
	private:
    int framesCounter;
    int finishScreen;
	public:

		Ending();
		~Ending();

    void init();
    void update();
    void draw();
    void clean();
    bool finished();
    GameScreen switchToScreen();

};
#endif
