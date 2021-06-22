#ifndef LOGO_H
#define LOGO_H

#include "Screen.hpp"

class Logo : public Screen
{
	private:
    int framesCounter = 0;
    int finishScreen = 0;

    int logoPositionX = 0;
    int logoPositionY = 0;

    int lettersCount = 0;

    int topSideRecWidth = 0;
    int leftSideRecHeight = 0;

    int bottomSideRecWidth = 0;
    int rightSideRecHeight = 0;

    char raylib[8] = { 0 };     // raylib text array, max 8 letters
    int state = 0;              // Tracking animation states (State Machine)
    float alpha = 1.0f;
	public:

		Logo();
		~Logo();

    void init();
    void update();
    void draw();
    void clean();
    bool finished();
    GameScreen switchToScreen();

};
#endif
