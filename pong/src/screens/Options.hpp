#ifndef OPTIONS_H
#define OPTIONS_H

#include "Screen.hpp"
#include "../utils/Text.hpp"

class Options : public Screen
{
	private:
    int framesCounter;
    GameScreen screen;
    Text titleLabel;

    Text musicLabel;
    Text musicValue;
    Text soundLabel;
    Text soundValue;

    Text masterVolLabel;
    Text masterVolValue;
    Text musicVolLabel;
    Text musicVolValue;
    Text soundVolLabel;
    Text soundVolValue;

    Text back;
    int highlighted;
	public:

		Options();
		~Options();

    void init();
    void update();
    void draw();
    void clean();
    GameScreen switchToScreen();

    void setSwitch(GameScreen screen) {
      this->screen = screen;
    }

};
#endif
