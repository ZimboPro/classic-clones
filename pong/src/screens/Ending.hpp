#ifndef ENDING_H
#define ENDING_H

#include "Screen.hpp"
#include "../utils/Text.hpp"

class Ending : public Screen
{
	private:
    double time;
    Text thanks;
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
