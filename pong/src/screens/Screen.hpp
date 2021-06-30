#ifndef SCREEN_H
#define SCREEN_H

typedef enum GameScreen { LOGO = 0, TITLE, MENU, OPTIONS, GAMEPLAY, ENDING, EXIT, PAUSE, GAMEPLAYPVP } GameScreen;

class Screen
{
	protected:
    bool screenFinished = false;
	public:

    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};
    virtual void clean(){};
    virtual bool finished(){ return screenFinished; };
    virtual GameScreen switchToScreen(){return GameScreen::LOGO; };
    virtual void updateProps(int) {}

};
#endif
