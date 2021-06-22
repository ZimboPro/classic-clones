#ifndef SCREEN_H
#define SCREEN_H

typedef enum GameScreen { LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

class Screen
{
	private:

	public:

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual bool finished() = 0;
    virtual GameScreen switchToScreen() = 0;

};
#endif
